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
     */
    Comedy(int, std::string, std::string, int);
    /**
     * @brief Creates a deep copy
     */
    Comedy(const Comedy&);
    /**
     * @brief Default deconstructor
     */
    ~Comedy();
    /**
     * @brief Creates a deep copy
     */
    Comedy& operator=(const Comedy&);
    /**
     * @brief simulate virtual const static behavio
     * @return char 
     */
    virtual char type() const { return Comedy::genre; }
    /**
     * @brief Returns the movie's key
     * @details Returns the defined sorting behavior of the movie
     * @return HashTable key value
     */
    virtual std::string getKey() const;
    /**
     * @brief Compares two movie objects
     * @details
     * Compares by:
     * Title
     * Year
     */
    bool operator<(const Comedy&) const;
    /**
     * @brief Prints out movie for display purposes
     * @return std::ostream& 
     */
    virtual std::ostream& display(std::ostream& out) const;
};