# `libKCD1`
[![C++17](https://img.shields.io/static/v1?label=standard&message=C%2B%2B17&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
[![Platform](https://img.shields.io/static/v1?label=platform&message=windows&color=dimgray&style=flat)](#)

Reverse-engineered headers and runtime library for **Kingdom Come: Deliverance 1** (CryEngine 3 + Warhorse modules). Includes **KCSE** (Kingdom Come Script Extender) — an SKSE-style native plugin framework.

> This is a hobby project. Not every RE'd member is guaranteed correct — verify before use. Contributions welcome.

## Build Dependencies

- [spdlog](https://github.com/gabime/spdlog)
- [Visual Studio 2022+](https://visualstudio.microsoft.com/)
  - Desktop development with C++
- [CMake 3.15+](https://cmake.org/)
- [vcpkg](https://github.com/microsoft/vcpkg)

## End User Dependencies

- [Kingdom Come: Deliverance 1](https://store.steampowered.com/app/379430/Kingdom_Come_Deliverance/)

## Notes

- libKCD1 targets game version **1.9.7.0**. CryEngine's interfuscator shuffles vtable order in release builds — SDK headers cannot be used for direct virtual calls across versions.

## Acknowledgements

Inspired by [SKSE](https://skse.silverlock.org/) and [CommonLibSSE](https://github.com/powerof3/CommonLibSSE).

## License

[GPLv3](LICENSE)
