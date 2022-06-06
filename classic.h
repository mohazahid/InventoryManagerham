/**
 * @file classic.h
 * @author
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.edu)
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
    std::string firstName; // first name of the major actor
    std::string lastName;  // last name of the major actor
    int month;             // month the movie was released

    /**
     * @brief Prints the classic
     * @return std::ostream&
     */
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
    /**
     * @brief Creates a deep copy
     */
    Classic(const Classic&);
    /**
     * @brief Default deconstructor
     */
    ~Classic();

    /**
     * @brief Creates a deep copy
     */
    Classic& operator=(const Classic&);

    // simulate virtual const static behavior
    virtual char type() const { return Classic::genre; }

    /**
     * @brief Returns the classics's key
     * @details Key is major actor and release date
     * @return std::string
     */
    virtual std::string getKey() const;

    /**
     * @brief Compares two classic objects
     * @details
     * Compares by:
     * firstName
     * lastName
     * year
     * month
     */
    bool operator<(const Classic&) const;
    /**
     * @brief Compares two classic objects
     * @return true if all member fields are equal
     * @return false any member field is not equal
     */
    bool operator==(const Classic&) const;
};