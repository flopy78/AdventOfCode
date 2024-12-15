#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>

using namespace std;

class WareHouseObject;
class Box;
class Robot;

bool move_box_from_coords(vector<Box>&,int,int,pair<int,int>,bool);

bool is_in_range(vector<string>,int,int);

vector<string> warehouse {};
bool box_not_found = false;

class WarehouseObject {
    public :
        int x;
        int y;
        char symbol;

        WarehouseObject(int x, int y,char symbol) {
            this -> x = x;
            this -> y = y;
            this -> symbol = symbol;
        }


        bool move(pair<int,int> direction,vector<Box> &boxes,bool activate = true) {
            auto[dx,dy] = direction;
            if (symbol == '@') {
                int nx = x+dx;
                int ny = y+dy;
                if (is_in_range(warehouse,nx,ny) && warehouse[ny][nx] != '#') {
                    bool can_move = true;
                    if (warehouse[ny][nx] != '.') {
                        can_move = move_box_from_coords(boxes,nx,ny,direction,false);
                    }
                    if (can_move) {
                        move_box_from_coords(boxes,nx,ny,direction,true);
                        warehouse[this->y][this->x] = '.';
                        warehouse[ny][nx] = symbol;
                        this->x = nx;
                        this->y = ny;
                    } 
                    return can_move;
                } else {
                    return false;
                } 
            } else if (symbol == 'O') {
                int nx1 = x + dx;
                int nx2 = x+1 + dx;
                int ny = y + dy;

                //cout << symbol << " " << x << " " << y<< " " << nx1 << " " << nx2 << " " << ny << endl;

                if (is_in_range(warehouse,nx1,ny) && is_in_range(warehouse,nx2,ny) && warehouse[ny][nx1] != '#' && warehouse[ny][nx2] != '#') {
                    bool first_move = true;
                    bool second_move = true;
                    if (warehouse[ny][nx1] != '.' && dx != 1) {
                        first_move = move_box_from_coords(boxes,nx1,ny,direction,activate);
                    }
                    if (warehouse[ny][nx2] != '.' && dx != -1) {
                        second_move = move_box_from_coords(boxes,nx2,ny,direction,activate);
                    }

                    bool can_move = first_move && second_move;                    

                    if (can_move && activate) {
                        warehouse[this->y][this->x] = '.';
                        warehouse[this->y][this->x+1] = '.';
                        warehouse[ny][nx1] = '[';
                        warehouse[ny][nx2] = ']'; 
                        this->x = nx1;
                        this->y = ny;
                    } 
                    return can_move;
                    
                } else {
                    return false;
                }

            } else {
                cerr << "WARNING" << endl;
                return false;
            }

        }

        int get_gps() {
            return x + 100*y;
        }
};

class Box : public WarehouseObject{
    public:
        Box(int x, int y) : WarehouseObject(x,y,'O') {

        }
    
};

class Robot : public WarehouseObject{
    public:
        string instructions;
        unordered_map<char,pair<int,int>> directions_map;
        Robot(int x, int y, string instructions) : WarehouseObject(x,y,'@') {
            this -> instructions = instructions;
            this -> directions_map = {{'>',make_pair(1,0)},{'<',make_pair(-1,0)},{'^', make_pair(0,-1)}, {'v',make_pair(0,1)}};
        }

        void execute(vector<Box> &boxes) {
            for (char instruction : this->instructions) {
                this->move(this->directions_map[instruction],boxes);
                /*cout << instruction<< endl;
                for (string line : warehouse) {
                    cout << line << endl;
                }*/
                
            }
        }
    
};


bool move_box_from_coords(vector<Box> &boxes, int x, int y,pair<int,int> direction,bool activate_leaves) {
    for (Box &box : boxes) {
        if ((box.x == x || box.x+1 == x) && box.y == y) {
           return box.move(direction,boxes,activate_leaves);
        }
    } 
    //cout << "BOX NOT FOUND" << endl;
    return false;
}



bool is_in_range(vector<string> warehouse, int x, int y) {
    return (x >= 0  && x < warehouse[0].length()) && (y >= 0 && y < warehouse.size());
}


int main() {
    ifstream file("input.txt");
    string buffer;
    string instructions("");
    vector<Box> boxes;

    while (getline(file,buffer) && buffer.length() > 0) {
        
        if (buffer.length() > 0) {
            string line;
            for (char c : buffer) {
                if (c == '.') line += "..";
                else if (c == '@') line += "@.";
                else if (c == '#') line += "##";
                else if (c == 'O') line += "[]";
            }
            warehouse.push_back(line);
            //cout << line << endl;
        }
    }

    int robot_x = 0;
    int robot_y = 0;

    for (int y = 0 ; y < warehouse.size() ; y++) {
        for (int x = 0 ; x < warehouse[y].length() ; x++) {
            if (warehouse[y][x] == '[') {
                boxes.push_back(Box(x,y));
            } else if (warehouse[y][x] == '@') {
                robot_x = x;
                robot_y = y;
            }
        } 
    }


    while (getline(file,buffer)) {
        instructions += buffer;
    }


    Robot robot(robot_x, robot_y,instructions);

    robot.execute(boxes);

    int gps_sum = 0;

    for (Box box : boxes) {
        gps_sum += box.get_gps();
    }
    
    cout << gps_sum << endl;
 




    return 0;
}