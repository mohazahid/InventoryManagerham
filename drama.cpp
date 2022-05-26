/**
 * @file drama.cpp
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief 
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 * 
 */

#include "drama.h"

Drama::Drama(int stock, std::string director, std::string title, int year) : 
    Movie(stock, director, title, year) {}

Drama::Drama(const Drama& d) : Movie(d.stock, d.director, d.title, d.year) {}

Drama::~Drama(){};

bool Drama::operator<(const Drama& rhs) const {
    if(this->director == rhs.director) {
        return this->title < rhs.title;
    }
    else {
        return this->director < rhs.director;
    }
}

std::ostream& Drama::print(std::ostream& out) const {
    out << this->stock << " of " << this->title << " by " << this->director << " in " << this->year;
    return out;
}
