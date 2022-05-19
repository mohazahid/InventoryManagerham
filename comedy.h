/**
 * @file comedy.h
 * @author 
 * your name (you@domain.com)
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

public: 

    bool operator<(const Comedy&);
    bool operator==(const Comedy&);

};