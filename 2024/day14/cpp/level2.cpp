#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class Robot {
    public :
        int x;
        int y;
        int vx;
        int vy;
        int space_w;
        int space_h;


        Robot(int x, int y, int vx, int vy, int space_w, int space_h) {
            this-> x = x;
            this-> y = y;
            this-> vx = vx;
            this-> vy = vy;
            this-> space_w = space_w;
            this-> space_h = space_h;
        }



        void move() {
            x = (x + vx) % space_w;
            y = (y + vy) % space_h;
            if (x < 0) x = space_w + x;
            if (y < 0) y = space_h + y;
            /*if ((y + vy) % space_h != y) {
                cerr << "MAJOR ERROR" << endl;

            }*/
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

bool find_tree(vector<vector<char>> space, int w,int h) {
    bool tree_found = false;
    for (int y = 0 ; y < h - 4 ; y++) {
        for (int x = 0 ; x < w - 2 ; x++) {
            if (space[y][x] == '#') {
                tree_found = true;
                for (int dy = 0 ; dy < 4 ; dy++) {
                    for (int dx = 0 ; dx < 2 ; dx++) {
                        if (space[y+dy][x+dx] == '.') {
                            tree_found = false;
                        }
                    }
                }
                if (tree_found) {
                    return true;
                }
            }
        }
    }
    return tree_found;
}

int main() {
    vector<Robot> robots = {};
    ifstream file("input.txt");
    string buffer;
    getline(file,buffer);
    vector<string> dimensions = split(buffer,' ');
    int w = stoi(dimensions[0]);
    int h = stoi(dimensions[1]);

    while (getline(file,buffer)) {
        vector<string> robot_data = split(buffer,' ');

        vector<string> robot_position = split(split(robot_data[0],'=')[1],',');
        int robot_x = stoi(robot_position[0]);
        int robot_y = stoi(robot_position[1]);

        vector<string> robot_speed = split(split(robot_data[1],'=')[1],',');
        int robot_vx = stoi(robot_speed[0]);
        int robot_vy = stoi(robot_speed[1]);
        robots.push_back(Robot(robot_x,robot_y,robot_vx,robot_vy,w,h));
    }
    vector<vector<char>> space;

    int time = 1;
    bool tree_detected = false;
    while (!tree_detected) {
        space = {};
        for (int i = 0 ; i < h ; i++) {
            vector<char> line = {};
            for (int j = 0 ; j < w ; j++) {
                line.push_back('.');
            }
            space.push_back(line);
        }


        for (Robot &robot : robots) {
            robot.move();
            space[robot.y][robot.x] = '#';
        }
        if (find_tree(space,w,h)) {
            /*for (vector<char> line : space) {
                for (char tile : line) {
                    cout << tile;
                }
                cout << endl;
            }*/
            cout << time << endl;
            tree_detected = true;
        }
        time ++;
    }


    return 0;
}