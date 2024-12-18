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
};

int find_best_path(vector<string> memory,pair<int,int> end) {
    vector<Step> opened_set {{0,0,0}};
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
                        new_set.push_back({newx,newy,step.path_length + 1});
                        closed_set.insert(make_pair(newx,newy));
                        if (newx == end.first && newy == end.second) {
                            is_finished = true;
                            return step.path_length + 1;
                        }
                    }
                }
            }
        }
        opened_set = new_set;
        /*cout << "====" << endl;
        for (Step step : opened_set) {
            cout << step.x << " " << step.y << endl;
        }
        cout << "====" << endl;

        cout << opened_set.size() << endl;*/
    }
    return 0;



}

int main() {
    int w = 71; //71 on input
    int h = 71; //71 on input
    int n_bytes_fallen = 1024; //1024 on the input

    ifstream file("input.txt");
    string buffer;
    vector<string> memory {};

    for (int i = 0 ; i < h ; i++) {
        string line("");
        for (int j = 0 ; j < w ; j++) {
            line += '.';
        }
        memory.push_back(line);
    }
    
    vector<pair<int,int>> bytes_locations;

    while (getline(file,buffer)) {
        vector<int> coords = map_stoi(split(buffer,','));
        int x = coords[0];
        int y = coords[1];
        bytes_locations.push_back(make_pair(x,y));
        
        if (bytes_locations.size() <= n_bytes_fallen) {
            memory[y][x] = '#';
        }
    }



    cout << find_best_path(memory,make_pair(w-1,h-1)) <<endl;



    



    return 0;
}