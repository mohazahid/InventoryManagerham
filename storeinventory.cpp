/**
 * @file storeinventory.cpp
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Implementation file for StoreInventory 
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 * import java.util.ArrayList;
 */

#include "storeinventory.h"

StoreInventory::StoreInventory(std::ifstream& customers, std::ifstream& movies) {
    setCustomers(customers);
    setMovies(movies);
}

void StoreInventory::setCustomers(std::ifstream& customers) {
    while(!customers.eof()) {
        Customer c;
        customers >> c.custID >> c.custLast >> c.custFirst;
        this->customers.insert(c);
    }
}

void StoreInventory::setMovies(std::ifstream& movies) {
    while(!movies.eof()) {
        // parse line 
        std::string line;
        std::getline(movies, line);
        if(line == "") continue; // empty line was read
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        char delim = ',';
        std::string token;
        while(std::getline(iss, token, delim)) {
            token.erase(0, token.find_first_not_of(' '));
            token.erase(token.find_last_not_of("\r")+1);
            tokens.push_back(token);
        }
        if(tokens.at(0).size() > 1) continue; // invalid movie type
        char type = tokens.at(0).at(0); // string should only be 1 char
        switch(type) {
            case 'F': {
                /*  Tokens.at()
                 *  0     1      2         3      4  
                 *  type, stock, director, title, year
                 */
                if(tokens.size() != 5) continue; // invalid arguements
                Comedy movie(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(4)));
                this->inventory.put((tokens.at(2) + tokens.at(3)), movie);
                break;
            }
            case 'C': {
                /*  Tokens.at()
                 *  0     1      2         3      4  
                 *  type, stock, director, title, firstName lastName month year
                 */
                // Finish specialized string parsing
                if(tokens.size() != 5) continue; // invalid arguements
                std::istringstream issClassic(tokens.at(4));
                tokens.pop_back();
                while(!issClassic.eof()) {
                    std::string temp;
                    if(issClassic >> temp) {
                        tokens.push_back(temp);
                    }
                }
                /*  Tokens.at()
                 *  0     1      2         3      4        5         6     7
                 *  type, stock, director, title, firstName lastName month year
                 */
                if(tokens.size() != 8) continue; // invalid arguements
                Classic movie(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(7)), tokens.at(4), tokens.at(5), std::stoi(tokens.at(6)));
                this->inventory.put((tokens.at(2)+tokens.at(3)), movie);
                break;
            }
            case 'D': {
                /*  Tokens.at()
                 *  0     1      2         3      4  
                 *  type, stock, director, title, year
                 */
                if(tokens.size() != 5) continue; // invalid arguements
                Comedy movie(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(4)));
                this->inventory.put((tokens.at(2) + tokens.at(3)), movie);
                break;
            }
            default: {
                continue;
            }
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

std::ostream& operator<<(std::ostream& out, StoreInventory& inv) {
    // Print Customers 
    for(auto customer : inv.customers) {
        out << customer;
    }
    out << std::endl;
    // Print Inventory
    out << inv.inventory;
    return out;
}
