#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>

using namespace std;

int comp(const void*a, const void*b) {
    return *((int*)a) - *((int*)b);
}

int abs_diff(int a, int b) {
    return (a-b>0)?(a-b):(b-a);
}

int main() {
    string buffer;
    ifstream file("input.txt");

    vector<int> l1;
    vector<int> l2;

    if (!file.is_open()) {
        cerr << "Error while reading the file" << endl;
        return 1;
    }

    while (getline(file,buffer)) {
        l1.push_back(stoi(buffer.substr(0,buffer.find("   "))));
        l2.push_back(stoi(buffer.substr(buffer.find("   ")+3,buffer.size())));

    }
    qsort(l1.data(),l1.size(),sizeof(int),comp);
    qsort(l2.data(),l2.size(),sizeof(int),comp);

    int total_diff = 0;

    int n = l1.size();

    for (int i = 0 ; i < n ; i++) {
        total_diff += abs_diff(l1[i],l2[i]);
    }

    cout << total_diff << endl;

    return 0;
}