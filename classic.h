/**
 * @file classic.h
 * @author 
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (oahmed@uw.edu)
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

protected:

    std::string firstName;
    std::string lastName;
    int month;

    virtual std::ostream& print(std::ostream&) const;

public:
    /**
     * @brief Construct a new Movie object
     * @param stock // quantity of movie in stock
     * @param director // director of movie
     * @param title // title of movie
     * @param year // year released of movie
     * @param firstName // first name of primary actor
     * @param lastName // last name of primary actor
     * @param month // month released of movie
     */
    Classic(int, std::string, std::string, int, std::string, std::string, int);
    Classic(const Classic&);
    virtual ~Classic();

    // simulate virtual const static behavior
    virtual char type() const { return Classic::genre; }

    virtual std::string getKey() const;

    bool operator<(const Classic&) const;
    bool operator==(const Classic&) const;

};