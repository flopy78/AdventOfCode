#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

struct Computer {
    string name;
    vector<string> neighbours;
};


size_t hashString(const string &key) {
    size_t hashCode = 0;
    int i = 0;
    for (const char &c : key) {
        hashCode += c * pow(17,i);
        i++;
    }
    return hashCode;
}

template<>
struct std::hash<Computer> {
    size_t operator()(const Computer &value) const {
        return hashString(value.name);
    }
};

template<>
struct std::hash<unordered_set<string>> {
    size_t operator()(const unordered_set<string> &value) const {
        size_t hashValue = 0;
        for (const string &elt : value) hashValue += hashString(elt);
        return hashValue;
    }
};

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "file problem" << endl;
        return 1;
    }
    string buffer;

    unordered_map<string,Computer> network;

    while (getline(file,buffer)) {
        string computer1_name = buffer.substr(0,2);
        string computer2_name = buffer.substr(3,5);
        if (network.find(computer1_name) == network.end()) {
            Computer computer1 = {computer1_name,{computer2_name}};
            network.insert({computer1_name,computer1});
        } else {
            network.at(computer1_name).neighbours.push_back(computer2_name);
        }
        if (network.find(computer2_name) == network.end()) {
            Computer computer2 = {computer2_name,{computer1_name}};
            network.insert({computer2_name,computer2});
        } else {
            network.at(computer2_name).neighbours.push_back(computer1_name);
        }
    }

    uint64_t n_triplets_with_t = 0;
    unordered_set<unordered_set<string>> found_triplets;

    for (auto computer : network) {
        if (computer.first[0] == 't') {
            for (int i = 0 ; i < computer.second.neighbours.size() ; i++) {
                for (int j = i ; j < computer.second.neighbours.size() ; j++) {
                    Computer neighbour1 = network.at(computer.second.neighbours[i]);
                    if (find(neighbour1.neighbours.begin(),neighbour1.neighbours.end(),computer.second.neighbours[j]) != neighbour1.neighbours.end()) {
                        if (!found_triplets.contains({computer.first,computer.second.neighbours[i],computer.second.neighbours[j]})) {
                            n_triplets_with_t  ++;
                            found_triplets.insert({computer.first,computer.second.neighbours[i],computer.second.neighbours[j]});
                            cout << computer.first << " " << computer.second.neighbours[i] << " " << computer.second.neighbours[j] << endl;
                        }

                    }

                }
            }
        }
    }

    cout << n_triplets_with_t << endl;



}

