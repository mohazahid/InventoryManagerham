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

Drama::~Drama(){};

bool Drama::operator<(const Drama& rhs) {
    if(this->director == rhs.director) {
        return this->title < rhs.title;
    }
    else {
        return this->director < rhs.director;
    }
}

std::ostream& Drama::print(std::ostream& out) {
    return out;
}
