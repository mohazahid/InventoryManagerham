/**
 * @file drama.h
 * @author
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.edu)
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
    Drama(int, std::string, std::string, int);
    /**
     * @brief Creates a deep copy
     */
    Drama(const Drama&);
    /**
     * @brief Default deconstructor
     */
    ~Drama();
    /**
     * @brief Creates a deep copy
     */
    Drama& operator=(const Drama&);

    // simulate virtual const static behavior
    virtual char type() const { return Drama::genre; }
    /**
     * @brief Prints out movie for display purposes
     * @return std::ostream& 
     */
    virtual std::ostream& display(std::ostream&) const;
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
     * Director
     * Year
     */
    bool operator<(const Drama&) const;
};