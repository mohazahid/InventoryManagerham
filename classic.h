/**
 * @file classic.h
 * @author 
 * your name (you@domain.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Header for Classic which implements Movie
 * @date 2022-05-18
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "movie.h"

class Classic : public Movie {

private:

    const static char genre = 'C';

    std::string lastName;
    std::string firstName;
    int month;

    // simulate virtual const static behavior
    virtual char type() { return genre; }

    virtual std::ofstream& print(std::ofstream&, Movie&);

public: 

    /**
     * @brief Construct a new Movie object
     * @param stock // quantity of movie in stock
     * @param director // director of movie
     * @param title // title of movie
     * @param year // year released of movie
     * @param lastName // last name of primary actor
     * @param firstName // first name of primary actor
     * @param month // month released of movie
     */
    Classic(int, std::string, std::string, int, std::string, std::string, int);
    ~Classic();

    bool operator<(const Classic&);
    bool operator==(const Classic&);

};