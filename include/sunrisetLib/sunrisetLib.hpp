// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#ifndef __SUNRISETLIB_HPP
#define __SUNRISETLIB_HPP

#include <filesystem>
#include <string>
#include <sunrisetLib/version.h>

// Public API

namespace dotname {

  class sunrisetLib {

    const std::string libName = std::string ("sunrisetLib v.") + SUNRISETLIB_VERSION;
    std::filesystem::path assetsPath_;

  public:
    sunrisetLib ();
    sunrisetLib (const std::filesystem::path& assetsPath);
    sunrisetLib (int year, int month, int day, double lon, double lat);
    ~sunrisetLib ();

    const std::filesystem::path getAssetsPath () const {
      return assetsPath_;
    }
    void setAssetsPath (const std::filesystem::path& assetsPath) {
      assetsPath_ = assetsPath;
    }

    void showSunriseSet (int year, int month, int day, double lon, double lat);
  };

} // namespace dotname

#endif // __SUNRISETLIB_HPP