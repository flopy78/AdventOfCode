#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <set>
#include <bitset>


using namespace std;

struct Operator {
    string input1;
    string input2;
    string logic_operator;
    string output;
};

int main() {
    ifstream file("input_corrected.txt");
    if (!file.is_open()) {
        cerr << "error while opening file" << endl;
        return 1;
    }

    string buffer;

    regex init_wires("(.+): (.)");
    regex calc_wires("(.+) (.+) (.+) -> (.+)");
    smatch match;

    unordered_map<string,bool> wires;

    set<string> z_wires;

    string xstr;
    string ystr;


    while (getline(file,buffer) && buffer != "") {
        if (regex_search(buffer,match,init_wires)) {
            if (match.str(2) == "1") {
                wires[match.str(1)] = true;
            } else  {
                wires[match.str(1)] = false;
            }
            if (match.str(1)[0] == 'x') {
                xstr= match.str(2) + xstr;
            } else if (match.str(1)[0] == 'y') {
                ystr = match.str(2) +ystr;
            }

        }
    }
    vector<Operator> operations;
    while(getline(file,buffer)) {
        if (regex_search(buffer,match,calc_wires)) {
            operations.push_back({match.str(1),match.str(3),match.str(2),match.str(4)});
            if (match.str(1).starts_with("z")) {
                z_wires.insert(match.str(1));
            }
            if (match.str(3).starts_with("z")) {
                z_wires.insert(match.str(2));
            }
            if (match.str(4).starts_with("z")) {
                z_wires.insert(match.str(4));
            }

        }
     }

    int n_z_calculated = 0;

    int i = 0;

    while (n_z_calculated < z_wires.size()) {
        if (i >= operations.size()) i = 0;

        Operator operation = operations[i];

        if (wires.contains(operation.input1) && wires.contains(operation.input2) && !wires.contains(operation.output)) {
            if (operation.output.starts_with("z")) n_z_calculated ++;
            if (operation.logic_operator == "AND") {
                wires[operation.output] = wires[operation.input1] && wires[operation.input2];
            } else if (operation.logic_operator == "OR") {
                wires[operation.output] = wires[operation.input1] || wires[operation.input2];
            } else if (operation.logic_operator == "XOR") {
                wires[operation.output] = wires[operation.input1] ^ wires[operation.input2];
            }
        }

        i++;

    }

    string binary_output("");

    for (const string &wire : z_wires) {
        if (wires[wire]) {
            binary_output = "1" + binary_output;
        } else {
            binary_output = "0" + binary_output;
        }
    }

    bitset<46> binary_sum(stoull(xstr,nullptr,2)+stoull(ystr,nullptr,2));

    cout << stoull(xstr,nullptr,2) << endl;
    cout << stoull(ystr,nullptr,2) << endl;

    cout << binary_output.length() << endl;
    cout << "4444443333333333222222222211111111110000000000" << endl;
    cout << "5432109876543210987654321098765432109876543210" << endl;
    cout << binary_sum << endl;
    cout << binary_output << endl;
    cout << stoull(binary_output,nullptr,2) << endl;

    
}