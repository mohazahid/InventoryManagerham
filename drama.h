/**
 * @file drama.h
 * @author 
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (oahmed@uw.edu)
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
    Drama(int, std::string, std::string, int);
    Drama(const Drama&);
    virtual ~Drama();

    // simulate virtual const static behavior
    virtual char type() const { return Drama::genre; }

    virtual std::string getKey() const;

    bool operator<(const Drama&) const;

};