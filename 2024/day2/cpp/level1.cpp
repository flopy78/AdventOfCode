#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<int> get_steps(vector<int> levels) {
    vector<int> steps;

    for (int i = 0 ; i < levels.size()-1 ; i++) {
        steps.push_back(levels[i+1]-levels[i]);
    }
    return steps;
}

bool is_safe(vector<int> steps) {
    int sign = 0;
    
    for (int step : steps) {
        if (abs(step)>3 || abs(step) < 1) {
            return false;
        }
        if (sign == 0) {
            sign = abs(step)/step;
        } else {
            if (abs(step)/step != sign) {
                return false;
            }
        }
    }
    return true;
}

int charInt(char c) {
    return c - '0';
}

vector<int> get_levels(string report) {
    vector<int> levels;

    for (char c : report) {
        if (c != ' ') levels.push_back(charInt(c));
    }
    return levels;
}

int main() {
    ifstream file("input.txt");
    string buffer;
    int n_safe = 0;
    if (!file.is_open()) {
        cerr << "Error while opening the file" << endl;
        return 1;
    }

    while (getline(file,buffer)) {
        vector<int> levels {get_levels(buffer)};
        vector<int> steps {get_steps(levels)};

        if (is_safe(steps)) n_safe ++;
    }
    cout << n_safe << endl;
    return 0;
}