#ifndef MANAGER_H
#define MANAGER_H

#include "Company.hpp"

class Manager : Employee {
	/* fix fizetés
	 */
	int pay_m;
	Company * company_m;

public:
	Manager(std::string name, Company * company)
		: Employee(name), pay_m(0), company_m(company) {
	}

	Manager(std::string name, int year_of_birth, int pay, Company * company)
		: Employee(name, year_of_birth), pay_m(pay), company_m(company) {
	}

	// ### ###

	int get_cost() override {
		return pay_m;
	}

	/* "ennek megfelelő levonást (egészen 0-ig)" kitűzés teljesítése
	 */
	int get_pay() {
		int r = (signed long long)(company_m->profit() * 0.01);
		return std::max(get_cost() + r, 0);
	}

	virtual void details() {
		common_details();
		printf(
			"\tBase pay:       %7d\n"
			"\tCalculated pay: %7d\n",
			get_cost(),
			get_pay()
		);
	}

	bool modify(const std::string &modification) override {
		if (Employee::modify(modification)) { return true; }
		
		auto eq_pos = modification.find("=");
		try {
			if (modification.substr(0, eq_pos) == "pay") {
				pay_m = std::stoi(modification.substr(eq_pos+1));
				return true;
			}
		} catch (...) {	// lehetséges `invalid_argument` vagy `out_of_range`
			return false;
		}

		return false;
	}

	std::string serialize() {
		return std::string()
			+ "m;"
			+ Employee::serialize() + ";"
			+ std::to_string(pay_m) + ";"
			+ company_m->name_m
			;
	}
};

#endif
