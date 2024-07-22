#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <numeric>

/* Dolgozó ős osztály
 */
class Employee {
public:
	/* ezt át menetileg használtam
	 */
  #if 0
	/* Csúnya hack, hogy valami id/hash szerűséget kapjak
	 *  nem 64bites rendszereken szörnyű bugokat okozna
	 */
	string id(){
		string r = std::to_string((long)this).substr(12);
		while (r.size() != 4) {
			r.insert(0, 1, '0');
		}
		return r;
	}
  #endif

	/* "elsődleges kulcs"
	 */
	int id_m;
	std::string name_m;
	int year_of_birth_m;

	/* alap értelmezett érték születési dátumokhoz, a UNIX epoch után
	 */
	const static int myepoc = 1970;

	/* az id_m kiosztására használatos érték;
	 *  minden Employee létrehozásával növekszik
	 */
	static int id_head;

	// ### ###

	Employee(const std::string& name) : Employee(name, myepoc) { ; }

	Employee(const std::string& name, int year_of_birth) : name_m(name), year_of_birth_m(year_of_birth) {
		id_m = id_head++;
	}

	virtual ~Employee() { ; }

	virtual int get_cost() = 0;
	virtual int get_pay()  = 0;
	virtual void details() = 0;

	virtual std::string serialize() {
		return std::string() // üres string, hogy használhassuk a '+' operátort
			// + std::to_string(id) + ";"
			+ name_m + ";"
			+ std::to_string(year_of_birth_m)
			;
	}

	/* felhasználó álltali módosításra használt függvény;
	 *  a sikerességet adja vissza;
	 *  minden override először meghívja ezt a függvényt
	 */
	virtual bool modify(const std::string &modification) {
		auto eq_pos = modification.find("=");
		if (eq_pos == std::string::npos) {
			return false;
		}
		
		if (modification.substr(0, eq_pos) == "birth") {
			try {
				year_of_birth_m = std::stoi(modification.substr(eq_pos+1));
				return true;
			} catch (...) {
				return false;
			}
		}

		return false;
	}

	/* segéd függvény az is_match() számára
	 */
	/* bár technikailag csak int-ekkel dolgozunk,
	 *  semmi akadája például string-ekkel bővíteni
	 */
	template<typename T>
	bool mycompare(char c, T a, T b) {
		switch (c) {
			case '>': {
				return a > b;
			};
			case '<': {
				return a < b;
			};
			case '=': {
				return a == b;
			};
		}
		return false;
	}

	bool is_match(const char * const filter) {
		size_t del = strcspn(filter, "<=>");
		if (del == strlen(filter)) { return false; }

		try {	// lehetséges konverziós hiba
			std::string_view field(filter, del);
			if (field == ".id") {
				return mycompare(filter[del], this->id_m, std::stoi(filter + del + 1));
			} else if (field == ".yeaf_of_birth") {
				return mycompare(filter[del], this->year_of_birth_m, std::stoi(filter + del + 1));
			}
		} catch (...) { ; }

		return false;
	}

protected:

	void common_details () {
		printf("#%s: %s (%d)\n",
			std::to_string(id_m).c_str(), name_m.c_str(), year_of_birth_m
		);
	}
};
#endif
