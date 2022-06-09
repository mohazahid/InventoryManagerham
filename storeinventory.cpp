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
        //Seperates tokens by commas 
        while(std::getline(iss, token, delim)) {
            token.erase(0, token.find_first_not_of(' '));
            token.erase(token.find_last_not_of("\r") + 1);
            tokens.push_back(token);
        }
        if(tokens.at(0).size() > 1) { // invalid movie type
            std::cout << "INVALID MOVIE TYPE: " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
            continue;
        }
        char type = tokens.at(0).at(0); // string should only be 1 char
        switch(type) {
        case 'F': {
            /*  Tokens.at()
             *  0     1      2         3      4
             *  type, stock, director, title, year
             */
            if(tokens.size() != 5) { // invalid arguments
                std::cout << "INVALID COMMAND ARGUMENTS: " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
                continue;
            }
            // creating a shared pointer of movie and formating the way its saved
            std::shared_ptr<Movie> movie =
                std::make_shared<Comedy>(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(4)));
            if(checkDuplicate(movie)) { // if true add to our inventory
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
            if(tokens.size() != 5) { // invalid arguments
                std::cout << "INVALID COMMAND ARGUMENTS: " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
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
            if(tokens.size() != 8) { // invalid arguments
                std::cout << "INVALID COMMAND ARGUMENTS: " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
                continue;
            }
            // creating a shared pointer of movie and formating the way its saved
            std::shared_ptr<Movie> movie =
                std::make_shared<Classic>(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(7)),
                                          tokens.at(4), tokens.at(5), std::stoi(tokens.at(6)));
            if(checkDuplicate(movie)) { // if true add to our inventory
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
                std::cout << "INVALID COMMAND: " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
                continue;
            }
            // creating a shared pointer of movie and formating the way its saved
            std::shared_ptr<Movie> movie =
                std::make_shared<Drama>(std::stoi(tokens.at(1)), tokens.at(2), tokens.at(3), std::stoi(tokens.at(4)));
            if(checkDuplicate(movie)) { // if no duplicate add to our inventory
                this->inventory.put(movie->getKey(), movie);
            }
            break;
        }
        default: {
            std::cout << "INVALID MOVIE TYPE: " << line.erase(line.find_last_not_of("\r") + 1) << "\n";
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
        std::string line;
        std::getline(commands, line);
        line.erase(line.find_last_not_of("\r") + 1);
        if(line.empty()) continue;   // empty line given
        char operation = line.at(0); // grab command type from command
        switch(operation) { //checks what action is being promted
        case Borrow: {
            transact(line);
            break;
        }
        case Return: {
            transact(line);
            break;
        }
        case Inventory: {
            printInventory(std::cout);
            break;
        }
        case History: {
            int id = std::stoi(line.substr(2, 4)); //string to int for the ID
            if(line.size() > 6) { // checks for invalid arguments
                std::cerr << "INVALID COMMAND ARGUMENTS: " << line << "\n";
                continue;
            }
            if(!isValid(id)) { // checks for invalid ID
                std::cerr << "INVALID CUSTID: " << line << "\n";
                continue;
            }
            printTransactions(std::cout, id);
            break;
        }
        default: {
            std::cerr << "INVALID COMMAND: " << line << "\n";
            break;
        }
        }
    }
}
void StoreInventory::transact(std::string line) {
    Log bLog{};
    bLog.customer.custID = -1;
    int id = stoi(line.substr(2, 4)); // grab id from command
    char movTyp = line.at(9); // grabs movie type
    for(const auto& customer : customers) {
        if(customer.custID == id) {
            bLog.customer = customer;
        }
    }
    if(bLog.customer.custID == -1) { // invalid id
        std::cerr << "INVALID CUSTID: " << line << "\n";
        return;
    }
    if(line.at(7) != 'D') { // invalid media type
        std::cerr << "INVALID MEDIA TYPE: " << line << "\n";
        return;
    }
    char op = line.at(0); // must be 'B' or 'R'
    if(op == Borrow) {
        bLog.type = Borrow;
    } else if(op == Return) {
        bLog.type = Return;
    } else { 
        std::cerr << "INVALID COMMAND: " << line << "\n";
        return;
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
        std::istringstream iss(line.substr(11));
        while(!iss.eof()) {
            std::string token;
            iss >> token;
            keytom += token;
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
        std::cerr << "INVALID MOVIE TYPE: " << line << "\n";
        return;
    }
    }
    // Find matching movie in inventory
    for(const auto& mov : inventory.get(keytom)) {
        if(mov->getKey() == keytom) {
            bLog.movie = mov.get(); // movie found; make copy
            if(bLog.type == Borrow) {
                if(mov->Borrow() == -1) {
                    std::cerr << "MOVIE STOCK IS EMPTY: " << line << "\n";
                    return;
                }
                this->transactions.put(bLog.customer.custID, bLog);
            }
            else if(bLog.type == Return) {
                if(mov->Return() == -1) { // movie found but its full
                    std::cerr << "MOVIE STOCK IS FULL: " << line << "\n";
                    return;
                }
                this->transactions.put(bLog.customer.custID, bLog);
            }
        }
    }
    if(bLog.movie == nullptr) { // movie was not found; invalid command
        std::cerr << "INVALID KEY: " << line << " (" << keytom << ")" << "\n";
    }
}

