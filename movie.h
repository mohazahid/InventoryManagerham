/**
 * @file movie.h
 * @author
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (oahmed@uw.edu)
 * @brief Header file for Movie
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <string>

class Movie {

private:

    /**
     * @details 
     * valid movies must extend Movie
     * genre = '0' is treated as an error code
     */
    const static char genre = '0'; 
    
protected:

    int stock; // quanty of movie in stock
    std::string director; // director of movie
    std::string title; // title of movie
    int year; // year released of movie

    /**
     * @brief Prints the movie
     * @details polymorphic function
     * @param out Stream to output to
     * @return out
     */
    virtual std::ostream& print(std::ostream&) const;

public:

    virtual ~Movie();
    /**
     * @brief Construct a new Movie object
     * @param stock // quantity of movie in stock
     * @param director // director of movie
     * @param title // title of movie
     * @param year // year released of movie
     */
    Movie(int, std::string, std::string, int);
    /**
     * @brief Copy constructor
     * @details Makes a deep copy
     */
    Movie(const Movie&);
    /**
     * @brief Default constructor 
     * @details Member fields are not defined
     */
    Movie();

    /**
     * @brief Returns the genre of the movie
     * @details Simulates static const virtual behavior 
     * @return genre
     */
    virtual char type() const { return genre; }

    virtual bool operator<(const Movie&) const;
    virtual bool operator==(const Movie&) const;

    friend std::ostream& operator<<(std::ostream&, Movie&);

    virtual std::string getKey() const;

    int Borrow();
    int Return();

};