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

bool is_fully_connected(const unordered_map<string,Computer> &network, const unordered_set<string> & set, const string &start_name) {
    for (const string &computer_name : set) {
        if (find(network.at(computer_name).neighbours.begin(),network.at(computer_name).neighbours.end(),start_name) == network.at(computer_name).neighbours.end()) {
            return false;
        }
    }
    return true;
}

unordered_set<string> explore(const unordered_map<string,Computer> &network, const string &start_name) {
    unordered_set<string> explored = {start_name};
    unordered_set<string> opened_set = {start_name};
    unordered_set<string> new_set = {};

    while (opened_set.size() > 0) {
        new_set = {};

        for (const string &computer_name : opened_set) {
            for (const string &neighbour_name : network.at(computer_name).neighbours) {
                if (explored.find(neighbour_name) == explored.end()) {
                    if (is_fully_connected(network,explored,neighbour_name)) {
                        new_set.insert(neighbour_name);
                        explored.insert(neighbour_name);
                    }
                }
            }
        }
        opened_set = new_set;
    }
    return explored;
}

string find_minimum(unordered_set<string> set) {
    string mini = "";

    for (const string &name : set) {
        if (mini == "" || name < mini) {
            mini = name;
        }
    }
    return mini;
}

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

    unordered_set<string> largest_set;
    uint64_t largest_size = 0;

    for (const auto &computer : network) {
        unordered_set fully_connected = explore(network,computer.first);
        if (fully_connected.size() > largest_size) {
            largest_size = fully_connected.size();
            largest_set = fully_connected;
        }
    }

    while (largest_set.size() > 0) {
        string mini = find_minimum(largest_set);
        cout << mini << ",";
        largest_set.erase(largest_set.find(mini));
    }
    cout << endl;

}

