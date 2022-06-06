/**
 * @file drama.cpp
 * @author
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.ed)
 * @brief
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 *
 */

#include "drama.h"

Drama::Drama(int stock, std::string director, std::string title, int year) : Movie(stock, director, title, year) {}

Drama::Drama(const Drama& d) : Movie(d.stock, d.director, d.title, d.year) {}

Drama::~Drama(){};

Drama& Drama::operator=(const Drama& rhs) {
    if(this == &rhs) return *this; // Check for self-assignment
    this->stock = rhs.stock;
    this->director = rhs.director;
    this->title = rhs.title;
    this->year = rhs.year;
    return *this;
}

bool Drama::operator<(const Drama& rhs) const {
    if(this->director == rhs.director) {
        return this->title < rhs.title;
    } else {
        return this->director < rhs.director;
    }
}

std::string Drama::getKey() const { return this->director + std::to_string(this->year); }

std::ostream& Drama::print(std::ostream& out) const {
    out << this->stock << " of " << this->type() << ' ' << this->director << ' ' << this->year << " " << this->title;
    return out;
}
