<img src="assets/logo.png" alt="DotNameCpp Logo" width="20%">

[![Linux](https://github.com/tomasmark79/SunrisetFree/actions/workflows/linux.yml/badge.svg)](https://github.com/tomasmark79/SunrisetFree/actions/workflows/linux.yml)
[![MacOS](https://github.com/tomasmark79/SunrisetFree/actions/workflows/macos.yml/badge.svg)](https://github.com/tomasmark79/SunrisetFree/actions/workflows/macos.yml)
[![Windows](https://github.com/tomasmark79/SunrisetFree/actions/workflows/windows.yml/badge.svg)](https://github.com/tomasmark79/SunrisetFree/actions/workflows/windows.yml)  

# SunrisetFree

Implementation of highly accurate sunrise and sunset calculations, with preparation for additional astrological computations. Ready for further extensions.

## Example
```bash
./SunrisetFree -y 2025 -m 4 -d 2 -l 49.86396819090531 -g 14.265802152828646
```

## Usage
```bash
Starting SunrisetFree ...
SunrisetFree
Usage:
  ./build/standalone/default/debug/./SunrisetFree [OPTION...]

  -h, --help           Show help
  -o, --omit           Omit library loading
  -2, --log2file       Log to file
  -y, --year arg       YEAR (default: 2025)
  -m, --month arg      MONTH (default: 4)
  -d, --day arg        DAY (default: 2)
  -g, --longitude arg  LONGITUDE (default: 14.265802152828646)
  -l, --latitude arg   LATITUDE (default: 49.86396819090531)
```

## References 

original algo core by these guys   
Written as DAYLEN.C, 1989-08-16  
Modified to SUNRISET.C, 1992-12-01  
(c) Paul Schlyter, 1989, 1992  

---

<img src="assets/logo.png" alt="DotNameCpp Logo" width="20%">

**[DotName C++ Template](https://github.com/tomasmark79/DotNameCppFree)** – A fast and practical starting point for modern C++ development! 🏗️ This template ensures a solid foundation with pre-configured settings, modular structure, and compatibility across platforms. Boost your workflow and deliver quality code. 🌈

## License

MIT License  
Copyright (c) 2024-2025 Tomáš Mark

[👆🏻](#sunriset)