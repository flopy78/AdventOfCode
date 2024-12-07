#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

vector<long long> map_stoll(vector<string> values) {
    vector<long long> numeric_values;
    for (string val : values) {
        numeric_values.push_back(stoll(val));
    }
    return numeric_values;
}

vector<string> product(string iter,long long repeat) {
    vector<string> prod {""};
    for (long long i = 0 ; i < repeat ; i++) {
        vector<string> new_prod{};
        for (string comb : prod) {
            for (char elt : iter) {
                new_prod.push_back(comb+elt);
            }
        }
        prod = new_prod;
    }
    return prod;
}
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

long long compute(vector<long long> terms, string ops,long long result) {
    long long compute = terms[0];

    for (long long i = 0 ; i < ops.size() ; i++) {
        if (ops[i] == '+') {
            compute += terms[i+1];
        } else if (ops[i] == '*') {
            compute *= terms[i+1];
        } else if (ops[i] == 's') {
            compute = stoll(to_string(compute)+to_string(terms[i+1]));   
        }
        if (compute > result) {
            return compute;
        }
    }
    return compute;
}

bool is_solvable(long long result,vector<long long> terms) {
    for (string ops : product("*+s",terms.size()-1)) {
        if (compute(terms,ops,result) == result) {
            return true;
        }
    }
    return false;
}

int main() {
    auto start = high_resolution_clock::now();
    ifstream file("input.txt");
    string buffer;
    long long score = 0;
    while(getline(file,buffer)) {
        vector<string> data =  split(buffer,':');
        long long result = stoll(data[0]);
        vector<long long> terms = map_stoll(split(data[1].substr(1,data[1].size()-1),' '));
        if (is_solvable(result,terms)) {
            score += result;
        }
    }
    cout << score << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout << duration.count()/(1e6) << "s" << endl;
    return 0;
}