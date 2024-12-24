#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <set>


using namespace std;

struct Operator {
    string input1;
    string input2;
    string logic_operator;
    string output;
};

int main() {
    ifstream file("input.txt");
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

    while (getline(file,buffer) && buffer != "") {
        if (regex_search(buffer,match,init_wires)) {
            if (match.str(2) == "1") {
                wires[match.str(1)] = true;
            } else  {
                wires[match.str(1)] = false;
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

    cout << binary_output << endl;
    cout << stoull(binary_output,nullptr,2) << endl;
    
     



    
}