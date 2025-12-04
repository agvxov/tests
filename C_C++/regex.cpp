#include <iostream>
#include <regex>

using namespace std;

signed main(int argc, char* argv[]){

	typedef char char_t;

	const char_t str[] = R"del(lkhsa k d a hajsnr akns ppp)del";
	match_results<const char_t*> m;
	basic_regex<char_t> r(" a ");
	regex_match(str, str + strlen(str), m, r);

	//cout << m.size() << endl;


	const string str2 = R"del(lkhsa k d a hajsnr akns ppp)del";
	smatch sm;
	regex r2("a");
	//while(regex_match(begin(str2), end(str2), sm, r2)){
	//	cout << sm[1] << endl;
	//}

	cout << distance(regex_iterator<std::string::const_iterator>(str2.begin(), str2.end(), r2), regex_iterator<std::string::const_iterator>()) << endl;

	return 0;
}

