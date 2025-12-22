#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<tuple>

using namespace std;

int main() {
    ifstream input ("input.txt");

    vector<tuple<uint64_t,uint64_t>> fresh_ranges;
    string buffer;
    while (getline(input,buffer) && buffer.size() > 0) {
        int sep_idx = 0;
        while (buffer[sep_idx] != '-') {
            sep_idx ++;
        }
        uint64_t lower = stoll(buffer.substr(0,sep_idx));
        uint64_t higher = stoll(buffer.substr(sep_idx+1,buffer.size()-1-sep_idx));
        fresh_ranges.push_back(make_tuple(lower,higher));
    }

    int nb_fresh = 0;

    while (getline(input,buffer)) {
        uint64_t id = stoll(buffer);
        bool is_fresh = false;
        cout << "--------" << endl;
        for (int i = 0 ; i < fresh_ranges.size() ; i++) {
            uint64_t lower = get<0>(fresh_ranges[i]);
            uint64_t higher = get<1>(fresh_ranges[i]);
            //cout << lower << " " << id << " " << higher << endl;

            if (lower <= id && higher >= id) {
                is_fresh = true;
                break;
            }

        }
        if (is_fresh) nb_fresh ++;
    }
    cout << "Résultat : " << nb_fresh << endl;
    
    return 0;
}