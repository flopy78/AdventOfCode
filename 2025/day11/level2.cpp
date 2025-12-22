#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <tuple>

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

        string start = "svr";
        string end = "out";
        deque<tuple<string,bool,bool>> opened_set = {make_tuple(start,false,false)};
        string fft_s = "fft";
        string dac_s = "dac";

        unordered_map<tuple<string,bool,bool>,bool> closed_set = {};

        while (!opened_set.empty()) {
            tuple<string,bool,bool> parent = opened_set.front();
            string parent_name = get<0>(parent);
            opened_set.pop_front();

            closed_set.insert(make_pair(parent,unit));
            for (auto it = devices[parent_name].begin() ; it != devices[parent_name].end() ; it++) {
                string child = *it;
                if (child == end && get<1>(parent) && get<2>(parent)) {
                    n_paths ++;
                } else if (child != end) {
                    bool dac = get<1>(parent);
                    bool fft = get<2>(parent);
                    if (child == fft_s) {
                        fft = true;
                    } else if (child == dac_s) {
                        dac = true;
                    }
                    tuple<string,bool,bool> packed_child = make_tuple(child,dac,fft);
                    if (!contains(closed_set,packed_child)) {
                        opened_set.push_back(packed_child);
                        closed_set.push_back(packed_child);
                    }
                }
                cout << "os size " << opened_set.size() << << endl;
            }
        }
        cout << n_paths << endl;



    } else {
        cerr << "problème ouverture fichier" << endl;
    }

    return 0;
}