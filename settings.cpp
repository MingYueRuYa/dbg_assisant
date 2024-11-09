#pragma once
#include "settings.h"

#include <filesystem>
#include <fstream>

Settings::Settings() {
  this->_load();
}

Settings::~Settings()
{
  this->save();
}

std::string Settings::get_lang() const {
  if (_config.is_null() || !_config.contains("lang")) {
    return "zh_CN";
  }
  else {
    return _config["lang"];
  }
}

void Settings::set_lang(const string& lang) {
  _config["lang"] = lang;
  this->save();
}

bool Settings::get_auto_start() const {
  if (_config.is_null() || !_config.contains("auto_start")) {
    return false;
  }
  else {
    return _config["auto_start"];
  }
}

void Settings::set_auto_start(bool start) {
  _config["auto_start"] = start;
  this->save();
}

const std::vector<string> Settings::get_dbg_path() const
{
  if (!_config.contains("dbg_path"))
  {
    return {};
  }

  return _config["dbg_path"];
}

bool Settings::add_dbg_path(const string& path)
{
  if (path.empty())
  {
    return false;
  }

  auto paths = _config["dbg_path"];
  for (auto& item : paths) {
    if (path == item) {
      return false;
    }
  }
  _config["dbg_path"].push_back(path);
  this->save();
  return true;
}

bool Settings::save() {
  std::ofstream o(this->_config_name);
  o << std::setw(4) << _config << std::endl;
  return true;
}

bool Settings::_load() {
  if (!std::filesystem::exists(this->_config_name)) {
    return false;
  }

  std::ifstream f(this->_config_name);
  _config = json::parse(f);
  return true;
}
