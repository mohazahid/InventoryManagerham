/**
 * @file classic.cpp
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Implementation for Classic which implements Movie
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 * 
 */

#include "classic.h"

// #TODO figure how to format this to not look like a pyschopath

Classic::Classic(int stock, std::string director, std::string title, int year, 
    std::string firstName, std::string lastName, int month) : 
    Movie(stock, director, title, year), firstName(firstName), 
    lastName(lastName), month(month) {}

Classic::~Classic(){}

bool Classic::operator<(const Classic& rhs) {
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

bool Classic::operator==(const Classic& rhs) {
    return (Movie::operator==(rhs) 
    && (this->lastName == rhs.lastName) 
    && (this->firstName == rhs.lastName) 
    && (this->month == rhs.month)); 
}

std::ofstream& Classic::print(std::ofstream&, Classic&) {
    
}