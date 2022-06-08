/**
 * @file comedy.cpp
 * @author
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.edu)
 * @brief Implementation for Comedy which implements Movie
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 *
 */

#include "comedy.h"

Comedy::Comedy(int stock, std::string director, std::string title, int year) : Movie(stock, director, title, year) {}

Comedy::Comedy(const Comedy& c) : Movie(c.stock, c.director, c.title, c.year) {}

Comedy::~Comedy() {}

Comedy& Comedy::operator=(const Comedy& rhs) {
    if(this == &rhs) return *this; // Check for self-assignment
    this->stock = rhs.stock;
    this->director = rhs.director;
    this->title = rhs.title;
    this->year = rhs.year;
    return *this;
}

bool Comedy::operator<(const Comedy& rhs) const {
    if(this->title == rhs.title) {
        return this->year < rhs.year;
    }
    return this->title < rhs.title;
}

std::string Comedy::getKey() const {
    return this->title + std::to_string(this->year);
}

std::ostream& Comedy::print(std::ostream& out) const {
    out << this->stock << " of " << this->type() << ' ' << this->title << ' ' << this->year;
    return out;
}

std::ostream& Comedy::display(std::ostream& out) const {
    out << this->type() << ' ' << this->director << ' ' << this->year << " " << this->title;
}