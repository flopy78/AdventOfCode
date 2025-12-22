#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <cmath>

using namespace std;

tuple<uint64_t,uint64_t> get_coords(string buffer) {
    
    int i = 0; 

    while (buffer[i] != ',') {
          i ++;
    }
    return make_tuple(stoll(buffer.substr(0,i)),stoll(buffer.substr(i+1,buffer.size()-1)));
}

uint64_t get_distance(uint64_t x, uint64_t y) {
    if (x > y) {
        return x-y + 1;
    } else {
        return y-x + 1;
    }
}



int main() {
    ifstream input ("input.txt");

    vector<tuple<uint64_t,uint64_t>> red_tiles = {};
    string buffer;

    while (getline(input,buffer)) {
        string b1;
        string b2;
        red_tiles.push_back(get_coords(buffer));
    }

    uint64_t max_aire = 0;

    for (int i = 0 ; i < red_tiles.size() ; i++) {
        for (int j = i + 1 ; j < red_tiles.size() ; j++) {
            uint64_t aire = get_distance(get<0>(red_tiles[i]),get<0>(red_tiles[j])) * get_distance(get<1>(red_tiles[i]),get<1>(red_tiles[j]));
            if (max_aire < aire) {
                max_aire = aire;
            }
        }
    }

    cout << max_aire << endl;

}
