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


struct ReindeerStep {
    Position position;
    pair<int,int> direction;
    int score;
};

bool operator < (const ReindeerStep & A, const ReindeerStep & B) {
    if (A.score == B.score) {
        if (A.position.y == B.position.y) {
            if (A.direction.second == B.direction.second) {
                if (A.position.x == B.position.x) {
                    if (A.direction.first == B.direction.first) {
                        return false;
                    } else {
                        return A.direction.first < B.direction.first;
                    }
                } else {
                    return A.position.x < B.position.x;
                }
            } else {
                return A.direction.second < A.direction.first;
            }
        } else {
            return A.position.y < B.position.y;
        }
    } else {
        return A.score < B.score;
    }
}

pair<int,int> turn_clockwise(pair<int,int> direction) {
    return make_pair(-direction.second,direction.first);

} 

pair<int,int> turn_counterclockwise(pair<int,int> direction) {
    return make_pair(direction.second,-direction.first);
}

ReindeerStep get_best_step(set<ReindeerStep> opened_set) {
    int best_score = -1;
    ReindeerStep best_step;
    for (ReindeerStep step : opened_set) {
        if (best_score == -1 || step.score < best_score) {
            best_score = step.score;
            best_step = step;
        }
    }
    return best_step;
}

bool is_finished(set<ReindeerStep> opened_set,Position end) {
    for (ReindeerStep step : opened_set) {
        if (end.x == step.position.x && end.y == step.position.y) {
            return true;
        }
    }
    return false;
}

bool contains(set<ReindeerStep> closed_set, ReindeerStep step,bool rotate) {
    for (ReindeerStep closed_pos : closed_set) {
        int x = step.position.x;
        int y = step.position.y;
        if (rotate) {
            x += step.direction.first;
            y += step.direction.second;
        }
        if (x == closed_pos.position.x && y == closed_pos.position.y){ //&& step.direction == closed_pos.direction) {
            return true;
        }
    }
    return false;
}


int get_best_score(vector<string> maze, ReindeerStep start, Position end) {
    set<ReindeerStep> opened_set {start};
    set<ReindeerStep> new_set;
    set<ReindeerStep> closed_set {};

    int n_loops = 0;
    
    while (!is_finished(opened_set,end)) {
        ReindeerStep explored_step = *opened_set.begin();

        closed_set.insert(explored_step);
        opened_set.erase(opened_set.begin());
        //opened_set.erase(opened_set.find(explored_step));
        auto[dx,dy] = explored_step.direction;
        ReindeerStep new_step = {{explored_step.position.x+dx,explored_step.position.y+dy},explored_step.direction,explored_step.score + 1};
        if (new_step.position.x == end.x && new_step.position.y == end.y) {
            return new_step.score;
        }
        if (maze[new_step.position.y][new_step.position.x] != '#' && !contains(closed_set,new_step,false)) {
            opened_set.insert(new_step);
        }
        auto[dx_cw,dy_cw] = turn_clockwise(explored_step.direction);
        ReindeerStep new_step_cw = {{explored_step.position.x,explored_step.position.y},{dx_cw,dy_cw},explored_step.score + 1000};
        if (maze[explored_step.position.y+dy_cw][explored_step.position.x+dx_cw] != '#' && !contains(closed_set,new_step_cw,true)) {
            opened_set.insert(new_step_cw);
        }
        auto[dx_ccw,dy_ccw] = turn_counterclockwise(explored_step.direction);
        ReindeerStep new_step_ccw = {{explored_step.position.x,explored_step.position.y},{dx_ccw,dy_ccw},explored_step.score + 1000};
        if (maze[explored_step.position.y+dy_ccw][explored_step.position.x+dx_ccw] != '#' && !contains(closed_set,new_step_ccw,true)) {
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

     cout << get_best_score(maze,start,end) << endl;
}