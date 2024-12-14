#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <unordered_set>

using namespace std;

vector<pair<int,int>> directions {make_pair(0,1),make_pair(0,-1),make_pair(1,0),make_pair(-1,0)};
vector<pair<int,int>> explored_tiles {};

template<>
struct std::hash<pair<int,int>> {
    size_t operator()(const pair<int,int> &value) const {
        return 7 * value.first + 13 * value.second;
    }
};

bool is_in_range(int x, int y, vector<string> field) {
    return (x >= 0 && x < field[0].length()) && (y >= 0 && y < field.size());
}

int get_extra_perimeter(int x, int y, vector<string> field) {
    int extra_perimeter = 0;
    for (auto[dx,dy] : directions) {
        if (!is_in_range(x+dx,y+dy,field)) extra_perimeter++;
        else if (field[y+dy][x+dx] != field[y][x]) extra_perimeter ++;
    }
    return extra_perimeter;
}


int get_section_price(int x, int y,vector<string> field) {
    int area = 1;
    char plant = field[y][x];
    int perimeter = get_extra_perimeter(x,y,field);
    int n = 0;
    unordered_set<pair<int,int>> opened_set {make_pair(x,y)};
    unordered_set<pair<int,int>> closed_set {make_pair(x,y)};
    unordered_set<pair<int,int>> new_set;

    while (opened_set.size() > 0) {
        new_set = {};
        for (auto[_x,_y] : opened_set) {

            for (auto[dx,dy] : directions) {
                int nx = _x + dx;
                int ny = _y + dy;
                if (is_in_range(nx,ny,field) && field[ny][nx] == plant) {
                    //Use at least c++20 to make this work
                    if (!closed_set.contains(make_pair(nx,ny))) {
                        area ++;
                        new_set.insert(make_pair(nx,ny));
                        closed_set.insert(make_pair(nx,ny));
                        perimeter += get_extra_perimeter(nx,ny,field);
                        explored_tiles.push_back(make_pair(nx,ny));
                    }
                }
            }
        }
        opened_set = new_set;
    }

    //cout << plant << " " << area << " * " << perimeter << endl;
    //cout << n << " " << closed_set.size() << endl;
    return area*perimeter;
    
 }

 bool contains(vector<pair<int,int>> tiles_list, pair<int,int> tile) {
    for (auto [x,y] : tiles_list) {
        if (x == tile.first && y == tile.second) return true;
    }
    return false;
 }

int main() {
    ifstream file("input.txt");
    vector<string> field;
    string buffer;

    while (getline(file,buffer)) {
        field.push_back(buffer);
    }

    int h = field.size();
    int w = field[0].length();

    unordered_map<char,int> section_areas;
    unordered_map<char,int> section_perimeters;
    vector<char> plants {};


    int price = 0;

    for (int y = 0 ; y < h ; y++) {
        for (int x = 0 ; x < w ; x++) {
            char plant = field[y][x];
            if (!contains(explored_tiles,make_pair(x,y))) {
                price += get_section_price(x,y,field);
            }


        }
    }

    cout << price << endl;


}