// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include <Logger/Logger.hpp>
#include <Utils/Utils.hpp>
#include <Sunriset/Sunriset.hpp>

namespace dotname {

  Sunriset::Sunriset () {
    LOG_D_STREAM << libName << " ...constructed" << std::endl;
    if (!assetsPath_.empty ()) {
      LOG_D_STREAM << "Assets path: " << assetsPath_ << std::endl;
    } else {
      LOG_D_STREAM << "Assets path is empty" << std::endl;
    }
  }
  Sunriset::Sunriset (const std::filesystem::path& assetsPath) : Sunriset () {
    assetsPath_ = assetsPath;
  }

  std::string Sunriset::doubleTo24Time (double time) {
    int hour = static_cast<int> (time);
    int minute = static_cast<int> ((time - hour) * 60);
    std::string timeString
        = std::to_string (hour) + ":" + (minute < 10 ? "0" : "") + std::to_string (minute);
    return timeString;
  }

  Sunriset::Sunriset (int year, int month, int day, double lon, double lat) : Sunriset () {

    double rise = 0.0;
    double set = 0.0;

    getSunriset (year, month, day, lon, lat, rise, set);

    LOG_I_STREAM << "Sunrise: " << doubleTo24Time (rise) << " "
                 << "Sunset: " << doubleTo24Time (set) << std::endl;
  }
  Sunriset::~Sunriset () {
    LOG_D_STREAM << libName << " ...destructed" << std::endl;
  }

} // namespace dotname