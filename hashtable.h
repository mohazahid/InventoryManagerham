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

/**
 * @brief 
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
    vector<std::unique_ptr<TableCell>> table;

    int hash(int);
    int hash(std::string);

public:

    HashTable<T>();
    HashTable<T>(int);

};
