# Func Spec

## Adatbázis terv
```C++
class Movie {
	string name;
	int year;
	int length;
	int box_office;
}

class Person {
	string name;
	URL profile_picture;
}

class Keyword {
	string keyword;
	bool is_category;
}

enum Role {
	// ?!
}

enum County {
	// ...
}

// Linking tables
class Movie_Role_Person {
	Movie movie;
	Role role;
	Person Person;
}

class Movie_Keyword {
	Movie movie;
	Keyword keyword;
}

class Movie_Country {
	Movie movie;
	Country country;
}

class Movie_Poster {
	Movie movie;
	URL poster;
}

class Movie_Trailer {
	Movie movie;
	URL trailer;
}

class Person_Picture {
	Person Person;
	URL poster;
}
```

## Software Stack
+ back end
 - flask
 - sqlite3
+ front end
+ maintenance
 - apache2
