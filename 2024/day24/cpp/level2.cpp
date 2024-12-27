#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <set>
#include <cstdint>


using namespace std;

struct Operator {
    string input1;
    string input2;
    string logic_operator;
    string output;
};

uint64_t get_value(unordered_map<string,bool> wires, vector<Operator> operations, const set<string> &z_wires, const vector<pair<string,string>>  &swaps) {
    for (const pair<string,string> &swap : swaps) {
        string output1 = swap.first;
        string output2 = swap.second;
        auto operator1 = find_if(operations.begin(),operations.end(),[&output1](const Operator &op){return op.output == output1;});
        operator1->output = output2;
        auto operator2 = find_if(operations.begin(),operations.end(),[&output2](const Operator &op){return op.output == output2;});
        operator1->output = output1;      
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

    //cout << binary_output << endl;
    return stoull(binary_output,nullptr,2);

}

vector<pair<string,string>>  get_swaps(const vector<Operator> &operations) {
    vector<pair<string,string>> swaps {};
    for (int i = 0 ; i < operations.size() ; i++) {  
        for (int j = i+1 ; j < operations.size() ; j++) {
            swaps.push_back(make_pair(operations[i].output,operations[j].output));
        }
    }   
    return swaps;
}

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

    string x_binary("");
    string y_binary("");

    while (getline(file,buffer) && buffer != "") {
        if (regex_search(buffer,match,init_wires)) {
            if (match.str(2) == "1") {
                wires[match.str(1)] = true;
            } else  {
                wires[match.str(1)] = false;
            }
            if (match.str(1).starts_with("x")) {
                x_binary = match.str(2) + x_binary;
            } else {
                y_binary = match.str(2) + y_binary;
            }

        }
    }

    uint64_t target = stoull(x_binary,nullptr,2) + stoull(y_binary,nullptr,2);

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

    vector<pair<string,string>> swaps = get_swaps(operations);
    int count = 0;
    for (int i = 0 ; i < swaps.size() ; i++) {
        for (int j = i+1 ; j < swaps.size() ; j++) {
            for (int k = j + 1 ; k < swaps.size() ; k++) {
                for (int l = k + 1 ; l < swaps.size() ; l++) {
                    if (get_value(wires,operations,z_wires,{swaps[i],swaps[j],swaps[k],swaps[l]}) == target) {
                        cout << swaps[i].first << " " << swaps[i].second << endl;
                        cout << swaps[j].first << " " << swaps[j].second << endl;
                        cout << swaps[k].first << " " << swaps[k].second << endl;
                        cout << swaps[l].first << " " << swaps[l].second << endl;
                        return 0;
                    }
                    count ++;
                    if (count%10==0) cout << count << endl;
                }
            }
        }
     }

        
}