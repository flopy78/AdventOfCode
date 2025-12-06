#include <iostream>
#include<string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    vector<string> lines;
    ifstream input ("input.txt");
    string buffer;

    while (getline(input,buffer)) {
        cout << buffer[buffer.size()-1];
        lines.push_back(buffer);
    }



    
    return 0;
}