#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void display_beams_line(string buffer, vector<int> beams) {
     for (int i = 0 ;  i < buffer.size() ; i++) {
        if (count(beams.begin(), beams.end(), i) != 0) {
            cout << "|";
        } else {
            cout << buffer[i];
        }
     }
     cout << " " << beams.size() << endl;

     for (int i = 0 ; i < beams.size() ; i++) {
        cout << beams[i] << " ";
     }
     cout << endl;
}



int main() {
    int n_splits = 0;
    vector<int> beams = {};
    ifstream input ("test.txt");
    string buffer;

    if (input.is_open()) {
        getline(input,buffer);
        int start_idx = 0;
        while (buffer[start_idx] != 'S') {
            start_idx++;
        }
        beams.push_back(start_idx);
        while (getline(input,buffer)) {
            vector<int> new_beams = {};
            for (int i = 0 ; i < beams.size() ; i++) {
                if (buffer[beams[i]] == '^') {

                    if (beams[i] > 0 && count(new_beams.begin(), new_beams.end(), beams[i]-1) == 0) {
                        new_beams.push_back(beams[i]-1);
                    }
                    if (beams[i] < buffer.size()-1 && count(new_beams.begin(), new_beams.end(), beams[i]+1) == 0) {
                        new_beams.push_back(beams[i]+1);
                    }
                    n_splits ++;

                } else if (count(new_beams.begin(), new_beams.end(), beams[i]) == 0) {
                    new_beams.push_back(beams[i]);
                }
            }

            beams = new_beams;
        }
        cout << "résultat : " << n_splits << endl;
    } else {
        cout << "problème d'ouverture du fichier\n" << endl;
    }







    return 0;
}