/**
 * @file comedy.cpp
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Implementation for Comedy which implements Movie
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 * 
 */

#include "comedy.h"

Comedy::Comedy(int stock, std::string director, std::string title, int year) : 
    Movie(stock, director, title, year) {}

Comedy::~Comedy(){}

bool Comedy::operator<(const Comedy& rhs) {
    if(this->title == rhs.title) {
        return this->year < rhs.year;
    }
    else {
        return this->title < rhs.title;
    }
}
// shh he wont know