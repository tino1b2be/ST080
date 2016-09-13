/**
	Small C++ program to convert samples exported from Audacity to an array format that can be used in the ST080 program.

	@author Tinotenda Chemvura
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main() {

    ifstream f("audio/kick_1.csv");
    vector<string> f1;
    string line;
    for (int i = 0; i < 5000; ++i){
        getline(f,line);
        f1.push_back(line);
    }
    f.close();

    ofstream o("stuff/f.txt");
    for(int i = 0; i < f1.size(); ++i){
        o << f1[i] << ",";
    }
    o.close();
    return 0;
}
