/**
 * @file comedy.h
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Header for Comedy which implements Movie
 * @date 2022-05-18
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "movie.h"

class Comedy : public Movie {

private:

    const static char genre = 'F';

    // simulate virtual const static behavior
    virtual char type() { return genre; }

    virtual std::ostream& print(std::ostream&);

public: 

    /**
     * @brief Construct a new Movie object
     * @param stock // quantity of movie in stock
     * @param director // director of movie
     * @param title // title of movie
     * @param year // year released of movie
     */
    Comedy(int, std::string, std::string, int);
    virtual ~Comedy();

    bool operator<(const Comedy&);

};