#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <bitset>

using namespace std;

uint64_t COUNT = 0;

vector<string> split(string str,char delim) {
    string buffer = "";
    vector<string> split {};

    for (char c : str) {
        if (c == delim) {
            split.push_back(buffer);
            buffer = "";
        } else {
            buffer += c;
        }
    }
    if (buffer.size() > 0) {
        split.push_back(buffer);
    }
    return split;
}

vector<int64_t> map_stoull(vector<string> input) {
    vector<int64_t> output {};
    for (string number : input) {
        output.push_back(stoull(number));
    }
    return output;
}

int64_t get_iter_output(int64_t A) {
    int64_t B = A%8;
    B=B^3;
    int64_t C = A/pow(2,B);
    B = B^5;
    B = B^C;
    return B%8;
}

vector<int64_t> execute(int64_t A, int64_t B, int64_t C) {
    vector<int64_t> output {};

    do {
        output.push_back(get_iter_output(A));
        A = A/8;

    } while (A != 0);
    return output;
}

int64_t find_previous_A(int64_t A, int64_t depth, const vector<int64_t> &program) {
    //cout << A << " " << depth << endl;
    if (depth == program.size()) {
        return A;
    }

    for (int rest = 0 ; rest < 8 ; rest++) {
        if (get_iter_output(A*8+rest) == program[program.size()-1-depth]) {
            int64_t new_A = find_previous_A(A*8+rest,depth+1,program);
            if (new_A != -1) {
                return new_A;
            }
        }
    }
    return -1;

}

int main() {
    ifstream file("input.txt");
    string buffer;

    for (int i = 0 ; i < 3 ; i++) {
        getline(file,buffer);
        vector<string> data = split(buffer,':');
    }

    getline(file,buffer); // empty line

    getline(file,buffer); // program

    for (const int64_t & out : execute(55593699,0,0)) {
        cout << out << ",";
    }
    cout << endl;

    
    vector<int64_t> program = map_stoull(split(split(buffer,' ')[1],','));
    cout << find_previous_A(0,0,program) << endl;

    return 0;
}