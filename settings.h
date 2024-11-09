#pragma once
#include "json/json.hpp"

#include <string>

using std::string;
using std::wstring;

using json = nlohmann::json;

class Settings {
public:
  Settings();
  ~Settings();
  Settings(const Settings& left) = delete;
  Settings& operator=(const Settings& left) = delete;

  string get_lang() const;
  void set_lang(const string& lang);
  bool get_auto_start() const;
  void set_auto_start(bool start);
  const std::vector<string> get_dbg_path() const;
  bool add_dbg_path(const string& path);

  bool save();

private:
  bool _load();

private:
  json _config;

  const string _config_name = "config.json";
};
