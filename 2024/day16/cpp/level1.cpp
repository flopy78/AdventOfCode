#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <set>
#include <unordered_set>

using namespace std;




struct Position {
    int x;
    int y;
};

template<>
struct std::hash<Position> {
    size_t operator()(const Position &value) const {
        return 7 * value.x + 13 * value.y;
    }
};

bool operator==(const Position & A, const Position & B) {
    return (A.x == B.x) && (A.y == B.y);
}

struct ReindeerStep {
    Position position;
    pair<int,int> direction;
    int score;
};


bool operator < (const ReindeerStep & A, const ReindeerStep & B) {
    if (A.score != B.score) 
        return A.score < B.score;
    if (A.position.y != B.position.y) 
        return A.position.y < B.position.y;
    if (A.direction.second != B.direction.second)
        return A.direction.second < B.direction.second;
    if (A.position.x != B.position.x)
        return A.position.x < B.position.x; 
    if (A.direction.first != B.direction.first) 
        return A.direction.first < B.direction.first;
    return false;
}                    


pair<int,int> turn_clockwise(pair<int,int> direction) {
    return make_pair(-direction.second,direction.first);

} 

pair<int,int> turn_counterclockwise(pair<int,int> direction) {
    return make_pair(direction.second,-direction.first);
}


bool is_finished(set<ReindeerStep> opened_set,Position end) {
    for (ReindeerStep step : opened_set) {
        if (end.x == step.position.x && end.y == step.position.y) {
            return true;
        }
    }
    return false;
}

int get_best_score(vector<string> maze, ReindeerStep start, Position end) {
    set<ReindeerStep> opened_set {start};
    set<ReindeerStep> new_set;
    unordered_set<Position> closed_set {};

    int n_loops = 0;
    
    while (!is_finished(opened_set,end)) {
        ReindeerStep explored_step = *opened_set.begin();

        closed_set.insert(explored_step.position);
        opened_set.erase(opened_set.begin());
        auto[dx,dy] = explored_step.direction;
        ReindeerStep new_step = {{explored_step.position.x+dx,explored_step.position.y+dy},explored_step.direction,explored_step.score + 1};
        if (new_step.position.x == end.x && new_step.position.y == end.y) {
            return new_step.score;
        }
        if (maze[new_step.position.y][new_step.position.x] != '#' && !closed_set.contains(new_step.position)) {
            opened_set.insert(new_step);
        }
        auto[dx_cw,dy_cw] = turn_clockwise(explored_step.direction);
        ReindeerStep new_step_cw = {{explored_step.position.x,explored_step.position.y},{dx_cw,dy_cw},explored_step.score + 1000};
        if (maze[explored_step.position.y+dy_cw][explored_step.position.x+dx_cw] != '#' && !closed_set.contains({new_step_cw.position.x+dx_cw,new_step_cw.position.y+dy_cw})) {
            opened_set.insert(new_step_cw);
        }
        auto[dx_ccw,dy_ccw] = turn_counterclockwise(explored_step.direction);
        ReindeerStep new_step_ccw = {{explored_step.position.x,explored_step.position.y},{dx_ccw,dy_ccw},explored_step.score + 1000};
        if (maze[explored_step.position.y+dy_ccw][explored_step.position.x+dx_ccw] != '#' && !closed_set.contains({new_step_ccw.position.x+dx_ccw,new_step_ccw.position.y+dy_ccw})) {
            opened_set.insert(new_step_ccw);
        }

        n_loops ++;

    }


    return (*opened_set.begin()).score;

}

int main() {
    vector<string> maze {};
    string buffer;
    ifstream file("input.txt");

    ReindeerStep start;
    Position end;

    int y = 0;
    while (getline(file,buffer)) {
        maze.push_back(buffer);
        for (int x = 0 ; x < buffer.length() ; x++) {
            if (buffer[x] == 'S') {
                start = {{x,y},make_pair(1,0),0};
            } else if (buffer[x] == 'E') {
                end = {x,y};
            }
        }
        y++;
    }
    cout << maze.size() << " " << maze[0].length() << endl;
    cout << get_best_score(maze,start,end) << endl;
}
