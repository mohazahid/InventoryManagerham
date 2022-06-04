/**
 * @file movie.cpp
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.edu)
 * @brief Implementation file for Movie
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 */

#include "movie.h"

Movie::Movie(){
    
}

Movie::Movie(int stock, std::string director, std::string title, int year) :
    stock(stock), director(director), title(title), year(year) {}

Movie::Movie(const Movie& m) : 
    stock(m.stock), director(m.director), title(m.title), year(m.year) {}

Movie::~Movie() {}

bool Movie::operator==(const Movie& rhs) const {
    return ((this->director == rhs.director)
           && (this->title == rhs.title) 
           && (this->year == rhs.year));
}

bool Movie::operator<(const Movie& rhs) const {
    return this->year < rhs.year;
}

std::ostream& operator<<(std::ostream& out, Movie& m) {
    return m.print(out);
}

std::ostream& Movie::print(std::ostream& out) const {
    out << "Invalid genre: " << this->type();
    return out;
}

std::string Movie::getDirector() {
    return director;
}

std::string Movie::getTitle() {
    return title;
}
std::string Movie::getKey() const {
    return this->title + this->director;
}
int Movie::getStock() const {
    return this->stock;
}
void Movie::setStock(int nStock) {
    this->stock = nStock;
}
int Movie::Borrow() {
    if(this->stock < 0) return -1;
    return --this->stock;
}

int Movie::Return() {
    return ++this->stock;
}
