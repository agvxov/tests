// @COMPILECMD g++ $@ -lboost_date_time
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main() {
    int year = 2023;
    int month = 7;

    boost::gregorian::date firstDay(year, month, 1);
    boost::gregorian::date::day_of_week_type weekday = firstDay.day_of_week();

    std::cout << "The first day of " << month << "/" << year << " is a " << weekday << std::endl;

    return 0;
}
