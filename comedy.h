/**
 * @file comedy.h
 * @author 
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.edu)
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

protected:

    virtual std::ostream& print(std::ostream&) const;

public: 

    /**
     * @brief Construct a new Movie object
     * @param stock // quantity of movie in stock
     * @param director // director of movie
     * @param title // title of movie
     * @param year // year released of movie
     */
    Comedy(int, std::string, std::string, int);
    Comedy(const Comedy&);
    virtual ~Comedy();

    // simulate virtual const static behavior
    virtual char type() const { return Comedy::genre; }

    virtual std::string getKey() const;

    bool operator<(const Comedy&) const;

};