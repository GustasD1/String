#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream> 
#include <chrono>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <chrono>
#include <deque>
#include <map>
#include <regex>


using std::vector;
using std::string;
using std::cout;
using std::sort;
class tekstas {
public:
	string zodis;
	int kiek=0;
	vector<int> linijos;

};
void skaitymas(vector<tekstas>& temp, vector<string> & url);
void pasikartojimai(vector<tekstas>& temp, vector<tekstas>& temp2);
int main() {
	vector<tekstas> temp;
	vector<tekstas> temp2;
	vector <string>url;

	skaitymas(temp,url);
	cout << "url adresai:" << std::endl;
	for (int i = 0; i < url.size(); i++) {
		cout << url[i] << std::endl;

	}
	pasikartojimai(temp, temp2);
	std::ofstream fr("output.txt");
	fr << std::left << std::setw(20) << "Zodziai" << "\t" << "Pasikartojo" << std::setw(5) << "\t" << "Eilutes kuriose galima rasti zodzius " << std::endl;
	for (int i = 0; i < temp2.size(); i++) {

		if (temp2[i].kiek > 1 && temp2[i].zodis != "") {
			fr << std::left << std::setw(20) << temp2[i].zodis << "\t" << temp2[i].kiek<<std::setw(14)<<" \t";
			for (int j = 0; j < temp2[i].linijos.size(); j++) {
				fr<< temp2[i].linijos[j] << " ";
			}
			fr << "" << std::endl;
	

		}

	}

	
	return 0;
}
void skaitymas(vector<tekstas>& temp, vector<string> & url) {
	std::fstream file;
	file.open("tekstas.txt");
	string eil;
	std::stringstream buf;
	int pazymys;
	int k = 0;
	temp.resize(1);
	tekstas laik;
	int kiekis = 1;
	std::regex regUrl("\\b((?:https?|ftp|file|)://[-a-zA-Z0-9+&@#/%?=~_|!:, .;]*[-a-zA-Z0-9+&@#/%=~_|])");
	while (file>>laik.zodis) {

		if (regex_match(laik.zodis, regUrl)) {
			url.push_back(laik.zodis);
		}
		temp.push_back(laik);
		kiekis++;
		temp.resize(kiekis);
	}


}
void pasikartojimai(vector<tekstas>& temp, vector<tekstas>& temp2) {
	std::ofstream fr("output.txt");

	tekstas laik;
	std::map<string, int> mp;
	vector<string> v1;
	string chars = "#!,%.)(–--";
	for (int i = 0; i < temp.size(); i++) {
		v1.push_back(temp[i].zodis);
	}
	for (int i = 0; i < v1.size(); i++) {
		string s = v1[i];
		for (char c : chars) {
			s.erase(std::remove(s.begin(), s.end(), c), s.end());
		}
		v1[i] = s;

	}

	for (auto v : v1) {
		size_t n = std::count(v1.begin(), v1.end(), v);
		mp[v] = n;
	}
	for (auto mvalue : mp) {
		laik.zodis = mvalue.first.c_str();
		laik.kiek = mvalue.second;
		temp2.push_back(laik);
	}
	string line;
	int linija = 1;
	string laikinas2;
	size_t laikinas;



	for (int i = 0; i < temp2.size(); i++) {
		std::ifstream fd("tekstas.txt");
		if (temp2[i].kiek > 1 && temp2[i].zodis != "") {
			while (getline(fd, line)) {
				std::istringstream iss(line);
				while (iss >> laikinas2) {
					for (char c : chars) {
						laikinas2.erase(std::remove(laikinas2.begin(), laikinas2.end(), c), laikinas2.end());
					}
					if (temp2[i].zodis == laikinas2) {
						temp2[i].linijos.push_back(linija);
					}
				}
				linija++;
			}
			linija = 1;
		}
	}
	for (int i = 0; i < temp2.size(); i++) {
		sort(temp2[i].linijos.begin(), temp2[i].linijos.end());
		temp2[i].linijos.erase(unique(temp2[i].linijos.begin(), temp2[i].linijos.end()), temp2[i].linijos.end());
	}


}

			


