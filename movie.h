/**
 * @file movie.h
 * @author
 * Hayden Lauritzen (haylau@uw.edu)
 * Abhimanyu Kumar (akumar28@uw.edu)
 * Mohammad Zahid (adyanzah@uw.edu)
 * @brief Header file for Movie
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// #TODO figure out how to make pure virtual?
// cant instaniate movie object in a log if its pure virtual see storeinventory.h:40

#pragma once

#include <iostream>
#include <string>

class Movie {

private:
    const static char genre = '0'; // type of movie

protected:
    int stock;            // quanty of movie in stock
    std::string director; // director of movie
    std::string title;    // title of movie
    int year;             // year released of movie

    // simulate virtual const static behavior

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
    Movie(const Movie&);
    Movie();

    std::string getDirector();
    std::string getTitle();

    virtual char type() const { return genre; }

    /**
     * @brief Defines sort predicate
     */
    struct sortPredicate {
        inline bool operator()(const Movie* v1, const Movie* v2) {
            return ((*v1) < (*v2));
        }
    };

    virtual bool operator<(const Movie&) const;
    virtual bool operator==(const Movie&) const;

    /**
     * @brief Prints the movie
     * @param out Stream to output to
     * @return Stream to output to
     */
    friend std::ostream& operator<<(std::ostream&, Movie&);

    /**
     * @brief Returns the movie's key
     * @details Returns the defined sorting behavior of the movie
     * @return HashTable key value 
     */
    virtual std::string getKey() const;

    /**
     * @brief Decrements movie's stock
     * @pre Stock must be greater than 1
     * @return Postdecrement of movie's stock
     */
    int Borrow();
    /**
     * @brief Decrements movie's stock
     * @pre Stock must 
     * @return Postincrement of movie's stock
     */
    int Return();
};