-- Insert dummy data for Movie
INSERT INTO Movie (title, year, length, box_office)
VALUES 
    ('The Silly Adventure', 2000, 120, 1000000),
    ('Crazy World', 2005, 90, 800000),
    ('Funky Journey', 2010, 110, 1200000),
    ('Whacky Wonderland', 2015, 95, 900000),
    ('The Zany Quest', 2018, 105, 1500000),
    ('Sillyville Chronicles', 2020, 100, 2000000),
    ('Hilarious Heights', 2013, 85, 700000),
    ('Bonkers Express', 2008, 115, 1100000),
    ('Laughland Adventures', 2019, 98, 1800000),
    ('Nonsensical Odyssey', 2003, 105, 950000);

-- Insert dummy data for Person
INSERT INTO Person (name, profile_picture)
VALUES 
    ('Silly McSillerson', 'https://example.com/silly_pic1.jpg'),
    ('Goofy Goober', 'https://example.com/goofy_pic1.jpg'),
    ('Chuckling Charlie', 'https://example.com/charlie_pic1.jpg'),
    ('Lighthearted Larry', 'https://example.com/larry_pic1.jpg'),
    ('Giggles McGiggleton', 'https://example.com/giggles_pic1.jpg');

-- Insert dummy data for Keyword
INSERT INTO Keyword (keyword, is_category)
VALUES 
    ('Hilarity', 1),
    ('Whimsical', 1),
    ('Laughs', 1),
    ('Absurd', 1),
    ('Silly', 1);

-- Insert dummy data for Role
INSERT INTO Role (role_name)
VALUES 
    ('Actor'),
    ('Director'),
    ('Producer'),
    ('Writer');

-- Insert dummy data for Country
INSERT INTO Country (country_name)
VALUES 
    ('USA'),
    ('UK'),
    ('Canada'),
    ('Australia'),
    ('France');

-- Insert dummy data for Movie_Role_Person (assigning random roles to people for movies)
INSERT INTO Movie_Role_Person (movie_id, role_id, person_id)
VALUES 
    (1, 1, 1),
    (1, 2, 2),
    (2, 1, 3),
    (2, 2, 4),
    (3, 1, 5),
    (3, 2, 1),
    (4, 1, 2),
    (4, 2, 3),
    (5, 1, 4),
    (5, 2, 5);

-- Insert dummy data for Movie_Keyword (assigning keywords to movies)
INSERT INTO Movie_Keyword (movie_id, keyword_id)
VALUES 
    (1, 1),
    (1, 3),
    (2, 2),
    (2, 4),
    (3, 1),
    (3, 5),
    (4, 2),
    (5, 3),
    (6, 1),
    (7, 2);

-- Insert dummy data for Movie_Country (assigning countries to movies)
INSERT INTO Movie_Country (movie_id, country_id)
VALUES 
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 4),
    (5, 5),
    (6, 1),
    (7, 2),
    (8, 3),
    (9, 4),
    (10, 5);

-- Insert dummy data for Movie_Poster (assigning posters to movies)
INSERT INTO Movie_Poster (movie_id, poster)
VALUES 
    (1, 'https://example.com/movie1_poster.jpg'),
    (2, 'https://example.com/movie2_poster.jpg'),
    (3, 'https://example.com/movie3_poster.jpg'),
    (4, 'https://example.com/movie4_poster.jpg'),
    (5, 'https://example.com/movie5_poster.jpg'),
    (6, 'https://example.com/movie6_poster.jpg'),
    (7, 'https://example.com/movie7_poster.jpg'),
    (8, 'https://example.com/movie8_poster.jpg'),
    (9, 'https://example.com/movie9_poster.jpg'),
    (10, 'https://example.com/movie10_poster.jpg');

-- Insert dummy data for Movie_Trailer (assigning trailers to movies)
INSERT INTO Movie_Trailer (movie_id, trailer)
VALUES 
    (1, 'https://example.com/movie1_trailer.mp4'),
    (2, 'https://example.com/movie2_trailer.mp4'),
    (3, 'https://example.com/movie3_trailer.mp4'),
    (4, 'https://example.com/movie4_trailer.mp4'),
    (5, 'https://example.com/movie5_trailer.mp4'),
    (6, 'https://example.com/movie6_trailer.mp4'),
    (7, 'https://example.com/movie7_trailer.mp4'),
    (8, 'https://example.com/movie8_trailer.mp4'),
    (9, 'https://example.com/movie9_trailer.mp4'),
    (10, 'https://example.com/movie10_trailer.mp4');

-- Insert dummy data for Person_Picture (assigning pictures to people)
INSERT INTO Person_Picture (person_id, poster)
VALUES 
    (1, 'https://example.com/person1_pic.jpg'),
    (2, 'https://example.com/person2_pic.jpg'),
    (3, 'https://example.com/person3_pic.jpg'),
    (4, 'https://example.com/person4_pic.jpg'),
    (5, 'https://example.com/person5_pic.jpg');
