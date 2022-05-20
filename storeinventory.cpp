/**
 * @file storeinventory.cpp
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Implementation file for StoreInventory 
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 * 
 */

#include "storeinventory.h"

StoreInventory::StoreInventory(std::ifstream& customers, std::ifstream& movies) {
    while(!customers.eof()) {
        Customer c;
        customers >> c.custID >> c.custLast >> c.custFirst;
        this->customers.insert(c);
    }
    while(!movies.eof()) {
        char type = movies.get();
        std::string input;
        std::getline(customers, input);
        std::queue<std::string> output;
        std::stringstream ss(input);
        while (ss.good()) {
            std::string str;
            std::getline(ss, str, ',');
            output.push(str);
        }
        int stock, year;
        std::string director, title;
        switch(type) {
            case 'F': {
                stock = std::stoi(output.front());
                output.pop();
                director = output.front();
                output.pop();
                title = output.front();
                output.pop();
                year = std::stoi(output.front());
                output.pop();
                Comedy movie(stock, director, title, year);
                Comedy* ptr = &movie;
                this->inventory.put((director + title), ptr);
            }
            case 'C': {
                int month;
                std::string lastName, firstName;
                stock = std::stoi(output.front());
                output.pop();
                director = output.front();
                output.pop();
                title = output.front();
                output.pop();
                firstName = output.front();
                output.pop();
                lastName = output.front();
                output.pop();
                month = std::stoi(output.front());
                output.pop();
                year = std::stoi(output.front());
                output.pop();
                Classic movie(stock, director, title, year, lastName, firstName, month);
                Classic* ptr = &movie;
                this->inventory.put((director + title), ptr);
            }
            case 'D': {
                stock = std::stoi(output.front());
                output.pop();
                director = output.front();
                output.pop();
                title = output.front();
                output.pop();
                year = std::stoi(output.front());
                output.pop();
                Drama movie(stock, director, title, year);
                Drama* ptr = &movie;
                this->inventory.put((director + title), ptr);
            }
            default: 
                // Skips to next line on invalid input
                customers.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

bool StoreInventory::transact(Log&) {
    return -1;
}

void StoreInventory::printInventory() const {
    
}

void StoreInventory::printTransactions(int) const {
    
}

void StoreInventory::operate(std::ifstream&) {
    
}
