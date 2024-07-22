#include "Employee.hpp"

/* típus a Worker munka nap státuszának kifejezésére
 *  typepun-olva, hogy könnyeben szérializálható legyen;
 *  bár lenne értelme a Worker-en belül definiálni,
 *  globális, hogy kevésbe legyen fájdalmas használni
 */
typedef enum {
	FULL     = 'F',
	DAY_OFF  = 'X',
	WAS_SICK = 'O',
} workday_t;
/* egy ismerősöm nem rég rámutatott, hogy a "_t" suffix-ot lefoglalja a POSIX,
 *   így ez technikailag árt a portolhatóságnak
 */

class Worker : Employee {
	/* mindösze heti fizetéssel operálunk, az átláthatóságért
	 */
	static const int days = 7;

	int pay_per_day_m;
	/* ledolgozott napok adatai
	 */
	workday_t work_data_m[Worker::days];

	/* work_data_m átalakítása a serializációhoz (mentésnél)
	 */
	std::string work_data_to_string() {
		std::string r("");
		for (int i = 0; i < days; i++) {
			r += (char)work_data_m[i];
		}
		return r;
	}

	/* work_data_to_string() ellentettje
	 */
	int c_string_to_work_data(const char * const s) {
		const int l = strlen(s);
		int r = 0;
		for (int i = 0; i < std::max(l, 7); i++) {
			switch ((workday_t)s[i]) {	// az invalid karakterek ignorálásra kerülnek
				case FULL:    [[ fallthrough ]];
				case DAY_OFF: [[ fallthrough ]];
				case WAS_SICK:
					work_data_m[i] = (workday_t)s[i];
					++r;
					break;
			}
		}
		return r;
	}

	/* munka adatok naptár szerű megjelenítése
	 */
	char * work_table() {
		int magic_number = ((7*2)+2)*2;
		char * r = (char*)malloc(sizeof(char) * magic_number);
		char b[] = "\th k s c p S v\n";
		memcpy(r, b, sizeof(b)-1);
		char * listing_start = r + sizeof(b)-1 + 1;
		listing_start[-1] = '\t';
		memset(listing_start, ' ', 7*2);
		for (int i = 0; i < 7; i++) {
			char &slot = *(listing_start + i * 2);
			slot = (char)work_data_m[i];
		}
		r[magic_number-2] = '\n';
		r[magic_number-1] = '\0';

		return r;
	}

public:
	Worker(std::string name)
		: Employee(name) {
		for (int i = 0; i < Worker::days; i++) {
			work_data_m[i] = FULL;
		}
	}

	Worker(std::string name, int year_of_birth, int pay_per_day, const char * const work_data)
		: Employee(name, year_of_birth), pay_per_day_m(pay_per_day) {
		c_string_to_work_data(work_data);
	}

	Worker(std::string name, int year_of_birth, int pay_per_day, workday_t * work_data)
		: Employee(name, year_of_birth), pay_per_day_m(pay_per_day) {
		for (int i = 0; i < Worker::days; i++) {
			work_data_m[i] = work_data[i];
		}
	}

	bool modify(const std::string &modification) override {
		if (Employee::modify(modification)) { return true; }
		
		auto eq_pos = modification.find("=");
		if (modification.substr(0, eq_pos) == "pay") {
			try {
				pay_per_day_m = std::stoi(modification.substr(eq_pos+1));
				return true;
			} catch (...) {
				return false;
			}
		} else if(modification.substr(0, eq_pos) == "performance") {
			c_string_to_work_data(modification.substr(eq_pos+1).c_str());
		}

		return false;
	}

	int get_cost(){
		/* munka napok öszegzése a nap enum értékétől függően súlyozva
		 */
		return std::accumulate(std::begin(work_data_m), std::end(work_data_m), 0, [this](int sum, int e) {
			int r;
			switch (e) {
				case FULL: {
					r = pay_per_day_m;
				} break;
				case WAS_SICK: {
					r = (int)(DAY_OFF * 0.6);
				} break;
				default: {
					r = 0;
				};
			}
			return sum + r;
		});
	};

	int get_pay(){
		return get_cost();
	};

	void details() {
		common_details();
		printf(
			"%s"
			"\tCalculated pay: %d\n",
			work_table(),
			get_pay()
		);
	};

	std::string serialize() {
		return std::string()
			+ "w;"
			+ Employee::serialize() + ";"
			+ std::to_string(pay_per_day_m) + ";"
			+ work_data_to_string()
			;
	}
};

