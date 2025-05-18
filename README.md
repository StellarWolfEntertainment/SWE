[![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/StellarWolfEntertainment/swe/build.yml?branch=main)](https://github.com/StellarWolfEntertainment/swe/actions/workflows/build.yml)
[![Version](https://img.shields.io/github/v/release/StellarWolfEntertainment/swe)](https://github.com/StellarWolfEntertainment/swe/releases)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE.md)
[![GitHub issues](https://img.shields.io/github/issues/StellarWolfEntertainment/swe)](https://github.com/StellarWolfEntertainment/swe/issues)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/StellarWolfEntertainment/swe)](https://github.com/StellarWolfEntertainment/swe/pulls)
![C++ Version](https://img.shields.io/badge/C%2B%2B%20Version-c%2B%2B11-blue)
![Platform](https://img.shields.io/badge/platform-cross--platform-brightgreen)

# SWE Library

**Stellar Wolf Entertainment (SWE) C++ Utility Library**

This library provides a collection of reusable, efficient, and type-safe C++ utilities for modern projects. It is designed to be modular, lightweight, and easy to integrate into your own codebase.

## Table of Contents

- [Features](#features)
- [Usage](#usage)
- [Build & Test](#build--test)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)
- [Notes](#notes)

## Features

- **String Utilities**  
  Case conversion, trimming, splitting, joining, comparison, and formatting for both `std::string` and `std::wstring`.  
  See [`include/swe/string.hpp`](include/swe/string.hpp).

- **Case-Insensitive Maps**  
  Drop-in replacements for `std::map` and `std::unordered_map` with case-insensitive string or wstring keys.  
  See [`include/swe/ci_map.hpp`](include/swe/ci_map.hpp).

- **Static Event System**  
  Lightweight, type-safe event system for static/free function callbacks, with encapsulation similar to C# events.  
  See [`include/swe/static_event.hpp`](include/swe/static_event.hpp).

- **Thread-Safe Static Events**  
  Like the static event system, but with mutex protection for safe concurrent use.  
  See [`include/swe/concurrent_static_event.hpp`](include/swe/concurrent_static_event.hpp).

## Usage

Include the relevant header(s) in your project:

```cpp
#include <swe/string.hpp>
#include <swe/ci_map.hpp>
#include <swe/static_event.hpp>
#include <swe/concurrent_static_event.hpp>
```
All utilities are in the `swe` namespace.

### Example

```cpp
#include <swe/string.hpp>
#include <iostream>

int main() {
    std::string s = "  Hello, SWE!  ";
    std::cout << swe::trim(s) << std::endl; // Output: "Hello, SWE!"
    return 0;
}
```

## Build & Test

This project uses CMake.

```sh
git clone https://github.com/StellarWolfEntertainment/swe.git
cd swe
cmake -B build
cmake --build build
ctest --test-dir build
```

## Documentation

- Generated documentation is available in the `docs/` directory.
- To generate docs locally, run:
  ```sh
  doxygen
  ```

## Contributing

Contributions are welcome! Please open issues or pull requests. See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## License

[MIT License](LICENSE.md).

## Notes

This project is a perpetual work in progress, and I do welcome contributions.

---
Created by Stellar Wolf Entertainment (SWE).
