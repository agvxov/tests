#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//for i in *; do echo "\"$i\","; done | shuf
vector<wstring> input = {
	L"TF2",                                                                                                                                                                                                                                       
	L"Markdown",                                                                                                                                                                                                                                  
	L"Deeper",                                                                                                                                                                                                                                    
	L"Új mappa",                                                                                                                                                                                                                                  
	L"S.T.A.L.K.E.R",                                                                                                                                                                                                                             
	L"Archive",
	L"Uninstaller",
	L"Achievements",
	L"photoshop",
	L"Bingo",
	L"VPN",
	L"házidolgozatok",
	L"Java",
	L"diy",
	L"Fonts",
	L"Personal",
	L"README.README",
	L"OPERATIONS",
	L"Xcom",
	L"Sed",
	L"bant",
	L"VMs",
	L"installers",
	L"H",
	L"Threads",
	L"lib",
	L"Networking_n_shite",
	L"Music",
	L"Kutatás",
	L"Call of Duty",
	L"Bash",
	L"k",
	L"Shitdows",
	L"Minecraft",
	L"un",
	L"torrent",
	L"Tor",
	L"Firefox",
	L"CNIT",
	L"Linux",
	L"biz",
	L"C#",
	L"FalloutNV",
	L"Xonotic",
	L"Kdenlive",
	L"Grub",
	L"Templates",
	L"X.cdd",
	L"bin",
	L"C++",
	L"Adobe",
	L"God",
	L"Humor_doboz",
	L"maping tools",
	L"Beta-testing",
	L"DnD",
	L"texturák",
	L"Python",
	L"játék",
	L"Age of Empires 3",
	L"Assembly",
	L"g",
	L"Vim",
	L"Chess"
};

signed main(int argc, char* argv[]){
	sort(input.begin(), input.end(),
		+[](wstring f, wstring s){
			std::transform(f.begin(), f.end(), f.begin(), std::towlower);
			std::transform(s.begin(), s.end(), s.begin(), std::towlower);
			wcout << f << L" vs " << s << L": " << (wcscmp(f.c_str(), s.c_str()) < 0) << endl;
			if(wcscmp(f.c_str(), s.c_str()) < 0) return true;
			return false;
		}
	);

	for(int i = 0; i < input.size(); i++){
		wcout << input[i] << endl;
	}

	return 0;
}

