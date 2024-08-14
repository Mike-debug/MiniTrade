//
// Created by Caesar on 4/4/24.
//

#ifndef CXX002_COMMONUTILS_H
#define CXX002_COMMONUTILS_H

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <bitset>


template<typename T>
void printVector(const std::vector<T> v) {
    for (auto e: v) {
        std::cout << e << "; ";
    }
    std::cout << std::endl;
}

template<typename T>
void printSet(const std::set<T> v) {
    for (auto e: v) {
        std::cout << e << "; ";
    }
    std::cout << std::endl;
}

template<typename T>
void printSet(const std::unordered_set<T> v) {
    for (auto e: v) {
        std::cout << e << "; ";
    }
    std::cout << std::endl;
}

template<typename K, typename V>
void printMap(const std::map<K, V> m) {
    std::cout << "{" << std::endl;
    for (auto mt = m.begin(); mt != m.end(); ++mt) {
        std::cout << "    " << mt->first << ": " << mt->second << ";" << std::endl;
    }
    std::cout << "}" << std::endl << std::endl;
}


template<typename K, typename V>
void printMap(const std::unordered_map<K, V> m) {
    std::cout << "{" << std::endl;
    for (auto mt = m.begin(); mt != m.end(); ++mt) {
        std::cout << "    " << mt->first << ": " << mt->second << ";" << std::endl;
    }
    std::cout << "}" << std::endl << std::endl;
}

template<typename K, typename V>
std::set<K> getSet(const std::map<K, V> &m) {
    std::set<K> ks{};
    for (auto mt = m.begin(); mt != m.end(); ++mt) {
        ks.insert(mt->first);
    }
    return ks;
}

template<typename K, typename V>
std::unordered_set<K> getSetFromMap(const std::unordered_map<K, V> &m) {
    std::unordered_set<K> ks{};
    for (auto mt = m.begin(); mt != m.end(); ++mt) {
        ks.insert(mt->first);
    }
    return ks;
}

template<typename T>
void printPriorityQueue(const std::priority_queue<T, std::vector<T>, std::less<T>> pq) {
    auto cpy = pq;
    while (!cpy.empty()) {
        std::cout << cpy.top() << "; ";
        cpy.pop();
    }
    std::cout << std::endl;
}

template<typename T>
void printPriorityQueue(const std::priority_queue<T, std::vector<T>, std::greater<T>> pq) {
    auto cpy = pq;
    while (!cpy.empty()) {
        std::cout << cpy.top() << "; ";
        cpy.pop();
    }
    std::cout << std::endl;
}

template<typename T>
void printVecVec(const std::vector<std::vector<T>> v) {
    for (auto e: v) {
        printVector(e);
    }
    std::cout << std::endl;
}

template<size_t N>
void printBitSet(std::bitset<N> bitSet) {
    std::cout << "--------------------bitset-------------------" << std::endl;
    std::cout << bitSet << std::endl;
    std::cout << bitSet.size() << std::endl;
    std::cout << bitSet.count() << std::endl;
    std::cout << std::endl;
}

template<typename T1, typename T2>
void printPair(std::pair<T1, T2> p) {
    std::cout << "{ " << p.first << ", " << p.second << " }" << std::endl;
}

#endif //CXX002_COMMONUTILS_H
