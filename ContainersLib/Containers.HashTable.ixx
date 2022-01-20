module;
#include <iostream>
#include <vector>
#include <string>

export module Containers:HashTable;

namespace Containers {
    template<class K, class V>
    struct Bucket {
        K key;
        V val;
        Bucket(const K& k, const V& v) : val(v), key(k) {}
    };

    template<class T> struct myHash {
    };

    template<> struct myHash<std::string> {
        static size_t hashFunction(const std::string& s) {
            return std::hash<std::string>()(s);
        }
    };

    template<> struct myHash<int> {
        static size_t hashFunction(const int m) {
            return std::hash<int>()(m);
        }
    };

    export template<class K, class V, class HashGenerator = myHash<K> >
    class HashTable {
    public:
        std::vector<std::vector<Bucket<K, V> > > table;
        HashTable(int size) {
            for (int i = 0; i < size; i++) {
                std::vector<Bucket<K, V> > v;
                table.push_back(v);
            }
        }
        ~HashTable() {}
        void set(const K& k, const V& v) {
            Bucket<K, V> b(k, v);
            for (int i = 0; i < table[hash(k)].size(); i++)
                if (table[hash(k)][i].key == k) {
                    table[hash(k)][i] = b;
                    return;
                }
            table[hash(k)].push_back(b);
        }
        V get(const K& k) {
            for (int i = 0; i < table[hash(k)].size(); i++)
                if (table[hash(k)][i].key == k)
                    return table[hash(k)][i].val;
        }
        bool exist(const K& k) {
            for (int i = 0; i < table[hash(k)].size(); i++)
                if (table[hash(k)][i].key == k)
                    return true;
            return false;
        }
        size_t hash(const K& k) {
            return HashGenerator::hashFunction(k) % table.size();
        }
    };
}