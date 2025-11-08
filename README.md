Header-only C++ cache library providing flexible in-memory caching. 

# FlexiCache

Header-only C++17 LRU cache library.

## Features
- Single-header, policy-ready design (not implemented yet)
- No dependencies (STL only)
- Simple API: put/get, LRU eviction
- MIT licensed

## Requirements
- C++17 or newer
- CMake 3.14+

## Getting Started

### Clone the repository (including submodules):

```sh
git clone --recurse-submodules https://github.com/vladimirjojic/flexicache.git
cd flexicache
```

### Configure and build

Using CMake:

```sh
cmake -S . -B build
cmake --build build
```

Using command line (alternatively):
```
g++ -std=c++17 -Iinclude -o main src/main.cpp
./main
```

## Project Structure
```
flexicache/
├── include/
│   └── flexicache.hpp        # main header-only library
├── src/
│   └── main.cpp              # example binary
├── tests/
│   └── tests.cpp             # doctest unit tests
├── external/
│   └── doctest/              # test framework (git submodule)
├── LICENSE                   # MIT license
├── README.md
├── .gitignore
└── CMakeLists.txt            # build configuration
```

## Usage Example
```cpp
#include "flexicache.hpp"

int main() {
	FlexiCache<int, std::string> cache(2);
	cache.put(1, "one");
	cache.put(2, "two");
	if (auto v = cache.get(1)) {
		std::cout << *v << std::endl;
	}
}
```

## License
MIT, see [LICENSE](LICENSE).
