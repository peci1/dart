# Design

## High Level Design Decisions

- Project name: DART
- Language: C++17
- Build tool: CMake >= 3.10.2
- Supported environments
  - Ubuntu
    - Distros: 18.04, 20.04, and the latest non-LTS distro (e.g., 21.04)
    - Platforms: amd64, arm64, ppc64le, and s390x
    - Compilers: GCC, Clang
  - Archlinux (todo)
    - Compilers: GCC
  - macOS
    - Compilers: Clang
  - Windows
    - Compilers: MSVC 2019

## Misc

- Prefer signed integer over unsigned integer

## Requirements

- DART shall allow installing multiple DART major versions alongside.
