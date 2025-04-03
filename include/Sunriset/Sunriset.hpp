// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#ifndef __SUNRISET_HPP
#define __SUNRISET_HPP

#include <filesystem>
#include <string>
#include <Sunriset/version.h>

extern "C" {
#include "Sunriset/sunriset.h"
}

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

    void showSunriset (int year, int month, int day, double lon, double lat);

    void getSunriset (int year, int month, int day, double lon, double lat, double& rise,
                        double& set) {
      sun_rise_set (year, month, day, lon, lat, &rise, &set);
    }
  };

} // namespace dotname

#endif // __SUNRISET_HPP