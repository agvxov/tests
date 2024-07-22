#include "Company.hpp"
#include "Manager.hpp"

/* header-only CSV könyvtár
 *  https://github.com/d99kris/rapidcsv
 */
#include "rapidcsv.h"

/* Close Coupling;
 *  lásd: switch()
 *  ideális esetben lenne egy factory, hogy Company ne függjön minden Employee leszármazottól,
 *  vizont abban az esetben nem lenne alkalmam használni a rapidcsv-t
 */
#include "Worker.hpp"
#include "Contractee.hpp"
#include "Manager.hpp"

using namespace std;
using namespace rapidcsv;

/* ez a függvény azért lett itt definiálva mert így nem függ az egész osztály a rapidcsv-től;
 *  és nyugodtan használhatjuk a namespaced "szennyezés" nélkül
 */
int Company::load(const char * const file) {
	try{
		/* LabelParams(-1, -1) - nincs se header sor, se oszlop
		 */
		Document csv(file, LabelParams(-1, -1), SeparatorParams(';'));
	 
		for (size_t i = 0; i < csv.GetRowCount(); i++) {
			Employee * e;

			/* legjobb tudomásom szerint a rapidcsv csak homogén mezőkkel dolgozok
			 *  mivel a mi mezőink kevertek, így kénytelenek vagyunk std::string-ből
			 *  kézzel állapítjuk meg a megfelelő értékeket
			 */
			const auto& row = csv.GetRow<string>(i);

			string name = row[1];
			int y       = stoi(row[2]);

			/* az első char indikálja milyen tipusú Employee-t kell constructálni
			 */
			switch (row[0][0]) {
				case 'w': {
					int p    = stoi(row[3]);
					string w = row[4];

					e = (Employee*)(new Worker(name, y, p, w.c_str()));
				} break;
				case 'c': {
					int p = stoi(row[3]);
					int h = stoi(row[4]);

					e = (Employee*)(new Contractee(name, y, p, h));
				} break;
				case 'm': {
					int p = stoi(row[3]);

					e = (Employee*)(new Manager(name, y, p, this));
				} break;
				default: {
				};
			}

			employees.push_back(e);
		}
	} catch(...) {
		return 1;
	}

	// implicit csv.close()	// (a deconstructor kezeli)
	return 0;
}
