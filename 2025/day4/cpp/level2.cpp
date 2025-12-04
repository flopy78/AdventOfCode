#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std; 

bool is_in_range(vector<string> paper_rolls, int x, int y) {
    int h = paper_rolls.size();
    int w = paper_rolls[0].size();
    return (x>=0 && x < w && y>=0 && y < h);
}

bool is_accessible(vector<string> paper_rolls, int x, int y) {
    int nb_neighbours = 0;
    for (int dx = -1 ; dx <= 1 ; dx ++) {
        for (int dy = -1 ; dy <= 1 ; dy++) {
            if (!(dx == 0 && dy == 0)) {
                if (is_in_range(paper_rolls,x+dx,y+dy) && paper_rolls[y+dy][x+dx] == '@') {
                    nb_neighbours ++;
                }
            }
        }
    }
    return (nb_neighbours < 4);

}

int main() {
    ifstream input ("input.txt");
    vector<string> paper_rolls;
    string buffer;

    if (input.is_open()) {
        while (getline(input,buffer)) {
            paper_rolls.push_back(buffer);
        }

        uint64_t accessible_rolls = 0;
        vector<vector<int>> rolls_to_remove;
        do {
            rolls_to_remove = {};
            for (int y = 0 ; y < paper_rolls.size() ; y++) {
                for (int x = 0 ; x < paper_rolls[y].size() ; x++) {
                    if (paper_rolls[y][x] == '@' && is_accessible(paper_rolls,x,y)) {
                        accessible_rolls ++;
                        rolls_to_remove.push_back({x,y});
                    }
                }
                for (int i = 0 ; i < rolls_to_remove.size() ; i++) {
                    paper_rolls[rolls_to_remove[i][1]][rolls_to_remove[i][0]] = ' ';
                }
            }
        } while (rolls_to_remove.size() > 0);
        cout << accessible_rolls << endl;
    } else {
        cout << "problème ouverture fichier\n" << endl;
    }




    return 0;

}


