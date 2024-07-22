/* inline constructor calls;
 * ".inc" kiterjesztés, hogy jelezze nem lehet vele úgy bánni mint egy teljes értékű forrás fájlal,
 * hiszen globális kontextusban nem valid;
 * ezt a fájlt fejlesztés közben használtam, jelenleg nem "szerepel" sehol;
 * ez a fálj auto generálva volt
 */

workday_t worker1_data[7] = { FULL, FULL, DAY_OFF, FULL, FULL, FULL, DAY_OFF };
mycompany.employees.push_back((Employee*)(new Worker("Alice", 1990, 100, worker1_data)));

workday_t worker2_data[7] = { FULL, FULL, FULL, FULL, FULL, FULL, FULL };
mycompany.employees.push_back((Employee*)(new Worker("Bob", 1985, 120, worker2_data)));

workday_t worker3_data[7] = { WAS_SICK, WAS_SICK, DAY_OFF, WAS_SICK, WAS_SICK, WAS_SICK, DAY_OFF };
mycompany.employees.push_back((Employee*)(new Worker("Charlie", 1995, 90, worker3_data)));

workday_t worker4_data[7] = { DAY_OFF, DAY_OFF, DAY_OFF, DAY_OFF, DAY_OFF, DAY_OFF, DAY_OFF };
mycompany.employees.push_back((Employee*)(new Worker("David", 1988, 110, worker4_data)));

workday_t worker5_data[7] = { FULL, FULL, FULL, FULL, FULL, DAY_OFF, FULL };
mycompany.employees.push_back((Employee*)(new Worker("Eva", 1992, 105, worker5_data)));

workday_t worker6_data[7] = { WAS_SICK, WAS_SICK, WAS_SICK, WAS_SICK, WAS_SICK, WAS_SICK, WAS_SICK };
mycompany.employees.push_back((Employee*)(new Worker("Fiona", 1980, 95, worker6_data)));


mycompany.employees.push_back((Employee*)(new Contractee("Grace", 1993, 20, 40)));
mycompany.employees.push_back((Employee*)(new Contractee("Henry", 1987, 25, 30)));
mycompany.employees.push_back((Employee*)(new Contractee("Ivy", 1998, 18, 35)));
mycompany.employees.push_back((Employee*)(new Contractee("Jack", 1991, 22, 25)));

mycompany.employees.push_back((Employee*)(new Manager("John", 1980, 80000, &mycompany)));
mycompany.employees.push_back((Employee*)(new Manager("Jane", 1985, 85000, &mycompany)));
