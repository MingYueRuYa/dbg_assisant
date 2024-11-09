#include "NTFSSearchHelper.h"
#include "NTFSFileSearch/common.h"

#include <fileapi.h>

#pragma comment( lib, "Shlwapi.lib" )

NTFSSearchHelper::NTFSSearchHelper(std::shared_ptr<std::threadpool> thread_pool)
  : _workbranch_ptr(thread_pool)
{
}

NTFSSearchHelper::~NTFSSearchHelper()
{
  for (auto& item : this->_map_ntfs_about) {
    delete item.first;
    delete item.second;
  }
}

void NTFSSearchHelper::set_finish_call_back(call_back cb)
{
  this->_finished_cb = cb;
}

void NTFSSearchHelper::set_search_file_name(const std::vector<wstring>& files_name)
{
  for (auto& f : files_name) {
    this->_files_name.push_back(f);
  }
}

bool NTFSSearchHelper::start()
{
  if (this->is_started())
  {
    return false;
  }

  auto func = [this](wchar_t disk) {
    WCHAR szVolume[7] = { L'\\', L'\\', L'.', L'\\', disk, L':' };
    CNTFSVolume* vol = nullptr;
    CNTFSVolumeSearcher* search = nullptr;
    {
      std::lock_guard<std::mutex> lock(this->_mutex);
      vol = new CNTFSVolume();
      search = new CNTFSVolumeSearcher();
      _map_ntfs_about[vol] = search;
    }

    if (!vol->Open(szVolume)) {
      //TODO error
      return;
    }
    if (!search->SetVolume(vol))
    {
      //TODO error
      return;
    }
    for (auto& item : this->_files_name) {
      this->FindFilesWithSameName(search, item);
    }
  };

  vector<wchar_t> disk_info = this->get_disk_volumn();
  this->_thread_count = disk_info.size() * this->_files_name.size();
  for (auto& item : disk_info)
  {
    (this->_workbranch_ptr)->commit(func, item);
  }

  return true;
}

void NTFSSearchHelper::stop()
{
  for (auto& item : this->_map_ntfs_about) {
    item.second->SetStopSearch(true);
  }
  this->_workbranch_ptr.reset();
}


vector<wchar_t> NTFSSearchHelper::get_disk_volumn() const
{
  DWORD dwDisk = GetLogicalDrives();
  int dwMask = 1;
  int step = 1;
  dwMask << 1;

  int alphabet_num = 26;
  std::map<int, wchar_t> disk_map = {};
  for (int i = 0; i < alphabet_num; i++) {
    disk_map[1 << i] = L'A' + i;
  }

  vector<wchar_t> disk_vec = {};
  while (step < alphabet_num) {
    ++step;
    if (0 != disk_map[dwMask & dwDisk]) {
      disk_vec.push_back(disk_map[dwMask & dwDisk]);
    }
    dwMask = dwMask << 1;
  }

  return disk_vec;
}

void NTFSSearchHelper::FindFilesWithSameName(CNTFSVolumeSearcher* search, const wstring& file_name)
{
  PNTFS_FILE_ENTRY	pFileResults;
  UINT64				nResultCount;

  search->ClearFileFilters();

  if (!search->AddFileFilter(FF_OPERATOR_EQUAL, FF_FACTOR_FILENAME, file_name.c_str()))
  {
    wprintf(L"Failed to add file filter\n");
    return;
  }

  BOOL bSuccess = search->FindFiles(FILE_SEARCH_FLAG_FIND_FILES,
    &pFileResults,
    &nResultCount
  );
  vector<wstring> result_vec = {};
  if (bSuccess)
  {
    if (!nResultCount)
    {
      wprintf(L"No files found\n");
    }
    else
    {
      PNTFS_FILE_ENTRY pEnumResult = pFileResults;
      for (UINT64 i = 0; i < nResultCount; ++i)
      {
        //wprintf(L"%I64u: %s\n", i + 1, pEnumResult->lpszFileName);
        result_vec.push_back(pEnumResult->lpszFileName);
        if (pEnumResult->NextEntryOffset == 0)
        {
          //wprintf(L"\n");
          break;
        }

        pEnumResult = POINTER_ADD(PNTFS_FILE_ENTRY, pFileResults, pEnumResult->NextEntryOffset);
      }
    }

    search->FreeFileEntries(pFileResults);
    if (this->_finished_cb != nullptr)
    {
      this->_finished_cb(result_vec);
    }
    this->_thread_count--;
  }

  //wprintf(L"Error: failed to search volume files\n");
}

bool NTFSSearchHelper::is_started() const
{
  return this->_thread_count != 0 ? true : false;
}

