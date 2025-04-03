// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#ifndef __SUNRISET_HPP
#define __SUNRISET_HPP

#include <filesystem>
#include <string>
#include <Sunriset/version.h>

// Public API

namespace dotname {

  class Sunriset {

    const std::string libName = std::string ("Sunriset v.") + SUNRISET_VERSION;
    std::filesystem::path assetsPath_;

  public:
    Sunriset ();
    Sunriset (const std::filesystem::path& assetsPath);
    Sunriset (int year, int month, int day, double lon, double lat);
    ~Sunriset ();

    const std::filesystem::path getAssetsPath () const {
      return assetsPath_;
    }
    void setAssetsPath (const std::filesystem::path& assetsPath) {
      assetsPath_ = assetsPath;
    }

    void showSunriseSet (int year, int month, int day, double lon, double lat);
  };

} // namespace dotname

#endif // __SUNRISET_HPP