/**
 * @file storeinventory.cpp
 * @author
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.edu)
 * @brief Implementation file for StoreInventory
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 * import java.util.ArrayList;
 */

#include <vector>

#include "movie.h"
#include "storeinventory.h"

StoreInventory::StoreInventory(std::istream& customers, std::istream& movies) {
    setCustomers(customers);
    setMovies(movies);
}

StoreInventory::StoreInventory(std::istream& customers, std::istream& movies, std::istream& commands) {
    setCustomers(customers);
    setMovies(movies);
    this->operate(commands);
}

void StoreInventory::setCustomers(std::istream& customers) {
    while(!customers.eof()) {
        Customer c;
        customers >> c.custID >> c.custLast >> c.custFirst;
        this->customers.insert(c);
    }
}
void StoreInventory::setMovies(std::istream& movies) {
    while(!movies.eof()) {
        // parse line
        std::string line;
        std::getline(movies, line);
        if(line == "") continue;
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        char delim = ',';
        std::string token;
        while(std::getline(iss, token, delim)) {
            token.erase(0, token.find_first_not_of(' '));
            token.erase(token.find_last_not_of("\r") + 1);
            tokens.push_back(token);
        }
        if(tokens.at(0).size() > 1) { // invalid movie type
            std::cout << "INVALID COMMAND " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
            continue;
        }
        char type = tokens.at(0).at(0); // string should only be 1 char
        switch(type) {
        case 'F': {
            /*  Tokens.at()
             *  0     1      2         3      4
             *  type, stock, director, title, year
             */
            if(tokens.size() != 5) { // invalid arguements
                std::cout << "INVALID COMMAND " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
                continue;
            }
            std::shared_ptr<Movie> movie =
                std::make_shared<Comedy>(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(4)));
            if(checkDuplicate(movie)) {
                this->inventory.put(movie->getKey(), movie);
            }
            break;
        }
        case 'C': {
            /*  Tokens.at()
             *  0     1      2         3      4
             *  type, stock, director, title, firstName lastName month year
             */
            // Finish specialized string parsing
            if(tokens.size() != 5) { // invalid arguements
                std::cout << "INVALID COMMAND " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
                continue;
            }
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
            if(tokens.size() != 8) { // invalid arguements
                std::cout << "INVALID COMMAND " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
                continue;
            }
            std::shared_ptr<Movie> movie =
                std::make_shared<Classic>(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(7)),
                                          tokens.at(4), tokens.at(5), std::stoi(tokens.at(6)));
            if(checkDuplicate(movie)) {
                this->inventory.put(movie->getKey(), movie);
            }
            break;
        }
        case 'D': {
            /*  Tokens.at()
             *  0     1      2         3      4
             *  type, stock, director, title, year
             */
            if(tokens.size() != 5) { // invalid arguements
                std::cout << "INVALID COMMAND " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
                continue;
            }
            std::shared_ptr<Movie> movie =
                std::make_shared<Drama>(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(4)));
            if(checkDuplicate(movie)) {
                this->inventory.put(movie->getKey(), movie);
            } else {
            }
            break;
        }
        default: {
            std::cout << "INVALID COMMAND " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
            continue;
        }
        }
    }
}
bool StoreInventory::checkDuplicate(std::shared_ptr<Movie> movie) {
    for(auto i : inventory.get(movie->getKey())) {
        if(*i == *movie) {
            // Increments stock and inventory by the duplicate's stock
            i->setStock(i->getStock() + movie->getStock());
            return false;
        }
    }
    return true;
}
void StoreInventory::operate(std::istream& commands) {
    while(!commands.eof()) {
        std::string line; // set line
        std::getline(commands, line);
        line.erase(line.find_last_not_of("\r") + 1);
        if(line.empty()) continue;   // empty line given
        char operation = line.at(0); // grab command type from command
        switch(operation) {
        case Borrow: {
            transact(line);
            break;
        }
        case Return: {
            transact(line);
            break;
        }
        case Inventory: {
            std::cout << "Checking Inventory\n"; 
            printInventory(std::cout);
            break;
        }
        case History: {
            int id = std::stoi(line.substr(2, 4));
            std::cout << "Checking History of customer " << id << '\n';
            if(line.size() > 6) { // invalid arguements
                std::cout << "INVALID COMMAND " << line << "\n";
                continue;
            }
            if(!isValid(id)) { // invalid ID
                std::cout << "INVALID COMMAND " << line << "\n";
                continue;
            }
            printTransactions(std::cout, id);
            break;
        }
        default: {
            std::cout << "INVALID COMMAND " << line << "\n";
            break;
        }
        }
    }
}

