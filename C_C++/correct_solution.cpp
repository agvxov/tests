#include <iostream>

using namespace std;

bool using_a_macro_would_be_cheating_because_the_preprocessor_would_literally_fill_up_the_main_and_do_the_one_thing_thats_not_allowed_at_the_challenge(){ cout << "Hello world" << endl; return 1; }

bool globals_are_the_way = using_a_macro_would_be_cheating_because_the_preprocessor_would_literally_fill_up_the_main_and_do_the_one_thing_thats_not_allowed_at_the_challenge();

int main(){}

//i have heard of this challenge and gave up after 5 minutes (cause i was drunk), the solution that came up 3 times in a row was to use a macro; i felt like i was cheates (see at the bool declaration); it has annoyed me for the past
//month, now that i, on my own managed to come up with a solution thats not bullshit, im happy
