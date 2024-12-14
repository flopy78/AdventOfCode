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
    for (int time = 0 ; time < 100 ; time++) {
        for (Robot &robot : robots) {
            robot.move();
        }

    }



    int count_left_up = 0;
    int count_right_up = 0;
    int count_left_down = 0;
    int count_right_down = 0;

    int half_w = w/2;
    int half_h = h/2;


    for (Robot &robot : robots) {
        //cout << robots[i].x << " " << robots[i].y << endl;
        if (robot.x < half_w) {
            if (robot.y < half_h) {
                count_left_up ++;
            } else if (robot.y > half_h) {

                count_left_down ++;
            }
        } else if (robot.x > half_w) {
            if (robot.y < half_h) {
                count_right_up ++;
            } else if (robot.y > half_h) {

                count_right_down ++;
            }
        }
    }
    cout << count_left_up * count_left_down * count_right_up * count_right_down << endl;
    return 0;
}