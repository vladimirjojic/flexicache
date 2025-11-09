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
#include <algorithm>

template <typename Key, typename Value>
class FlexiCache
{
public:
    FlexiCache(size_t capacity) : capacity_(capacity) {}

    void put(const Key &k, const Value &v) noexcept
    {
        if (capacity_ == 0)
            return;

        auto it = cache_.find(k);
        if (it != cache_.end())
        {
            list_.erase(it->second.second);
            list_.push_front(k);
            it->second = {v, list_.begin()};
            return;
        }

        if (list_.size() >= capacity_)
        {
            const auto &old_key = list_.back();
            cache_.erase(old_key);
            list_.pop_back();
        }

        list_.push_front(k);
        cache_[k] = {v, list_.begin()};
    }

    const std::optional<Value> get(const Key &k) noexcept
    {
        auto it = cache_.find(k);
        if (it == cache_.end())
            return std::nullopt;

        list_.splice(list_.begin(), list_, it->second.second);
        return it->second.first;
    }

    bool contains(const Key &k) const 
    {
        return cache_.find(k) != cache_.end();
    }


    size_t size() const noexcept
    {
        return cache_.size();
    }

    size_t capacity() const noexcept
    {
        return capacity_;
    }

private:
    size_t capacity_;
    std::unordered_map<Key, std::pair<Value, typename std::list<Key>::iterator>> cache_;
    std::list<Key> list_;
};

#endif // FLEXICACHE_INCLUDE_FLEXICACHE_H
