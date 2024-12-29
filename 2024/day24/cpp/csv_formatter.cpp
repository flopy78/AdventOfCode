#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

struct Node {
    int id;
    string input1;
    string label;
    string input2;
    string output;
};


int main() {
    regex init_wires("(.+): (.)");
    regex calc_wires("(.+) (.+) (.+) -> (.+)");
    smatch match;

    ifstream source("input.txt");
    ofstream dest_nodes("network_nodes.csv");
    ofstream dest_links("network_links.csv");
    string buffer;

    vector<Node> nodes {};

    int id = 0;


    while (getline(source,buffer) && buffer != "") {
        if (regex_search(buffer,match,init_wires)) {
            nodes.push_back({id=id,.input1="",.input2="",.label="INPUT",.output=match.str(1)});
            id++;
        }
    }

    while (getline(source,buffer)) {
        if (regex_search(buffer,match,calc_wires)) {
            nodes.push_back({id,match.str(1),match.str(2),match.str(3),match.str(4)});
            id++;
            if (match.str(4)[0] == 'z') {
                nodes.push_back({.id=id,.input1=match.str(4),.input2="",.label="OUTPUT",.output=""});
                id++;
            }

        }
    }

    dest_nodes << "id;label" << endl;
    for (const Node &node : nodes) {
        dest_nodes << node.id << ";" << node.label << endl;
    }

    dest_links << "source;target;label" << endl;
    for (const Node &node1 : nodes) {
        for (const Node &node2 : nodes) {
            if ((node1.output == node2.input1 || node1.output == node2.input2) && node1.output != "") {
                dest_links << node1.id << ";" << node2.id << ";" << node1.output << endl;
            }
        }
    }

    
    source.close();
    dest_nodes.close();
    dest_links.close();
    return 0;
}