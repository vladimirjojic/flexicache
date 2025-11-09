#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "flexicache.hpp"

TEST_CASE("replace existing entry when capacity is one")
{
    FlexiCache<int,int> fc(1);

    fc.put(1, 1);
    REQUIRE(fc.size() == 1);

    fc.put(2, 2);
    CHECK(fc.size() == 1);
    CHECK(fc.contains(1) == false);
    CHECK(fc.contains(2) == true);
}

TEST_CASE("simple test of put, contains, get")
{
    FlexiCache<int, int> fc(5);

    fc.put(1, 1);
    fc.put(2, 2);
    fc.put(3, 3);

    REQUIRE(fc.capacity() == 5);
    REQUIRE(fc.size() == 3);

    SUBCASE("cache contains added elements")
    {
        auto val1 = fc.contains(1);
        auto val2 = fc.contains(2);
        auto val3 = fc.contains(3);

        CHECK(val1 == true);
        CHECK(val2 == true);
        CHECK(val3 == true);
    }

    SUBCASE("cache returns added elements")
    {
        auto val1 = fc.get(1);
        auto val2 = fc.get(2);
        auto val3 = fc.get(3);

        CHECK(val1.value() == 1);
        CHECK(val2.value() == 2);
        CHECK(val3.value() == 3);
    }

    SUBCASE("values not added are not in the cache")
    {
        auto val = fc.get(99);

        CHECK(val.has_value() == false);
    }
}

TEST_CASE("overwrite and eviction (LRU behavior)")
{
    FlexiCache<int, int> fc(3);

    fc.put(1, 1);
    fc.put(2, 2);
    fc.put(3, 3);

    REQUIRE(fc.size() == 3);

    SUBCASE("overwrite existing key")
    {
        // adding existing key should update value and not change size
        fc.put(2, 20);
        auto v = fc.get(2);

        CHECK(fc.size() == 3);
        CHECK(v.has_value());
        CHECK(v.value() == 20);
    }

    SUBCASE("eviction respects recency (get updates recent)")
    {
        // access key 1 to mark it as recently used
        auto val = fc.get(1);
        REQUIRE(val.has_value());
        CHECK(val.value() == 1);

        // inserting a new element should evict the least-recently-used,
        // which is 2, as we have already accessed to 1
        fc.put(4, 4);

        CHECK(fc.size() == 3);
        CHECK(fc.contains(2) == false);
        CHECK(fc.contains(1) == true);
        CHECK(fc.contains(3) == true);
        CHECK(fc.contains(4) == true);
    }

    SUBCASE("contains does not update recency")
    {
        CHECK(fc.contains(1) == true);

        fc.put(4, 4);

        CHECK(fc.contains(1) == false);
        CHECK(fc.contains(4) == true);
    }
}
