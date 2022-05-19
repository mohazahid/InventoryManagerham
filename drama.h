/**
 * @file drama.h
 * @author 
 * your name (you@domain.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Header for Drama which implements Movie
 * @date 2022-05-18
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "movie.h"

class Classic : public Movie {

private:

    const static char genre = 'D';

    // simulate virtual const static behavior
    virtual char type() { return genre; }

public: 

    bool operator<(const Classic&);
    bool operator==(const Classic&);

};