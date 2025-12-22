#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>

using namespace std;

int main() {
    ifstream input ("input.txt");
    unordered_map<string,vector<string>> devices;
    string buffer;
    string trash;

    if (input.is_open()) {
        while (getline(input,buffer)) {
            stringstream buffer_stream (buffer);

            string device_name;
            getline(buffer_stream,device_name,':');

            getline(buffer_stream,trash,' ');

            vector<string> outputs = {};
            string output_buffer;
            while (getline(buffer_stream,output_buffer,' ')) {
                outputs.push_back(output_buffer);
            }
            devices.insert(make_pair(device_name,outputs));
        }

        uint64_t n_paths = 0;
        uint64_t opened_set_size = 1;
        unordered_map<string,bool> closed_set = {};
        for (auto it : devices) {
            closed_set.insert(make_pair(it.first,false));
        }
        string start = "you";
        string end = "out";
        deque<string> opened_set = {start};

        while (!opened_set.empty()) {
            string parent = opened_set.front();
            opened_set.pop_front();
            for (auto it = devices[parent].begin() ; it != devices[parent].end() ; it++) {
                string child = *it;
                if (child == end) {
                    n_paths ++;
                } else {
                    opened_set.push_back(child);
                }
            }
        }
        cout << n_paths << endl;



    } else {
        cerr << "problème ouverture fichier" << endl;
    }

    return 0;
}