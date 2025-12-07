#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

uint64_t get_duplicate_idx(vector<tuple<int,uint64_t>> beams, int beam_column) {
    for (int i = 0 ; i < beams.size() ; i++) {
        if (get<0>(beams[i]) == beam_column) {
            return i;
        }
    }
    return beams.size(); //no duplicate found
}


int main() {
    vector<tuple<int,uint64_t>> beams = {};
    ifstream input ("input.txt");
    string buffer;

    if (input.is_open()) {
        getline(input,buffer);
        int start_idx = 0;
        while (buffer[start_idx] != 'S') {
            start_idx++;
        }
        beams.push_back(make_tuple(start_idx,1));


        while (getline(input,buffer)) {
            vector<tuple<int,uint64_t>> new_beams = {};
            for (int i = 0 ; i < beams.size() ; i++) {
                int beam_column = get<0>(beams[i]);
                uint64_t beam_multiplicity = get<1>(beams[i]);
                if (buffer[beam_column] == '^') {
                    if (beam_column > 0) {
                        int duplicate_idx = get_duplicate_idx(new_beams,beam_column-1);
                        if (duplicate_idx < new_beams.size()) {
                            new_beams[duplicate_idx] = make_tuple(beam_column-1,get<1>(new_beams[duplicate_idx])+beam_multiplicity);
                        } else {
                            new_beams.push_back(make_tuple(beam_column-1,beam_multiplicity));
                        }
                    }
                    if (beam_column < buffer.size()-1) {
                        int duplicate_idx = get_duplicate_idx(new_beams,beam_column+1);
                        if (duplicate_idx < new_beams.size()) {
                            new_beams[duplicate_idx] = make_tuple(beam_column+1,get<1>(new_beams[duplicate_idx])+beam_multiplicity);
                        } else {
                            new_beams.push_back(make_tuple(beam_column+1,beam_multiplicity));
                        }
                    }

                } else {
                    int duplicate_idx = get_duplicate_idx(new_beams,beam_column);
                    if (duplicate_idx < new_beams.size()) {
                        new_beams[duplicate_idx] = make_tuple(beam_column,get<1>(new_beams[duplicate_idx])+beam_multiplicity);
                    } else {
                        new_beams.push_back(make_tuple(beam_column,beam_multiplicity));
                    }
                }
            }

            beams = new_beams;
        }

        uint64_t n_timelines = 0;

        for (int i = 0 ; i < beams.size() ; i++) {
            n_timelines += get<1>(beams[i]);
        }
        cout << "résultat : " << n_timelines << endl;

     } else {
        cout << "problème d'ouverture du fichier\n" << endl;
    }

    return 0;
}