void StoreInventory::printCustomers(std::ostream& out) const {
    out << "\n-------------------------------------------------------------------------------------------------\n";
    out << "Customers List: \n";
    for(auto customer : this->customers) { // loops through customers
        out << customer << '\n';
    }
    out.flush();
}

void StoreInventory::printInventory(std::ostream& out) const {
    out << "\n-------------------------------------------------------------------------------------------------";
    std::vector<std::shared_ptr<Comedy>> comedys;
    std::vector<std::shared_ptr<Drama>> dramas;
    std::vector<std::shared_ptr<Classic>> classics;
    // filter movies into vectors to be sorted
    for(int i = 0; i < this->inventory.getSize(); ++i) {
        for(const auto& movie : this->inventory.get(i)) {
            char type = movie->type();
            switch(type) {
            // Cases F = Comedy, D = Drama, C = Classic
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
    out.flush();

    // Define std::sort predicates
    auto sortComedys = [](std::shared_ptr<Comedy> lhs, std::shared_ptr<Comedy> rhs) { return (*lhs) < (*rhs); };
    auto sortDramas = [](std::shared_ptr<Drama> lhs, std::shared_ptr<Drama> rhs) { return (*lhs) < (*rhs); };
    auto sortClassics = [](std::shared_ptr<Classic> lhs, std::shared_ptr<Classic> rhs) { return (*lhs) < (*rhs); };
    // Sort movies acco!rding to sorting behavior
    std::sort(comedys.begin(), comedys.end(), sortComedys); // *lhs < *rhs
    std::sort(dramas.begin(), dramas.end(), sortDramas);
    std::sort(classics.begin(), classics.end(), sortClassics);
    out << "\nInventory Movies: \n";
    //prints movies in our inventory
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
    std::cout << "\n-------------------------------------------------------------------------------------------------\n";
    std::cout << "Checking History of Customer " << id << '\n';
    if(!isValid(id)) return; // if 'id' does not exist in customer list, return
    for(const auto& log : transactions.get(id)) {
        if(log.customer.custID == id) {
            out << log << '\n';
        }
    }
    out.flush();
}

void StoreInventory::printTransactions(std::ostream& out) const {
    std::cout << "\n-------------------------------------------------------------------------------------------------\n";
    for(int i = 0; i < this->transactions.getSize(); ++i) {
        for(const auto& log : transactions.get(i)) {
            out << log << "\n";
        }
    }
    out.flush();

}
bool StoreInventory::isValid(int id) const {
    //loops through all customers
    for(auto const& cust : this->customers) {
        //if the id we are searching for is equal to any of the customer id's
        //then we return true;
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
