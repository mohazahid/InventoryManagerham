/**
 * @file movie.h
 * @author
 * Hayden Lauritzen (haydenlauritzen@gmail.com)
 * your name (you@domain.com)
 * your name (you@domain.com)
 * @brief Header file for Movie
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 // #TODO figure out how to make pure virtual? 
 // cant instaniate movie object in a log if its pure virtual see storeinventory.h:40

#pragma once

#include <string>

class Movie{
protected:

    const static char genre = '0'; // type of movie
    int stock; // quanty of movie in stock
    std::string director; // director of movie
    std::string title; // title of movie
    int year; // year released of movie

    // simulate virtual const static behavior
    virtual char type() { return genre; }

    virtual std::ofstream& print(std::ofstream&, Movie&);

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

    virtual bool operator<(const Movie&);
    virtual bool operator==(const Movie&);

    friend std::ofstream& operator<<(std::ofstream&, Movie&);

    int Borrow();
    int Return();

};