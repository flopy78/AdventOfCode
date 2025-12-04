#include<iostream>
#include<fstream>
#include<string>
#include<cstdint>

using namespace std;


int max_idx(string seq,int begin, int end) {
    char maxi = '0';
    int max_idx = begin;
    for (int i = begin ; i < end ; i++) {
        if (seq[i] > maxi) {
            maxi = seq[i];
            max_idx = i;

        }
    }
    return max_idx;
}


uint64_t get_max_joltage(string line) {
    cout << line << endl;
    char max_joltage_str[12];
    int idx = 0;
    for (int i = 0 ; i < 12 ; i++) {
        idx = max_idx(line,idx,line.size()-(12-i)+1);

        max_joltage_str[i] = line[idx];
        idx ++;
    }
    return atoll(max_joltage_str);
}

int main() {
    uint64_t total_joltage = 0;
    ifstream input ("input.txt");
    string line;
    if (input.is_open()) {
        while (getline(input,line)) {
            uint64_t max_joltage = get_max_joltage(line);
            total_joltage += max_joltage;
        }
        cout << "Resultat :  " << total_joltage << endl;
        input.close();
    } else {
        cout << "Problem opening file" << endl;
    }
    return 0;
}