void StoreInventory::transact(std::string line) {
    Log bLog;
    int id = stoi(line.substr(2, 4)); // grab id from command
    char movTyp = line.at(7);
    for(const auto& customer : customers) {
        if(customer.custID == id) {
            bLog.customer = customer;
        }
    }
    char op = line.at(0); // must be 'B' or 'R'
    if(op == Borrow) {
        bLog.type = Borrow;
    } else if(op == Return) {
        bLog.type = Return;
    } else {
        std::cout << "INVALID COMMAND " << line << "\n";
    }
    std::string keytom = "";
    switch(movTyp) {
    case 'F': {
        // fetch key to movie
        keytom += line.substr(11, line.find(',') - 11) += line.substr(line.find(',') + 2);
        break;
    }
    case 'C': {
        // fetch key to movie
        std::istringstream iss(line.substr(12));
        while(!iss.eof()) {
            iss >> keytom;
        }
        break;
    }
    case 'D': {
        // fetch key to movie
        keytom += line.substr(11, line.find(',') - 11);
        keytom += line.substr(line.find(',') + 2, line.size() - line.find(',') - 3);
        break;
    }
    default: {
        std::cout << "INVALID COMMAND " << line << "\n";
        break;
    }
    }
    // Find matching movie in inventory
    for(const auto& mov : inventory.get(keytom)) {
        if(mov->getKey() == keytom) {
            bLog.movie = mov.get(); // movie found; make copy
            if(bLog.type == Borrow) {
                if(mov->Borrow() == -1) {
                    std::cout << "MOVIE STOCK IS EMPTY: " << line << "\n";
                }
                else {
                    this->transactions.put(bLog.customer.custID, bLog);
                }
                if(mov->Return() == -1) {
                    std::cout << "MOVIE STOCK IS FULL: " << line << "\n";
                }
                else {
                    this->transactions.put(bLog.customer.custID, bLog);
                }
            }
        }
    }
    if(bLog.movie == nullptr) { // movie was not found; invalid command
        std::cout << "INVALID COMMAND: " << line << "\n";
    }
}

void StoreInventory::printCustomers(std::ostream& out) const {
    out << "Customers List: \n";
    for(auto customer : this->customers) {
        out << customer << '\n';
    }
    out << std::endl;
}

void StoreInventory::printInventory(std::ostream& out) const {
    std::vector<std::shared_ptr<Comedy>> comedys;
    std::vector<std::shared_ptr<Drama>> dramas;
    std::vector<std::shared_ptr<Classic>> classics;
    // filter movies into vectors to be sorted
    for(int i = 0; i < this->inventory.getSize(); ++i) {
        for(const auto& movie : this->inventory.get(i)) {
            char type = movie->type();
            switch(type) {
            case 'F': {
                comedys.push_back(std::dynamic_pointer_cast<Comedy>(movie));
                break;
            }
            case 'D': {
                dramas.push_back(std::dynamic_pointer_cast<Drama>(movie));
                break;
            }
            case 'C': {
                classics.push_back(std::dynamic_pointer_cast<Classic>(movie));
                break;
            }
            default: {
                // All defined movies are either 'F', 'D', or 'C'
                std::cerr << *movie << std::endl;
            }
            }
        }
    }
    std::cout << std::endl;

    // Define std::sort predicates
    auto sortComedys = [](std::shared_ptr<Comedy> lhs, std::shared_ptr<Comedy> rhs) { return (*lhs) < (*rhs); };
    auto sortDramas = [](std::shared_ptr<Drama> lhs, std::shared_ptr<Drama> rhs) { return (*lhs) < (*rhs); };
    auto sortClassics = [](std::shared_ptr<Classic> lhs, std::shared_ptr<Classic> rhs) { return (*lhs) < (*rhs); };
    // Sort movies acco!rding to sorting behavior
    std::sort(comedys.begin(), comedys.end(), sortComedys); // *lhs < *rhs
    std::sort(dramas.begin(), dramas.end(), sortDramas);
    std::sort(classics.begin(), classics.end(), sortClassics);
    out<<"Inventory Movies: \n";
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
}

void StoreInventory::printTransactions(std::ostream& out) const {
    for(int i = 0; i < this->transactions.getSize(); ++i) {
        for(const auto& log : transactions.get(i)) {
            out << log << "\n";
        }
    }
    out << std::endl;
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
