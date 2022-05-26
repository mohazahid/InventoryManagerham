/**
 * @file movie.cpp
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Implementation file for Movie
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 */

#include "movie.h"

Movie::Movie(int stock, std::string director, std::string title, int year) : 
    stock(stock), director(director), title(title), year(year) {}

Movie::~Movie() {}

bool Movie::operator==(const Movie& rhs) {
    return ((this->director == rhs.director) 
    && (this->title == rhs.title) 
    && (this->year == rhs.year)); 
}

bool Movie::operator<(const Movie& rhs) {
    return this->year < rhs.year;
}

std::ostream& operator<<(std::ostream& out, Movie& m) {
    return m.print(out);
}

std::ostream& Movie::print(std::ostream& out) {
    out << "Invalid genre: " << type();
    return out;
}

int Movie::Borrow() {
    if(this->stock < 0) return -1;
    return --this->stock;
}

int Movie::Return() {
    return ++this->stock;
}