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
#include <list>

/**
 * @brief Stores values according to a hash function
 * @details HashTable only stores pointers to objects
 * @tparam T value
 */
template <typename T>
class HashTable {

private:

    static const int DEFAULT_SIZE = 100; // if no size is given, a vector of 100 values is defined

    int size; // size of vector
    std::vector<std::list<T>> table; // vector of points

    /**
     * @brief Hashs the key and returns the corresponding table index
     * @param key value to hash
     * @return index in table
     */
    int hash(int key) const {
        return key % this->size;
    }
    /**
     * @brief Converts a string to an integer to be hashed
     * @details returns hash(int)
     * @param key value to hash
     * @return index in table
     */
    int stringToKey(std::string key) const {
        int sum = 0;
        for(char c : key) {
            sum += c;
        }
        return sum;
    }

public:
    
    HashTable<T>() : size(DEFAULT_SIZE), table(this->size){}
    HashTable<T>(int size) : size(size), table(this->size){}

    /**
     * @brief Inserts the value at the key's location
     * @param key Key to hash
     * @param value Value to insert into table
     */
    void put(int key, const T& val) {
        int idx = hash(key);
        table.at(idx).push_back(val);
    }
    /**
     * @brief Inserts the value at the key's location
     * @details Converts std::string into an int value 
     * @param key Key to hash
     * @param value Value to insert into table
     */
    void put(std::string key, const T& value) {
        put(stringToKey(key), value);
    }
 
    /**
     * @brief Returns a list of all values stored at the given key
     * @param key Key to hash
     * @return std::list<T> 
     */
    std::list<T> get(int key) const {
        return table.at(hash(key));
    }
    /**
     * @brief Returns a list of all values stored at the given key
     * @details Converts the key into an int
     * @param key Key to hash
     * @return std::list<T> 
     */
    std::list<T> get(std::string key) const {
        return get(stringToKey(key));
    }

    /**
     * @brief Removes all values stored with the given key
     * @param key Key to hash
     */
    void remove(int key) {
        this->table.at(hash(key)).clear();        
    }
    /**
     * @brief Removes all values stored with the given key
     * @param key Key to hash
     */
    void remove(std::string key) {
        remove(stringToKey(key));
    }

    /**
     * @brief Removes the given value with the given key
     * @param key Key to hash
     * @param val Value to remove
     */
    void remove(int key, T& val) {
        this->table.at(hash(key)).remove(val);
    }
    /**
     * @brief Removes the given value with the given key
     * @param key Key to hash
     * @param val Value to remove
     */
    void remove(std::string key, T& val) {
        remove(stringToKey(key), val);
    }

};
