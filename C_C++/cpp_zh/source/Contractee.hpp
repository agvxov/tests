#include "Employee.hpp"

class Contractee : Employee {
	int pay_per_hour_m;
	int hour_count_m;

public:
	Contractee(std::string name)
		: Employee(name), pay_per_hour_m(0), hour_count_m(0) {
	}

	Contractee(std::string name, int year_of_birth, int pay_per_hour, int hour_count)
		: Employee(name, year_of_birth), pay_per_hour_m(pay_per_hour), hour_count_m(hour_count) {
	}

	int get_cost(){
		const int i = pay_per_hour_m * hour_count_m;
		return i * (int)(i * 0.3);
	}

	int get_pay(){
		return get_cost();
	};

	void details() {
		common_details();
		printf(
			"\tHours worked last week: %7d\n"
			"\tHourly salary:          %7d\n"
			"\tCalculated pay:         %7d\n",
			pay_per_hour_m,
			hour_count_m,
			get_pay()
		);
	}

	bool modify(const std::string &modification) override {
		if (Employee::modify(modification)) { return true; }
		
		auto eq_pos = modification.find("=");
		try {
			if (modification.substr(0, eq_pos) == "pay") {
				pay_per_hour_m = std::stoi(modification.substr(eq_pos+1));
				return true;
			} else if (modification.substr(0, eq_pos) == "hour") {
				hour_count_m = std::stoi(modification.substr(eq_pos+1));
				return true;
			}
		} catch (...) {
			return false;
		}

		return false;
	}

	std::string serialize() {
		return std::string()
			+ "c;"
			+ Employee::serialize() + ";"
			+ std::to_string(pay_per_hour_m) + ";"
			+ std::to_string(hour_count_m)
			;
	}
};

