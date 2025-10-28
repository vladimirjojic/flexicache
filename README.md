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

## Build
```sh
mkdir build
cd build
cmake ..
cmake --build .
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
