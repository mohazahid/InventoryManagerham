/**
 * @file storeinventory.h
 * @author 
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (oahmed@uw.edu)
 * @brief Header file for StoreInventory
 * @date 2022-05-18
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <string>
#include <list>
#include <set>

#include <algorithm>
#include <memory>

#include "hashtable.tpp"
#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"

/**
 * @brief Manages the inventory for a movie store
 * Contains a set of valid customers
 * Contains a hashtable of movies
 * Contains a hashtable of previous transactions
 */
class StoreInventory {

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

    /**
     * @brief Contains information about a customer
     */
    struct Customer {
        int custID; // 4 digit ID
        std::string custFirst; // Customer first name
        std::string custLast; // Customer last name
        bool operator<(const Customer& rhs) const {
            return this->custID < rhs.custID;
        }    
        friend std::ostream& operator<<(std::ostream& out, const Customer& c){
            return out << c.custID << ' ' << c.custFirst << ' ' << c.custLast << '\n';
        }
    };

    /**
     * @brief Contains information about a transaction
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
    HashTable<Log> transactions; // key depends on movie type
    HashTable<std::shared_ptr<Movie>> inventory; // key is director + title

    /**
     * @brief Inserts a Log into transactions and modifies the corresponding stock  
     * @param transaction Transaction to insert
     * @pre Movie must exist in inventory
     * @pre custID must exist in transactions
     * @return true If insertion is successful.
     * @return false If 'Log.type' is 'B' and the corresponding stock is less than 1
     * @return false If 'movie' does not exist in inventory
     */
    bool transact(Log&);

    /**
     * @brief Prints all valid customers and their IDs
     * @param out Stream to output to.
     */
    void printCustomers(std::ostream&) const;
    /**
     * @brief Prints a sorted inventory
     * @details prints in the order depending on Movie's sorting attributes 
     * @param out Stream to output to.
     */
    void printInventory(std::ostream&) const;
    /**
     * @brief Prints the transactions of a customer
     * @param out Stream to output to.
     * @param custID custID of customer
     */
    void printTransactions(std::ostream&, int) const;
    /**
     * @brief Prints all transatcions
     * @param out Stream to output to.
     */
    void printTransactions(std::ostream&) const;

    /**
     * @brief Determines if a customer ID is valid.
     * @return true if ID exists in 'customers'
     * @return false if ID does not exist in 'customers'
     */
    bool isValid(int) const;

    /**
     * @brief Inputs all valid customers from a file stream.
     * @param in File stream to input from
     */
    void setCustomers(std::ifstream&);
    /**
     * @brief Inputs all movies in stock from a file stream
     * @param in FIle stream to input from
     */
    void setMovies(std::ifstream&);

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

    /**
     * @brief Prints all customers, movies, and transactions
     * @param out Stream to output to
     * @param si StoreInventory to print
     * @return out 
     */
    friend std::ostream& operator<<(std::ostream&, StoreInventory&);

};