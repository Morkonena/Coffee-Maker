//
// Created by M�rk�nen� on 14.7.2018
//

#ifndef CORE_STANDARD_H
#define CORE_STANDARD_H

#include <assert.h>
#include <algorithm>
#include <atomic>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>
#include <utility>

#define ASSERT(X) assert(X)

template<typename T>
using Function = std::function<T>;

template<typename T>
using Parameters = std::initializer_list<T>;

template<typename K, typename T>
using Map = std::map<K, T>;

typedef std::mutex Lock;

template<typename K>
using Set = std::set<K>;

typedef std::string String;

template<typename T>
using List = std::vector<T>;

template<typename T>
using Managed = std::unique_ptr<T>;

typedef unsigned int uint;
typedef unsigned char byte;

template<typename A, typename B>
using Pair = std::pair<A, B>;

#endif // !CORE_STANDARD_H
