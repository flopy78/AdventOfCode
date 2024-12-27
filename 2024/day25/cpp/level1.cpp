#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using scheme = vector<string>;

vector<int> get_columns_size(const scheme &current_scheme) {
    vector<int> result = {-1,-1,-1,-1,-1}; //removing the first/last column
    for (int y = 0; y < current_scheme.size() ; y++) {
        for (int x = 0 ; x < current_scheme[y].size() ; x++) {
            if (current_scheme[y][x] == '#') result[x] ++;
        }
    }
    return result;
}

bool is_fitting(const vector<int> &key, const vector<int> &lock) {
    for (int i = 0 ; i < 5 ; i++) {
        if ((key[i] + lock[i]) > 5) { //7 rows, but the first one and the last one are excluded, so 5 left !
            return false;
        }
    }
    return true;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "file opening problem";
        return 1;
    }

    string buffer;
    vector<vector<int>> keys {};
    vector<vector<int>> locks {};
    scheme current_scheme {};

    while (getline(file,buffer)) {
        if (buffer == "") {
            if (current_scheme[0][0] == '.') {
                keys.push_back(get_columns_size(current_scheme));
            } else {
                locks.push_back(get_columns_size(current_scheme));
            }
        current_scheme = {};
        } else {
            current_scheme.push_back(buffer);
        }
    }
    if (current_scheme.size() > 0) {
        if (current_scheme[0][0] == '.') {
            keys.push_back(get_columns_size(current_scheme));
        } else {
            locks.push_back(get_columns_size(current_scheme));
        }
    }

    int n_fitting = 0;

    int n_poss = locks.size() * keys.size();
    int i = 0;
    for (const vector<int> &lock : locks) {
        for (const vector<int> &key : keys) {
            if (is_fitting(key,lock)) {
                n_fitting ++;
            }
            i++;
            cout << i << "/" << n_poss << endl;
        }

    }

    cout << n_fitting << endl;


    return 0;
}