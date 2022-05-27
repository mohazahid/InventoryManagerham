/**
 * @file storeinventory.cpp
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.edu)
 * @brief Implementation file for StoreInventory 
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 * import java.util.ArrayList;
 */

#include "storeinventory.h"
#include "movie.h"

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
                // # TODO output invalid command to console
                // Comedy* movie = new Comedy(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(4)));
                std::shared_ptr<Movie> movie = std::make_shared<Comedy>(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(4)));
                this->inventory.put(movie->getKey(), movie);
                break;
            }
            case 'C': {
                /*  Tokens.at()
                 *  0     1      2         3      4  
                 *  type, stock, director, title, firstName lastName month year
                 */
                // Finish specialized string parsing
                if(tokens.size() != 5) continue; // invalid arguements
                // # TODO output invalid command to console
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
                 *  type, stock, director, title, firstName lastName month 
                 * 
                 */
                if(tokens.size() != 8) continue; // invalid arguements
                // # TODO output invalid command to console
                std::shared_ptr<Movie> movie = std::make_shared<Classic>(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(7)), tokens.at(4), tokens.at(5), std::stoi(tokens.at(6)));
                this->inventory.put(movie->getKey(), movie);
                break;
            }
            case 'D': {
                /*  Tokens.at()
                 *  0     1      2         3      4  
                 *  type, stock, director, title, year
                 */
                if(tokens.size() != 5) continue; // invalid arguements 
                // # TODO output invalid command to console
                std::shared_ptr<Movie> movie = std::make_shared<Drama>(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(4)));
                this->inventory.put(movie->getKey(), movie);
                break;
            }
            default: {
                // # TODO output invalid command to console
                continue;
            }
        }
    }
}

void StoreInventory::operate(std::ifstream& commands) {
    while(!commands.eof()) {
        std::string line;
        std::getline(commands, line);
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        while(!iss.eof()) {
            std::string temp;
            if(iss >> temp) { 
                tokens.push_back(temp);
            }
        }
        if (tokens.at(0).size() > 1) continue; // invalid movie type
        char operation = tokens.at(0).at(0);
        switch(operation) {
            case Borrow: {
                break;
            }
            case Return: {
                break;
            }
            case Inventory: {
                printInventory(std::cout);
                break;
            }
            case History: {
                if (tokens.size() != 2) continue; // invalid arguements
                int id = std::stoi(tokens.at(2));
                if(!isValid(id)) continue; // invalid ID
                printTransactions(std::cout, id);
                break;
            }
            default: {
                // invalid command
                break;
            }
        }
    }
}

bool StoreInventory::transact(Log& l) {
    std::string dir = l.movie.getDirector();
    std::string title = l.movie.getTitle();
    if(isValid(l.customer.custID) and l.type != 'B'){
        auto movList = inventory.get(dir);
        for(auto mov: movList){
            if(*mov == l.movie){
                transactions.put(l.movie.getKey(), l);
                return true;
            }
        }
    } else {
        return false;
    }
    return -1;
}

void StoreInventory::printCustomers(std::ostream& out) const {
    for(auto customer : this->customers) {
        out << customer;
    }
    out << std::endl;
}

void StoreInventory::printInventory(std::ostream& out) const {
    std::vector<Movie*> comedys;
    std::vector<Movie*> dramas;
    std::vector<Movie*> classics;
    // filter movies into vectors to be sorted
    for(int i = 0; i < this->inventory.getSize(); ++i) {
        for(const auto& movie : this->inventory.get(i)) {
            char type = movie->type();
            switch(type) {
                case 'F': {
                    comedys.push_back(movie.get());
                    break;
                }   
                case 'D': {
                    dramas.push_back(movie.get());
                    break;
                }
                case 'C': {
                    classics.push_back(movie.get());
                    break;
                }
                default: {
                    // All defined movies are either 'F', 'D', or 'C' 
                    std::cerr << *movie << std::endl; 
                }
            }
        }
    }
    // sort movies
    std::sort(comedys.begin(), comedys.end());
    std::sort(dramas.begin(), dramas.end());
    std::sort(classics.begin(), classics.end());
    for(auto comedy : comedys) {
        out << *comedy << '\n';
    }
    for(auto drama : dramas) {
        out << *drama << '\n';
    }
    for(auto classic : classics) {
        out << *classic << '\n';
    }
}

void StoreInventory::printTransactions(std::ostream& out, int id) const {
    if(!isValid(id)) return; // if 'id' does not exist in customer list, return
    for(const auto& log : transactions.get(id)) {
        out << log << '\n';
    }
    out << std::endl;
    // auto log_front = logList.begin();
    // for (int i = 0; i < logList.size(); i++)
    // {
    //     std::advance(log_front, i);
    //     std::cout << *log_front << std::endl;
    // }
}

void StoreInventory::printTransactions(std::ostream& out) const {
    for(int i = 0; i < this->transactions.getSize(); ++i) {
        for(const auto& log : transactions.get(i)) {
            out << log << '\n';
        }
    }
}    

bool StoreInventory::isValid(int id) const {
    for(auto const& cust : this->customers) {
        if(cust.custID == id) return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, StoreInventory& inv) {
    inv.printCustomers(out);
    inv.printInventory(out);
    inv.printTransactions(out);
    return out;
}
