/**
 * @file hashtable.h
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Header file for HashTable
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <vector>
#include <memory>


/**
 * @brief 
 * HashTable only stores pointers to objects
 * @tparam T value
 */
template <typename T>
class HashTable {

private:

    static const int DEFAULT_SIZE = 100; // if no size is given, a vector of 100 values is defined

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

    int size; // size of vector
    std::vector<std::unique_ptr<TableCell>> table;

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
    int hash(std::string key) {
        int sum = 0;
        for(char c : key) {
            sum += c;
        }
        return hash(sum);
    }

public:

    HashTable<T>() : size(DEFAULT_SIZE), table(100){}
    HashTable<T>(int size) : size(size), table(this->size){}

};
