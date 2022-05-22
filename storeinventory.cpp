/**
 * @file storeinventory.cpp
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Implementation file for StoreInventory 
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 * import java.util.ArrayList;*
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
        movies.ignore(1);
        std::string input;
        std::getline(movies, input);
        if(input == "") continue;
        std::queue<std::string> output;
        std::stringstream ss(input);
        while(ss.good()) {
            std::string str;
            std::getline(ss, str, ',');
            str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
            str = str.substr(1);
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
                this->inventory.put((director + title), movie);
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
                this->inventory.put((director + title), movie);
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
                this->inventory.put((director + title), movie);
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

void StoreInventory::printTransactions(int id) const {
    if(!isValid(id)) return; // if 'id' does not exist in customer list, return
    std::list<Log> logList = transactions.get(id);
    for(auto const& log : logList) {
        std::cout << log << '\n';
    }
    std::cout << std::endl;
    // auto log_front = logList.begin();
    // for (int i = 0; i < logList.size(); i++)
    // {
    //     std::advance(log_front, i);
    //     std::cout << *log_front << std::endl;
    // }
}

void StoreInventory::operate(std::ifstream&) {
    
}

bool StoreInventory::isValid(int id) const {
    for(auto const& cust : this->customers) {
        if(cust.custID == id) return true;
    }
    return false;
}