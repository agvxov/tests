// @BAKE g++ $@ -o $*; ./$*
#include <map>
#include <stdio.h>

using namespace std;

signed main() {
    //std::map<char, std::map<char, int>> charMapOfMaps = {
    //    {'a', {{'x', 1}, {'y', 2}, {'z', 3}}},
    //    {'b', {{'x', 4}, {'y', 5}, {'z', 6}}},
    //    {'c', {{'x', 7}, {'y', 8}, {'z', 9}}}
    //};
	map<char, map<char, int>> m = {
		{ 'o', { {'k', 1}, {'o', 3} }},
		{ 'p', {{'l', 2} }},
	};
}
