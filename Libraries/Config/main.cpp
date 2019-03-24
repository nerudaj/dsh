#include <Config.hpp>
#include <algorithm>

using cfg::Item;

int main() {
	cfg::Csv csv;
	csv.setHeaders({Item("id"), Item("name"), Item("age")});
	csv.resize(3, 3);
	
	csv[0][0] = 3;
	csv[0][1] = "doomista";
	csv[0][2] = 19;
	
	csv[1][0] = 1;
	csv[1][1] = "papooch";
	csv[1][2] = 23;
	
	csv[2][0] = 2;
	csv[2][1] = "derb";
	csv[2][2] = 69;
	
	std::sort(csv.begin(), csv.end(), [](const auto &a, const auto &b) {
		return a[0].asInt() < b[0].asInt();
	});
	
	csv.saveToFile("output.csv");
	
	return 0;
}