#!/bin/env sqlite3

PRAGMA foreign_keys = OFF; -- Disable foreign key checking

-- Drop tables if they exist
DROP TABLE IF EXISTS Movie_Role_Person;
DROP TABLE IF EXISTS Movie_Keyword;
DROP TABLE IF EXISTS Movie_Country;
DROP TABLE IF EXISTS Movie_Poster;
DROP TABLE IF EXISTS Movie_Trailer;
DROP TABLE IF EXISTS Person_Picture;
DROP TABLE IF EXISTS Movie;
DROP TABLE IF EXISTS Person;
DROP TABLE IF EXISTS Keyword;
DROP TABLE IF EXISTS Role;
DROP TABLE IF EXISTS Country;

PRAGMA foreign_keys = ON; -- Re-enable foreign key checking

-- Create tables
CREATE TABLE Movie (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT,
    year INTEGER,
    length INTEGER,
    box_office INTEGER
);

CREATE TABLE Person (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    profile_picture TEXT
);

CREATE TABLE Keyword (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    keyword TEXT,
    is_category INTEGER
);

CREATE TABLE Role (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    role_name TEXT
);

CREATE TABLE Country (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    country_name TEXT
);

CREATE TABLE Movie_Role_Person (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    movie_id INTEGER,
    role_id INTEGER,
    person_id INTEGER,
    FOREIGN KEY (movie_id) REFERENCES Movie(id),
    FOREIGN KEY (role_id) REFERENCES Role(id),
    FOREIGN KEY (person_id) REFERENCES Person(id)
);

CREATE TABLE Movie_Keyword (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    movie_id INTEGER,
    keyword_id INTEGER,
    FOREIGN KEY (movie_id) REFERENCES Movie(id),
    FOREIGN KEY (keyword_id) REFERENCES Keyword(id)
);

CREATE TABLE Movie_Country (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    movie_id INTEGER,
    country_id INTEGER,
    FOREIGN KEY (movie_id) REFERENCES Movie(id),
    FOREIGN KEY (country_id) REFERENCES Country(id)
);

CREATE TABLE Movie_Poster (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    movie_id INTEGER,
    poster TEXT,
    FOREIGN KEY (movie_id) REFERENCES Movie(id)
);

CREATE TABLE Movie_Trailer (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    movie_id INTEGER,
    trailer TEXT,
    FOREIGN KEY (movie_id) REFERENCES Movie(id)
);

CREATE TABLE Person_Picture (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    person_id INTEGER,
    poster TEXT,
    FOREIGN KEY (person_id) REFERENCES Person(id)
);
