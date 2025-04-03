// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include "Logger/Logger.hpp"
#include "Utils/Utils.hpp"
#include "Sunriset/Sunriset.hpp"

#include <cxxopts.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Config {
  constexpr char standaloneName[] = "SunrisetApp";
  const std::filesystem::path executablePath = Utils::FSManager::getExecutePath ();
  constexpr std::string_view utilsAssetPath = UTILS_ASSET_PATH;
  constexpr std::string_view utilsFirstAssetFile = UTILS_FIRST_ASSET_FILE;
  const std::filesystem::path assetsPath = executablePath / utilsAssetPath;
  const std::filesystem::path assetsPathFirstFile = assetsPath / utilsFirstAssetFile;
}

std::unique_ptr<dotname::Sunriset> uniqueLib;

int processArguments (int argc, const char* argv[]) {
  try {
    auto options = std::make_unique<cxxopts::Options> (argv[0], Config::standaloneName);
    options->positional_help ("[optional args]").show_positional_help ();
    options->set_width (80);
    options->set_tab_expansion ();
    options->add_options () ("h,help", "Show help");
    options->add_options () ("o,omit", "Omit library loading",
                             cxxopts::value<bool> ()->default_value ("false"));
    options->add_options () ("2,log2file", "Log to file",
                             cxxopts::value<bool> ()->default_value ("false"));

    options->add_options () ("y,year", "YEAR", cxxopts::value<int> ()->default_value ("2025"));
    options->add_options () ("m,month", "MONTH", cxxopts::value<int> ()->default_value ("4"));
    options->add_options () ("d,day", "DAY", cxxopts::value<int> ()->default_value ("2"));

    options->add_options () ("g,longitude", "LONGITUDE",
                             cxxopts::value<double> ()->default_value ("14.265802152828646"));

    options->add_options () ("l,latitude", "LATITUDE",
                             cxxopts::value<double> ()->default_value ("49.86396819090531"));

    const auto result = options->parse (argc, argv);

    if (result.count ("help")) {
      LOG_I << options->help ({ "", "Group" }) << std::endl;
      return 0;
    }

    if (result["log2file"].as<bool> ()) {
      LOG.enableFileLogging (std::string (Config::standaloneName) + ".log");
      LOG_D << "Logging to file enabled [-2]" << std::endl;
    }

    if (!result.count ("omit")) {
      // uniqueLib = std::make_unique<dotname::Sunriset> ();
      // uniqueLib = std::make_unique<dotname::Sunriset> (Config::assetsPath);
      uniqueLib = std::make_unique<dotname::Sunriset> (
          result["year"].as<int> (), result["month"].as<int> (), result["day"].as<int> (),
          result["longitude"].as<double> (), result["latitude"].as<double> ());

    } else {
      LOG_D << "Loading library omitted [-o]" << std::endl;
    }

    if (!result.unmatched ().empty ()) {
      for (const auto& arg : result.unmatched ()) {
        LOG_E << "Unrecognized option: " << arg << std::endl;
      }
      LOG_I << options->help () << std::endl;
      return 1;
    }

  } catch (const cxxopts::exceptions::exception& e) {
    LOG_E << "error parsing options: " << e.what () << std::endl;
    return 1;
  }
  return 0;
}

int main (int argc, const char* argv[]) {
  LOG.noHeader (true);
  LOG_D << "Starting " << Config::standaloneName << " ..." << std::endl;
  if (processArguments (argc, argv) != 0) {
    return 1;
  }
  return 0;
}