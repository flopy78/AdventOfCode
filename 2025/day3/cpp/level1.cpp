#include<iostream>
#include<fstream>
#include<string>
#include<cstdint>

using namespace std;

uint64_t char_to_uint64_t(char c) {
    if (c == '0') return 0;
    else if (c == '1') return 1;
    else if (c == '2') return 2;
    else if (c == '3') return 3;
    else if (c == '4') return 4;
    else if (c == '5') return 5;
    else if (c == '6' ) return 6;
    else if (c == '7') return 7;
    else if (c == '8') return 8;
    else if (c == '9') return 9;
    else fprintf(stderr,"not accepted input\n");exit(1);
}

int main() {
     uint64_t total_joltage = 0;
    ifstream input ("input.txt");
    string line;
    if (input.is_open()) {
        while (getline(input,line)) {
            uint64_t max_joltage = 0;
            for (int i = 0 ; i < line.size() ; i++) {
                for (int j = i + 1 ; j < line.size() ; j++) {
                    uint64_t joltage = char_to_uint64_t(line.at(i))*10+char_to_uint64_t(line.at(j));
                    
                    if (joltage > max_joltage) {
                        max_joltage = joltage;
                    }
                }
            }
            total_joltage += max_joltage;
        }
        cout << "Resultat :  " << total_joltage << endl;
        input.close();
    } else {
        cout << "Problem opening file" << endl;
    }
    

    return 0;
}