#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_set>

using namespace std;

template<>
struct std::hash<pair<int,int>> {
    size_t operator()(const pair<int,int> &value) const {
        return 7 * value.first + 13 * value.second;
    }
};

vector<string> split(string str,char delim) {
    string buffer = "";
    vector<string> split {};

    for (char c : str) {
        if (c == delim) {
            split.push_back(buffer);
            buffer = "";
        } else {
            buffer += c;
        }
    }
    if (buffer.size() > 0) {
        split.push_back(buffer);
    }
    return split;
}

vector<int> map_stoi(vector<string> input) {
    vector<int> output {};
    for (string number : input) {
        output.push_back(stoi(number));
    }
    return output;
}

bool is_in_range(vector<string> memory, int x, int y) {
    return (x >= 0  && x < memory[0].length()) && (y >= 0 && y < memory.size());
}

struct Step {
    int x;
    int y;
    int path_length;
    unordered_set<pair<int,int>> path;
};

unordered_set<pair<int,int>> find_best_path(vector<string> memory,pair<int,int> end) {
    vector<Step> opened_set {{0,0,0,{}}};
    vector<Step> new_set;
    unordered_set<pair<int,int>> closed_set;
    closed_set.insert(make_pair(0,0));
    bool is_finished = false;
    vector<pair<int,int>> directions {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1}
    };

    while (!is_finished) {
        new_set = {};
        for (Step step : opened_set) {
            for (auto[dx,dy] : directions) {
                int newx = step.x + dx;
                int newy = step.y + dy;
                if (is_in_range(memory,newx,newy)) {
                    if (memory[newy][newx] != '#' && !closed_set.contains(make_pair(newx,newy))) {
                        Step new_step = {newx,newy,step.path_length + 1,step.path};
                        new_step.path.insert(make_pair(step.x,step.y));

                        if (newx == end.first && newy == end.second) {
                            is_finished = true;
                            return new_step.path;
                        } else {
                            new_set.push_back(new_step);
                            closed_set.insert(make_pair(newx,newy));
                        }
                    }
                }
            }
        }
        opened_set = new_set;
        if (opened_set.size() == 0) {
            return {};
        }
    }
    return {};
}

int main() {
    int w = 7; //71 on input
    int h = 7; //71 on input
    int n_bytes_fallen = 12; //1024 on the input

    ifstream file("example.txt");
    string buffer;
    vector<string> memory {};

    for (int i = 0 ; i < h ; i++) {
        string line("");
        for (int j = 0 ; j < w ; j++) {
            line += '.';
        }
        memory.push_back(line);
    }
    
    //vector<pair<int,int>> bytes_locations;
    int bytes_idx = 0;

    while (getline(file,buffer) && bytes_idx < n_bytes_fallen) {
        vector<int> coords = map_stoi(split(buffer,','));
        memory[coords[1]][coords[0]] = '#';
        bytes_idx ++;
    
    }

    unordered_set<pair<int,int>> possible_break_places = find_best_path(memory,make_pair(w-1,h-1));

    bool is_blocked = false;
    while (!is_blocked) {
        vector<int> coords = map_stoi(split(buffer,','));
        memory[coords[1]][coords[0]] = '#';        
        if (possible_break_places.contains(make_pair(coords[0],coords[1]))) {
            if (find_best_path(memory,make_pair(w-1,h-1)).size() == 0) {
                is_blocked = true;
                cout << bytes_idx << endl;
                break;
            }
        }
        bytes_idx ++;
    }

    
    return 0;
}