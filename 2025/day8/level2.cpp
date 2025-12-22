#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<vector>
#include<tuple>
#include<chrono>

using namespace std;


class JunctionBox {
    public:
        uint64_t x;
        uint64_t y;
        uint64_t z;
        int idx;
        int circuit_idx;


        JunctionBox(int x, int y, int z, int idx, int circuit_idx) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->idx = idx;
            this->circuit_idx = circuit_idx;
        }

        void display() {
            cout << "circuit : " << this->circuit_idx << " idx : " << this->idx << " coords : " << this->x << "," << this->y << "," << this-> z << endl;
        }


};

class Circuit {
    public:
        vector<int> nodes;
        int size;
        bool activate;

        Circuit(vector<int> nodes) {
            this->nodes = nodes;
            this->size = nodes.size();
            this->activate = true;
        }

        void append_nodes(vector<int> nodes) {
            for (int i = 0 ; i < nodes.size() ; i++) {
                this->nodes.push_back(nodes[i]);
                this->size ++;
            }
        }

        void display() {
            cout << ((this->activate)? "actif /" : "inactif /"); 
            for (int i = 0 ; i < this->nodes.size() ; i++) {
                cout << this->nodes[i] << "->"; 
            }
            cout << endl;
        }
};

uint64_t get_distance(JunctionBox a,JunctionBox b) {
    uint64_t dx = a.x - b.x;
    uint64_t dy = a.y - b.y;
    uint64_t dz = a.z - b.z;
    return dx*dx + dy*dy +dz*dz;
}

bool contains(vector<tuple<int,int>> linked_pairs, int j, int k) {
    for (int i = 0 ; i < linked_pairs.size() ; i++) {
        if (get<0>(linked_pairs[i]) == j && get<1>(linked_pairs[i]) == k) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream input ("input.txt");

    clock_t start, end;

    start = clock();

    vector<JunctionBox> junction_boxes = {};
    vector<Circuit> circuits = {};
    int idx = 0;
    if (input.is_open()) {
        string buffer;
        while (getline(input,buffer)) {
            istringstream line_stream (buffer);
            string token;
            vector<uint64_t> coords;
            while (getline(line_stream,token,',')) {
                coords.push_back(stoll(token));
            }
            junction_boxes.push_back(JunctionBox(coords[0],coords[1],coords[2],idx,idx));
            circuits.push_back(Circuit({idx}));
            idx++;
        }
    }

    int best_first;
    int best_second;
    uint64_t min_distance;
    vector<tuple<int,int>> linked_pairs = {};
    uint64_t n_circuits = circuits.size();

    uint64_t n_tours = 0;
    while (n_circuits > 1) {
        
        //cout << n_circuits << endl;
        best_first = 0;
        best_second = 1;

        min_distance = INFINITY;

        for (int j = 0 ; j < junction_boxes.size() ; j++) {
            for (int k = j +1 ; k < junction_boxes.size() ; k++) {
                double distance =  get_distance(junction_boxes[j],junction_boxes[k]);
                if (min_distance > distance && !contains(linked_pairs,j,k)) {
                    best_first = j;
                    best_second = k;
                    min_distance = distance;
                }
            }
        }

        //junction_boxes[best_first].display();
        //junction_boxes[best_second].display();
        
        //cout << best_first << " " << best_second << " " << min_distance << endl;

        linked_pairs.push_back(make_tuple(best_first,best_second));


        if (junction_boxes[best_first].circuit_idx != junction_boxes[best_second].circuit_idx) {
            //cout << "something happened" << endl;
            JunctionBox best_first_box = junction_boxes[best_first];
            JunctionBox best_second_box = junction_boxes[best_second];
            vector<int> second_neighbours = circuits[best_second_box.circuit_idx].nodes;
            circuits[best_second_box.circuit_idx].activate = false;
            n_circuits --;
            for (int i = 0 ; i < second_neighbours.size() ; i++) {
                junction_boxes[second_neighbours[i]].circuit_idx = best_first_box.circuit_idx;
            }
            circuits[junction_boxes[best_first].circuit_idx].append_nodes(circuits[best_second_box.circuit_idx].nodes);
            circuits[best_second_box.circuit_idx].nodes = {};

        }
        //cout << endl;
        n_tours ++;
    }

    cout << "resultat : " << junction_boxes[get<0>(linked_pairs[n_tours-1])].x* junction_boxes[get<1>(linked_pairs[n_tours-1])].x << endl;
    end = clock();

    cout << ((float)end-start)/CLOCKS_PER_SEC << endl;

    
    return 0;
}