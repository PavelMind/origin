#pragma once
#include <map>
#include <string>
#include <iostream>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept {
        return "Very Big Data String: " + key;
    }
};

class CacheProxyDB : VeryHeavyDatabase {
public:
    explicit CacheProxyDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {}
    std::string GetData(const std::string& key) noexcept {
        if (cache_.find(key) == cache_.end()) {
            std::cout << "Get from real object\n";
            cache_[key] = real_db_->GetData(key);
        }
        else {
            std::cout << "Get from cache\n";
        }
        return cache_.at(key);
    }

private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
};



class OneShotDB : VeryHeavyDatabase {
    VeryHeavyDatabase* real_db_;
    size_t maxCount;
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1) :
        real_db_(real_object), maxCount(shots) {
    }

    std::string GetData(const std::string& key) {
        if (maxCount > 0) {
            --maxCount;
            return real_db_->GetData(key);
        }
        else
            return std::string{ "error" };
    }
};