#ifndef COMPANY_H
#define COMPANY_H

#include "Employee.hpp"

#include <stdio.h>
#include <vector>
#include <numeric>
#include <fstream>

/* Container class a dolgozók számára
 */
class Company {
	/* "a cég bejegyzett neve"
	 */
	std::string name_m;
	/* "bevétel amit a Manager-ek osztalékának megállapítására használunk"
	 */
	signed long long revenue_m = 1000000;

	/* "segéd függvény a cég kiadásainak kiszámítására;"
	 */
	signed long long spendings() {
		/* "tetetjük, hogy az egyetlen kiadás az összes dolgozó fizetésének összege lenne"
		 */
		return std::accumulate(std::begin(employees), std::end(employees), 0, [this](int sum, Employee * e) {
			return sum + e->get_cost();
		});
	}

	/* a Manager letárolja melyik cégnél dolgozik és olvas belőlle
	 *  bár a `friend` haszánálata itt nem kifejezetten indokolt,
	 *  a sokszínűség kedvéért ez is egy megoldás
	 */
	friend class Manager;

public:
	std::vector<Employee*> employees;

	Company(const char * const name) : name_m(name) { }

	~Company() {
		for (auto e : employees) {
			delete e;
		}
	}

	signed long long profit() {
		return revenue_m - spendings();
	}

	// ### Employee keresés ###
	Employee * by_id(const std::string &id) {
		for (const auto &i : employees) {
			if (std::to_string(i->id_m) == id) {
				return i;
			}
		}

		return nullptr;
	}

	std::vector<Employee*> by_name(const char * const query) {
		std::vector<Employee*> r;
		for (const auto &i : employees) {
			/* case érzékeny substring keresés
			 */
			if (i->name_m.find(query) != std::string::npos) {
				r.push_back(i);
			}
		}

		return r;
	}


	// ### Tárolás ###
	
	/* A tárolás CSV fáljba történik;
	 *  praktikai okoból a dolgozókat tároljuk
	 */

	/* "BAcK up" függvény
	 */
	int bak(const char * const file) {
		std::ofstream ofile(file);
		if (not ofile.is_open()) {
			fputs("Failed to write Company to disk.\n", stderr);
			return 1;
		}
		for (const auto &e : employees) {
			ofile << e->serialize() << std::endl;
		}
		ofile.close();
		return 0;
	}

	int load(const char * const file);

	// ### Megjelenítésre használt függvények ###
	void details() {
		printf("-- %s\n"
			"\tNumber of employees: %ld\n"
			"\tRevenue: %lld\n"
			"\tProfit:  %lld\n",
			name_m.c_str(),
			employees.size(),
			revenue_m,
			profit()
		);
	}

	void list_employees() {
		for (auto e : employees) {
			printf("#%-3s : %-10s %7d\n",
				std::to_string(e->id_m).c_str(),
				e->name_m.c_str(),
				e->get_pay()
			);
		}
	}

	void print() {
		details();
		puts("");
		list_employees();
		puts("\n");
	}

};

#endif
