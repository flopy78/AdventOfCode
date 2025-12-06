#include <iostream>
#include<string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

uint64_t power_of_10(int n) {
    uint64_t p = 1;
    for (int i = 0 ; i < n ; i++) {
        p *= 10;
    }
    return p;
}

int main() {
    vector<string> lines;
    ifstream input ("input.txt");
    string buffer;

    while (getline(input,buffer)) {
        lines.push_back(buffer);
    }

    int operator_line_idx = lines.size() -1;
    uint64_t total = 0;
    uint64_t local_result = 0;

    char current_operator = ' ';
    for (int column = 0; column < lines[operator_line_idx].size() ; column++) {
        if (lines[operator_line_idx][column] != ' ') {
            cout << "local result : " << local_result << endl;
            current_operator = lines[operator_line_idx][column];
            total += local_result;

            if (current_operator == '+') {
                cout << "+" << endl;
                local_result = 0;
            } else if (current_operator == '*') {
                cout << "*" << endl;
                local_result = 1;
            }
        }
        uint64_t number = 0;
        int power = 0;
        for (int line = operator_line_idx -1 ; line >= 0  ; line--) {
            uint64_t digit = (lines[line][column] == ' ')? 0 : (lines[line][column]-'0');
            number += power_of_10(power) * digit;
            if (digit > 0) power ++;
        }
        cout << number << endl;
        if (current_operator == '+') {
            local_result += number;
        } else if (current_operator == '*' && number != 0) {
            local_result *= number;
        }
    }
    cout << "local result " << local_result << endl;
    total += local_result; //the last problem
    cout << "total : " << total << endl;



    
    return 0;
}