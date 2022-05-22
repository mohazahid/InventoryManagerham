/**
 * @file drama.h
 * @author 
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Header for Drama which implements Movie
 * @date 2022-05-18
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "movie.h"

class Drama : public Movie {

private:

    const static char genre = 'D';

    // simulate virtual const static behavior
    virtual char type() { return genre; }

    virtual std::ofstream& print(std::ofstream&, Drama&);

public: 

    /**
     * @brief Construct a new Movie object
     * @param stock // quantity of movie in stock
     * @param director // director of movie
     * @param title // title of movie
     * @param year // year released of movie
     */
    Drama(int, std::string, std::string, int);
    virtual ~Drama();

    bool operator<(const Drama&);

};