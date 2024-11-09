#pragma once

#include <string>
#include <functional>
#include <vector>
#include <map>
#include <atomic>

#include "ThreadPool/thread_pool.hpp"

#include "NTFSFileSearch/NTFSVolume.h"
#include "NTFSFileSearch/NTFSVolumeSearcher.h"

using std::wstring;
using std::vector;
using std::threadpool;

using call_back = std::function<void(std::vector<wstring>)>;

class NTFSSearchHelper
{
public:
  NTFSSearchHelper(std::shared_ptr<std::threadpool> thread_pool);
  ~NTFSSearchHelper();

  void set_finish_call_back(call_back);
  void set_search_file_name(const std::vector<wstring>& file_name);
  bool start();
  void stop();

private:
  vector<wchar_t> get_disk_volumn() const;
  void FindFilesWithSameName(CNTFSVolumeSearcher* search, const wstring& file_name);
  bool is_started() const;

private:
  call_back _finished_cb = nullptr;
  std::vector<wstring> _files_name = {};
  //CNTFSVolumeSearcher	g_vSearcher;
  //CNTFSVolume* g_pSourceVolume = nullptr;
  std::map<CNTFSVolume*, CNTFSVolumeSearcher*> _map_ntfs_about = {};
  std::shared_ptr<std::threadpool> _workbranch_ptr;
  std::atomic_uint _thread_count = 0;
  std::mutex _mutex;
};

