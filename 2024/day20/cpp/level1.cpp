#include  <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

const vector<pair<int,int>> directions { 
    {1,0},
    {-1,0},   
    {0,1},
    {0,-1}
};


template<>
struct std::hash<pair<int,int>> {
    size_t operator()(const pair<int,int> &value) const {
        return value.first * 7 + value.second * 13;
    }
};


pair<int,int> find_pos(const vector<string> &maze, const char &symbol) {
    for (int y = 0 ; y < maze.size() ; y++) {
        for (int x = 0 ; x < maze[y].length() ; x++) {
            if (maze[y][x] == symbol) {
                return make_pair(x,y);
            }
        }
    }
    cerr << "find_pos : SYMBOL NOT FOUND" << endl;
    return make_pair(-1,-1);
}

bool is_in_range(const vector<string> &maze, const pair<int,int> &step) {
    return (step.first >=0 && step.first < maze[0].length()) && (step.second >= 0 && step.second < maze.size());
}

vector<pair<int,int>> get_path(const vector<string> &maze, const pair<int,int> &start, const pair<int,int> &end) {
    pair<int,int> current_step = start;

    vector<pair<int,int>> path;


    while (current_step != end) {
        for (auto[dx,dy] : directions) {
            pair<int,int> new_step = make_pair(current_step.first+dx,current_step.second+dy);
            if (is_in_range(maze,new_step) && maze[new_step.second][new_step.first] != '#') {
                if (path.size() == 0 || new_step != path.back()) {
                    path.push_back(current_step);
                    current_step = new_step;
                    break;
                }
            }
        }

    }
    path.push_back(end);
    return path;
}

int get_idx(const vector<pair<int,int>> path, const pair<int,int> &step) {
    return find(path.begin(),path.end(),step) - path.begin();

}

int get_efficient_cheats(const vector<string> &maze, const vector<pair<int,int>> &path,const pair<int,int> &start, int threshold) {
    unordered_set<pair<int,int>> closed_set {start};
    unordered_set<pair<int,int>> opened_set {start};
    unordered_set<pair<int,int>> new_set;
    int n_efficient_cheats = 0;

    int start_idx = get_idx(path,start);

    for (int i = 0 ; i < 20 ; i++) {
        int cheat_time = i+1;
        new_set = {};
        for (const pair<int,int> &step : opened_set) {
            for (auto[dx,dy] : directions) {
                pair<int,int> new_step = make_pair(step.first+dx,step.second+dy);
                if (is_in_range(maze,new_step) && !closed_set.contains(new_step)) {
                    closed_set.insert(new_step);
                    if (maze[new_step.second][new_step.first] != '#') {
                        int time_won = get_idx(path,new_step) - start_idx - cheat_time;
                        if (time_won >= threshold) {
                            n_efficient_cheats ++;
 
                        }
                    } 
                    new_set.insert(new_step);

                }
            }
        }
        opened_set = new_set;
    }



    return n_efficient_cheats;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "file opening error" << endl;
        return 1;
    }
    string buffer;
    vector<string> maze;

    while(getline(file,buffer)) {
        maze.push_back(buffer);
    }

    pair<int,int> start = find_pos(maze,'S');
    pair<int,int> end = find_pos(maze,'E');

    vector<pair<int,int>> path = get_path(maze,start,end);

    int total_efficient_cheats = 0;

    int i = 0;

    for (const pair<int,int> &step : path) {
        total_efficient_cheats += get_efficient_cheats(maze,path,step,100);
        i++;
        cout << i << "/" << path.size() << endl;
    }

    cout << total_efficient_cheats << endl;

    return 0;
}