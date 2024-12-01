#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<unordered_map>

using namespace std;

int comp(const void*a, const void*b) {
    return *((int*)a) - *((int*)b);
}


int main() {
    string buffer;
    ifstream file("input.txt");

    unordered_map<int,int> count;

    int n_max = 1000;

    vector<int> l1;
    vector<int> l2;

    if (!file.is_open()) {
        cerr << "Error while reading the file" << endl;
        return 1;
    }
    int n1,n2;
    while (getline(file,buffer)) {
        n1 = stoi(buffer.substr(0,buffer.find("   ")));
        n2 = stoi(buffer.substr(buffer.find("   ")+3,buffer.size()));
        l1.push_back(n1);
        l2.push_back(n2);
        count[n2] ++;
    }
    int score = 0;
    for (int n1 : l1) score += n1*count[n1];

    cout << score << endl;


    return 0;
}