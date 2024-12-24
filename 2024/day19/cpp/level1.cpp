#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <cstdint>

using namespace std;

vector<string> split(const string &str) {
    int i = 0;
    string  buffer("");
    vector<string> split;
    while (i < str.length()) {
        if (i+1 < str.length() && str[i] == ',' && str[i+1] == ' ') {
            split.push_back(buffer);
            i += 2;
            buffer = "";
        } else {
            buffer += str[i];
            i++;
        }
    }
    split.push_back(buffer);
    return split;
}

bool is_possible(const string & design, const vector<string> &towels,unordered_map<string,bool> &cache) {
    if (design.length()==0) return true;

    for (const string &towel : towels) {
        bool result;
        if (design.starts_with(towel)) {
            string new_design = design.substr(towel.length(),design.length());
            if (cache.find(design) == cache.end()) {
                result = is_possible(new_design,towels,cache);
                cache.insert({new_design,result});
            } else {
                result = cache.at(new_design);
            }

            if (result) return true;

        }
    }
    return false;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "file error" << endl;
        return 1;
    }
    string buffer;
    getline(file,buffer);
    vector<string> towels = split(buffer);

    getline(file,buffer); // empty line

    uint64_t n_possible = 0;

    unordered_map<string,bool> cache;

    int i = 0;
    while (getline(file,buffer)) {
        if (is_possible(buffer,towels,cache)) {
            n_possible ++;
        }
        i ++;
        cout << i << "/" << 400 << endl;
    }

    cout << n_possible << endl;

}