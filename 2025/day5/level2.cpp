#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<tuple>

using namespace std;

int size_without_overlap(vector<tuple<uint64_t,uint64_t>> fresh_ranges,int i) {
    uint64_t lower_ref = get<0>(fresh_ranges[i]);
    uint64_t higher_ref = get<1>(fresh_ranges[i]);
    uint64_t mini = lower_ref;
    uint64_t maxi = higher_ref;

    cout << "-----" << endl;

    cout << mini << " " << maxi << endl; 
    
    for (int j = 0 ; j < i ; j++) {
        uint64_t lower = get<0>(fresh_ranges[j]);
        uint64_t higher = get<1>(fresh_ranges[j]);
        if (lower <= mini && higher >= maxi) { //total inclusion : 0 new ids
            cout << "total inclusion dans " << lower << " " << higher <<  endl;
            return 0;
        }
        if (mini <= higher && mini >= lower) {
            mini = higher + 1;
        }
        if (maxi >= lower && maxi <= higher) {
            maxi = lower -1;
        }
    }
    cout << mini << " " << maxi << endl; 

    if (maxi-mini >= 0) {
        return maxi-mini +1;
    } else {
        return 0;
    }




}

int main() {
    ifstream input ("tets.txt");

    uint64_t nb_fresh;

    string buffer;
    vector<tuple<uint64_t,uint64_t>> fresh_ranges;

    while (getline(input,buffer) && buffer.size() > 0) {
        int sep_idx = 0;
        while (buffer[sep_idx] != '-') {
            sep_idx ++;
        }
        uint64_t lower = stoll(buffer.substr(0,sep_idx));
        uint64_t higher = stoll(buffer.substr(sep_idx+1,buffer.size()-1-sep_idx));
        fresh_ranges.push_back(make_tuple(lower,higher));
    }

    for (int i = 0 ; i < fresh_ranges.size() ; i++) {
        nb_fresh += size_without_overlap(fresh_ranges,i);
    }



    cout << "Résultat : " << nb_fresh << endl;
    
    return 0;
}