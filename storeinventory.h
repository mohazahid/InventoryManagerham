/**
 * @file storeinventory.h
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Header file for StoreInventory
 * @date 2022-05-18
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <set>
#include <limits> // used for fstream numeric limit
#include <sstream>
#include <queue>
#include <algorithm>
#include "hashtable.tpp"
#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"


class StoreInventory{

private:


    /**
     * @brief Operations StoreInventory can make
     */
    enum Operation {
        Borrow = 'B',
        Return = 'R',
        Inventory = 'I',
        History = 'H'
    };

    struct Customer {
        int custID; // 4 digit ID
        std::string custFirst; // Customer first name
        std::string custLast; // Customer last name
        bool operator<(const Customer& rhs) const {
            return this->custID < rhs.custID;
        }    
    };

    /**
     * @brief Contains information about a given transaction
     */
    struct Log {
        Operation type; // 'B' or 'R'
        Customer customer; // Contains information about the customer
        Movie movie; // Contains information about the movie 
        
        friend std::ostream& operator<<(std::ostream& os, const Log& log){
            return os<< log.type << std::endl;
        }
    };

    
    std::set<Customer> customers; // stores customers
    HashTable<Log> transactions; // key is custID
    HashTable<Movie> inventory; // key is director + title

    /**
     * @brief Inserts a Log into transactions and modifies the corresponding stock  
     * @param transaction Transaction to insert
     * @pre Movie must exist in inventory
     * @pre custID must exist in transactions
     * @return true If insertion is successful.
     * @return false If 'Log.type' is 'B' and the corresponding stock is less than 1
     * @return false If 'movie' does not 
     */
    bool transact(Log&);
    /**
     * @brief Prints a sorted inventory
     * @details prints in the order of #TODO 
     */
    void printInventory() const;
    /**
     * @brief Prints the transactions of a customer
     * @param custID custID of customer
     */
    void printTransactions(int) const;

    bool isValid(int) const;

public:

    /**
     * @brief Construct a new Store Inventory object
     * @param customers std::ifstream of customers to insert into transactions
     * @param movies std::ifstream of movies to insert into inventory
     */
    StoreInventory(std::ifstream&, std::ifstream&);
    /**
     * @brief Runs all the provided commands
     * @details Invalid commands will be skipped
     * @param filename std::ifstream of commands to run
     */
    void operate(std::ifstream&);

};