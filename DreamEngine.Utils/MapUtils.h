#pragma once

#include <map>

class MapUtils
{

public:

    template<class K, class V>
    static V TryGetByKey(const std::map<K, V>& map, K key, V def)
    {
        auto res = map.find(key);
        if (res == map.end()) return def;

        return res->second;
    }

    template<class K, class V>
    static K TryGetByValue(const std::map<K, V>& map, V value, K def)
    {
        for (auto mapIter : map)
        {
            if (mapIter.second == value)
                return mapIter.first;
        }

        return def;
    }

};

