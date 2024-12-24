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

uint64_t n_possible(const string & design, const vector<string> &towels,unordered_map<string,uint64_t> &cache) {
    if (design.length()==0) return 1;
    uint64_t total = 0;
    for (const string &towel : towels) {
        if (design.starts_with(towel)) {
            uint64_t result;
            string new_design = design.substr(towel.length(),design.length());
            if (cache.find(design) == cache.end()) {
                result = n_possible(new_design,towels,cache);
                cache.insert({new_design,result});
            } else {
                result = cache.at(new_design);
            }
            total += result;

        }
    }
    return total;
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

    uint64_t n_possible_orders = 0;

    unordered_map<string,uint64_t> cache;

    int i = 0;
    while (getline(file,buffer)) {
        n_possible_orders += n_possible(buffer,towels,cache);
        i ++;
        cout << i << "/" << 400 << endl;
    }

    cout << n_possible_orders << endl;

}