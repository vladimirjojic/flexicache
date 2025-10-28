/*
 * flexicache.hpp
 *
 * Copyright (c) 2025 Vladimir Jojic
 * SPDX-License-Identifier: MIT
 *
 * - Header-only cache library.
 * - No external dependencies; C++17 required.
 * - Core library avoids exceptions and RTTI.
 *
 * This file contains the public API and implementation for FlexiCache.
 */

#ifndef FLEXICACHE_INCLUDE_FLEXICACHE_H
#define FLEXICACHE_INCLUDE_FLEXICACHE_H

#include <unordered_map>
#include <list>
#include <optional>

template <typename Key, typename Value>
class FlexiCache
{
public:
    FlexiCache(size_t capacity) : capacity_(capacity) {}

    void put(const Key &k, const Value &v)
    {
        const auto &it = cache_.find(k);

        if (it != cache_.end())
        {
            auto const &list_it = std::find(list_.begin(), list_.end(), k);
            list_.erase(list_it);
        }

        if (list_.size() >= capacity_)
        {
            const auto &old_key = list_.back();
            list_.pop_back();
            cache_.erase(old_key);
        }

        list_.push_front(k);
        cache_[k] = v;
    }

    const std::optional<Value> get(const Key &k)
    {
        if (this->contains(k))
        {
            auto it = std::find(list_.begin(), list_.end(), k);
            if (it != list_.end())
            {
                list_.erase(it);
                list_.push_front(k);
            }

            return cache_[k];
        }

        return std::nullopt;
    }

    bool contains(const Key &k) const
    {
        return cache_.find(k) != cache_.end();
    }

private:
    size_t capacity_;
    std::unordered_map<Key, Value> cache_;
    std::list<Key> list_;
};

#endif // FLEXICACHE_INCLUDE_FLEXICACHE_H
