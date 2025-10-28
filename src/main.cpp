#include <iostream>
#include "flexicache.hpp"

int main()
{
    FlexiCache<int, std::string> cache(2);

    cache.put(1, "one");
    cache.put(2, "two");

    if (auto v = cache.get(1))
    {
        std::cout << "1: " << *v << std::endl;
    }

    cache.put(3, "three"); // add key 3, key 2 will be evicted

    if (auto v = cache.get(2))
    {
        std::cout << "2: " << *v << std::endl;
    }
    else
    {
        std::cout << "2 is not in the cache" << std::endl;
    }

    return 0;
}
