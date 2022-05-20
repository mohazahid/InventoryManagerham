/**
 * @file hashtable.h
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Template file for HashTable
 * @date 2022-05-18
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <vector>
#include <memory>

/**
 * @brief 
 * Prevents hash conflicts by storing new values as a list
 * @tparam T 
 */
template <typename T>
struct TableCell {
    std::unique_ptr<T> value; // value storted in hash table
    std::unique_ptr<TableCell> next; // 
};

/**
 * @brief 
 * HashTable only stores pointers to objects
 * @tparam T value
 */
template <typename T>
class HashTable {

private:

    static const int DEFAULT_SIZE = 100; // if no size is given, a vector of 100 values is defined

    int size; // size of vector
    std::vector<std::unique_ptr<TableCell<T>>> table;

    /**
     * @brief Hashs the key and returns the corresponding table index
     * @param key value to hash
     * @return index in table
     */
    int hash(int key) {
        return key % this->size;
    }

    /**
     * @brief Converts a string to an integer to be hashed
     * @details returns hash(int)
     * @param key value to hash
     * @return index in table
     */
    int stringToKey(std::string key) {
        int sum = 0;
        for(char c : key) {
            sum += c;
        }
        return sum;
    }

public:
    
    HashTable<T>() : size(DEFAULT_SIZE) {
        for(int i = 0; i < this->size; ++i) {
            this->table.push_back(std::make_unique<TableCell<T>>());
        }
    }
    HashTable<T>(int size) : size(size) {
        for(int i = 0; i < this->size; ++i) {
            this->table.push_back(std::make_unique<TableCell<T>>());
        }
    }

    /**
     * @brief Inserts the value at the key's location
     * @param key Key to hash
     * @param value Value to insert into table
     */
    void put(int key, const T& val) {
        int idx = hash(key);
        // Insert cell at head
        TableCell<T>* cur = table.at(idx).get();
        while(!(cur->next == nullptr)) {
            cur = cur->next.get();
        }
        if(cur->value == nullptr) {
            cur->value = std::make_unique<T>(val);
            cur->next = std::make_unique<TableCell<T>>();
        }
        // Hash conflict
    }
    /**
     * @brief Inserts the value at the key's location
     * @details Converts std::string into an int value 
     * @param key Key to hash
     * @param value Value to insert into table
     */
    void put(std::string key, const T& value) { put(stringToKey(key), value); }
 
    // std::list<T> get(int key) {
    //     std::list<T> out;
    //     auto cur = table.at(hash(key))->value;
    //     while(cur != nullptr) {
    //         out.push_back(cur->value);
    //         cur = cur->next;
    //     }
    //     return out;
    // }
    // std::list<T> get(std::string key) { return get(stringToKey(key)); }
 
    // bool remove(int key, T) {

    // }

};
