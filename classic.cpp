/**
 * @file classic.cpp
 * @author
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.edu)
 * @brief Implementation for Classic which implements Movie
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 *
 */

#include "classic.h"

// #TODO figure how to format this to not look like a pyschopath

Classic::Classic(int stock, std::string director, std::string title, int year, std::string firstName,
                 std::string lastName, int month)
    : Movie(stock, director, title, year), firstName(firstName), lastName(lastName), month(month) {}

Classic::Classic(const Classic& c)
    : Movie(c.stock, c.director, c.title, c.year), firstName(c.firstName), lastName(c.lastName), month(c.month) {}

Classic::~Classic() {}

Classic& Classic::operator=(const Classic& rhs) {
    if(this == &rhs) return *this; // Check for self-assignment
    this->stock = rhs.stock;
    this->director = rhs.director;
    this->title = rhs.title;
    this->year = rhs.year;
    this->month = rhs.month;
    this->firstName = rhs.firstName;
    this->lastName = rhs.lastName;
    return *this;
}

bool Classic::operator<(const Classic& rhs) const {
    if(this->year != rhs.year) {
        return this->year < rhs.year;
    }
    if(this->month != rhs.month) {
        return this->month < rhs.month;
    }
    if(this->lastName != rhs.lastName) {
        return this->lastName < rhs.lastName;
    }
    return this->firstName < rhs.firstName;
}

bool Classic::operator==(const Classic& rhs) const {
    return Movie::operator==(rhs) && this->lastName == rhs.lastName && this->firstName == rhs.lastName &&
           this->month == rhs.month;
}

std::string Classic::getKey() const {
    return std::to_string(this->month) + std::to_string(this->year) + this->firstName + this->lastName;
}

std::ostream& Classic::print(std::ostream& out) const {
    out << this->stock << " of " << this->type() << ' ' << this->month << ' ' << this->year << ' ' << this->firstName
        << ' ' << this->lastName;
    return out;
}

std::ostream& Classic::display(std::ostream& out) const {
    return out << this->type() << ' ' << this->director << ' ' << this->title << ' ' << this->firstName << ' '
               << this->lastName << ' ' << this->month << ' ' << this->year;
}