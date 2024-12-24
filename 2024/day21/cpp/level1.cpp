#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdint>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <set>

using namespace std;

const unordered_map<char,pair<int,int>> directions {
    {'>',make_pair(1,0)},
    {'<',make_pair(-1,0)},
    {'^',make_pair(0,-1)},
    {'v',make_pair(0,1)}
};

struct Step {
    int x;
    int y;
    int64_t score;
    char last_move;
    string moves;
};

template<>
struct std::hash<Step> {
    size_t operator()(const Step &step) const {
        return step.x * 7 + step.y * 13;
    }
};

bool operator<(const Step &A, const Step &B) {
    if (A.score != B.score) return A.score < B.score;
    //else if (A.n_virages != B.n_virages) return A.n_virages < B.n_virages;
    else if (A.x != B.x) return A.x < B.x;
    else if (A.y != B.y) return A.y < B.y;
    return false;
}

template<>
struct std::hash<pair<int,int>> {
    size_t operator()(const pair<int,int> &paire) const {
        return paire.first * 7 + paire.second * 13;
    }
};

bool operator==(const Step &A, const Step &B) {
    return (A.x == B.x) && (A.y == B.y);// && (A.score == B.score);
}

pair<int,int> find_position(const vector<string> &pad, const char &symbol) {
    for (int y = 0 ; y < pad.size() ; y++) {
        for (int x = 0 ; x < pad[y].length() ; x++) {
            if (pad[y][x] == symbol) 
                return make_pair(x,y);
        }
    }
    cerr << "SYMBOL NOT FOUND" << endl;
    return make_pair(-1,-1);
}

bool is_in_range(const vector<string> &pad, const int &x, const int &y) {
    return (y >= 0 && y < pad.size()) && (x >= 0 && x < pad[y].length());
}




uint64_t get_n_instructions(const char &start, const char &end, const int &pad_id) {
    vector<string> pad;

    if (start == end) {
        return 1;
    }

    if (pad_id == 0) {
        pad = {
            "789",
            "456",
            "123",
            "#0A"
        };
    } else {
        pad = {
            "#^A",
            "<v>"
        };
    }  

    int64_t best_score = -1;
    char best_last_move = 'A';
    string best_moves = "";

    pair<int,int> start_pos = find_position(pad,start);
    pair<int,int> end_pos = find_position(pad,end);

    set<Step> opened_set {{start_pos.first,start_pos.second,0,'A',""}};
    unordered_set<pair<int,int>> closed_set {};
    set<Step> new_set;



    while (opened_set.size() > 0) {
        new_set = {};
        for (const Step &step : opened_set) {
            closed_set.insert(make_pair(step.x,step.y));
            for (const auto &direction  : directions) {
                auto[dx,dy] = direction.second;
                int nx = step.x + dx;
                int ny = step.y + dy;

                if (is_in_range(pad,nx,ny) && pad[ny][nx] != '#' && !closed_set.contains(make_pair(nx,ny))) { //(nx,ny) is in the grid
                    int new_score = step.score;
                    if (pad_id < 2)
                        new_score += get_n_instructions(step.last_move,direction.first,pad_id+1);
                    else
                        new_score ++;
                    Step new_step {nx,ny,new_score,direction.first,step.moves+direction.first};
                    if (nx == end_pos.first && ny == end_pos.second) {
                        if (pad_id == 2) new_step.score ++;
                        else new_step.score += get_n_instructions(new_step.last_move,'A',pad_id+1);
                        if (best_score == -1 || new_step.score < best_score) {
                            if(pad_id == 0) cout << "end " << new_step.x << " " << new_step.y << " " << new_step.score << endl;
                               best_score = new_step.score;
                            best_last_move = new_step.last_move;
                            best_moves = new_step.moves;
                        }
                    } else {
                        new_set.insert(new_step);
                        closed_set.insert(make_pair(nx,ny));
                    }
                }
            }
        }
        opened_set = new_set;

    }
    if (pad_id == 0) cout  << start << end << " " << best_moves << " " << best_score << endl;

    return best_score;
}


int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "file opening error" << endl;
        return 1;
    }
    string buffer;
    int solution = 0;
    while (getline(file,buffer)) {
        int numeric_part = stoi(buffer.substr(0,buffer.length()-1));
        cout << "numeric part :  " << numeric_part << endl;
        uint64_t n_instructions = get_n_instructions('A',buffer[0],0);

        for (int i = 0 ; i < buffer.length()-1 ; i++) {
            n_instructions += get_n_instructions(buffer[i],buffer[i+1],0);
        }
        cout << "instructions : " << n_instructions << endl;
        solution += numeric_part * n_instructions;
    }
    cout << solution << endl;
    return 0;
}