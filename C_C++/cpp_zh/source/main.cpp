#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "Employee.hpp"
#include "Worker.hpp"
#include "Contractee.hpp"
#include "Manager.hpp"
#include "Company.hpp"

#include "help_message.h"

using namespace std;

/* globális példaértékű Company példány amin a "shell" operálhat
 */
Company mycompany("Beadandó Inc.");

// Ambiens Osztály

/* vissza adja a felhasználói input 'i'-edik mezejét,
 *  ahol a mezők white space szeparált string-ek ként vannak definiálva
 */
string parse_field(const string &line, int i) {
	/* ezt a függvényt könyebb C string-ekkel implementálni,
	 *  de az input std::string-ként jut ide kényelmesen,
	 *  ezért "átváltjuk"
	 */
	const char * line_p = line.c_str();	// mező eleje
	const char * end_p  = line_p;		// mező vége
	for (int h = 0; h < i; h++) {	// iterate
		line_p = end_p;
		while (isspace(*line_p)) {	// find begin
			++line_p;
		}
		end_p = line_p;
		while (!isspace(*end_p)		// find end
		&& *end_p != '\0') {
			++end_p;
		}
	}

	string r = string(line_p, (end_p) - line_p);

	return r;
}

/* felhasználói parancs értelmezése
 */
void command(const string &line) {
	if (line == "q") {		// "Quit"
		throw int();
	} else if (line[0] == 'h') {	// "Help"
		puts(help_message);
		return;
	} else if (line.substr(0, 2) == "c ") { // "Create"
		// ?! példa
		if (line.size() < 5) {
			return;
		}

		string name = parse_field(line, 3);
		//puts(name.c_str());

		const char type = line[2];
		Employee * e;
		switch (type) {
			case 'w': {
				e = (Employee *)(new Worker(name));
			} break;
			case 'c': {
				e = (Employee *)(new Contractee(name));
			} break;
			case 'm': {
				e = (Employee *)(new Manager(name, &mycompany));
			} break;
			default: {
				fputs("No employee created.", stderr);
				return;
			} break;
		}
		mycompany.employees.push_back(e);
		puts("Employee created.");
		return;
	} else if (line.substr(0, 2) == "i ") { // "Info"
		string id = parse_field(line, 2);

		Employee * e = mycompany.by_id(id);
		if (e) {
			e->details();
			puts("");
		}

		return;
	} else if (line.substr(0, 2) == "m ") { // "Modify"
		string id = parse_field(line, 2);
		string modification = parse_field(line, 3);

		Employee * e = mycompany.by_id(id);
		if (e) {
			puts(e->modify(modification) ? "Modification performed." : "Modification error.");
		}

		return;
	} else if (line.substr(0, 2) == "d ") {	// "Delete"
		string id = parse_field(line, 2);
		for (size_t i = 0; i < mycompany.employees.size(); i++) {
			if (std::to_string(mycompany.employees[i]->id_m) == id) {
				mycompany.employees.erase(mycompany.employees.begin() + i);
				break;
			}
		}

		return;
	} else if (line[0] == 'l') {	// "List"
		mycompany.print();
		return;
	/* ------
	 * a biztonsági mentés beégetve pusztán azért,
	 *  hogy kényelmesebb legyen tesztelni
	 */
	} else if (line[0] == 'w') {	// "Write"
		mycompany.bak("./data/bak.csv");
		return;
	} else if (line[0] == 'r') {	// "Read"
		mycompany.load("./data/bak.csv");
		return;
	/* ---
	 */
	} else {
		puts(help_message);
		return;
	}
}

void filter(unordered_set<Employee*> &s, const char * const f) {
	if (not *f) { return; }

	switch (f[0]) {
		case '.': {	// mező érték alapú szűrés
			for (const auto &i : mycompany.employees) {
				if (i->is_match(f)) {
					s.insert(i);
				}
			}
		} break;
		default: {	// feltehetőleg név
			auto t = mycompany.by_name(f);
			s.insert(t.begin(), t.end());
		} break;
	}
}

void search(string line) {
	/* vissza térési lista;
	 *  `set`, hogy ne kézzel kelljen duplikált bejegyzéseket ellenőrizni
	 */
	unordered_set<Employee*> r;

	/* space szeparált mezőnként szűrünk;
	 *  a találatokat hozzáfűzzük az eddigiekhez;
	 *  a szűrők között "vagy" kapcsolat áll fen
	 */
	char * dup = strdup(line.c_str()+1);
	const char * delim = " ";
	char * data = strtok(dup, delim);
	int i = 0;
	do {
		filter(r, data);
		++i;
	} while((data = strtok(NULL, delim), data));

	for (const auto &e : r) {
		e->details();
		puts("");
	}

	free(dup);
}

/* top-level user input kezelő
 */
void input() {
	// Beolvasás
	string line;
	fputs("$ ", stdout);
	std::getline(std::cin, line);

	if (std::cin.eof()) {
		puts("");
		throw int();
	}

	// Értelmezés
	switch (line[0]) {
		case '/': {	// keresés
			search(line);
		} break;
		default: {	// parancs
			command(line);		
		};
	}
}

bool init() {
	/* (lehet, hogy) keverjük a C/C++ I/O-t ezért szinkronizáljuk az
	 *  std iostream objektumokat az stdio függvényekkel;
	 *  számomra a C stílusú output és a C++ stílusú input esik kézre,
	 *  valós projektben persze csak az egyiket használnám
	 */
	std::ios_base::sync_with_stdio(true);
	return true; // megszokásból
}

signed main() {
	init();
	//#include "dummy_constructors.inc"
	//mycompany.bak("./data/employees.csv");
	
	if(mycompany.load("./data/employees.csv")) {
		fputs("Fatális hiba: adatok betöltése sikertelen", stderr);
		return 1;
	}

	mycompany.print();

	/* a kilépést kizárólag azért implementálom kivételel,
	 * mert szerettem volna kivételkezelést használni a programban,
     * de máshol sem lett volna kevésbe értelmetlen
	 */
	try {
		for (;;) {
			input();
		}
	} catch (...) {
		;
	}

	return 0;
}
