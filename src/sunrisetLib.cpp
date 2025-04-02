// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include <Logger/Logger.hpp>
#include <Utils/Utils.hpp>
#include <sunrisetLib/sunrisetLib.hpp>

extern "C" {
#include "Sunriset/sunriset.h"
}

namespace dotname {

  sunrisetLib::sunrisetLib () {
    LOG_D << libName << " ...constructed" << std::endl;
    if (!assetsPath_.empty ()) {
      LOG_D << "Assets path: " << assetsPath_ << std::endl;
    } else {
      LOG_D << "Assets path is empty" << std::endl;
    }
  }
  sunrisetLib::sunrisetLib (const std::filesystem::path& assetsPath) : sunrisetLib () {
    assetsPath_ = assetsPath;
  }
  sunrisetLib::sunrisetLib (int year, int month, int day, double lon, double lat) : sunrisetLib () {
    showSunriseSet (year, month, day, lon, lat);
  }
  sunrisetLib::~sunrisetLib () {
    LOG_D_DESTRUCTOR (sunrisetLib) << libName << " ...destructed" << std::endl;
  }

  void sunrisetLib::showSunriseSet (int year, int month, int day, double lon, double lat) {
    double rise = 0.0;
    double set = 0.0;
    sun_rise_set (year, month, day, lon, lat, &rise, &set);
    int riseHour = static_cast<int> (rise);
    int riseMinute = static_cast<int> ((rise - riseHour) * 60);
    int setHour = static_cast<int> (set);
    int setMinute = static_cast<int> ((set - setHour) * 60);

    /* parse output for required tool */
    LOG_I << "DOTNAME " << riseHour << ":" << (riseMinute < 10 ? "0" : "") << riseMinute << " "
          << setHour << ":" << (setMinute < 10 ? "0" : "") << setMinute << std::endl;
  }

} // namespace dotname