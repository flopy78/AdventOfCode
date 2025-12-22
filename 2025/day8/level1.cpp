#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<vector>
#include<tuple>

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

    int N = 1000; //number of pairs to match
    int best_first;
    int best_second;
    uint64_t min_distance;
    vector<tuple<int,int>> linked_pairs = {};
    for (int _ = 0 ; _ < N ; _++) {
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
        
        cout << best_first << " " << best_second << " " << min_distance << endl;

        linked_pairs.push_back(make_tuple(best_first,best_second));


        if (junction_boxes[best_first].circuit_idx != junction_boxes[best_second].circuit_idx) {
            //cout << "something happened" << endl;
            JunctionBox best_first_box = junction_boxes[best_first];
            JunctionBox best_second_box = junction_boxes[best_second];
            vector<int> second_neighbours = circuits[best_second_box.circuit_idx].nodes;
            circuits[best_second_box.circuit_idx].activate = false;
            for (int i = 0 ; i < second_neighbours.size() ; i++) {
                junction_boxes[second_neighbours[i]].circuit_idx = best_first_box.circuit_idx;
            }
            circuits[junction_boxes[best_first].circuit_idx].append_nodes(circuits[best_second_box.circuit_idx].nodes);
            circuits[best_second_box.circuit_idx].nodes = {};

        }
        //cout << endl;
    }
    int n_circuits = 0;
    for (int i = 0 ; i < circuits.size() ; i++) {
        circuits[i].display();
        if (circuits[i].activate) {
            n_circuits ++;
        }
    }
    //
    
    cout << "circuits actifs : " << n_circuits << endl;
    vector<int> biggest_circuits = {};
    uint64_t prod = 1;
    for (int i = 0 ; i < 3 ; i++) {
        int biggest_size = 0;
        int biggest_circuit_idx;
        for (int j = 0 ; j < circuits.size() ; j++) {
            if (circuits[j].activate && count(biggest_circuits.begin(),biggest_circuits.end(),j) == 0) {
                if (circuits[j].size > biggest_size) {
                    biggest_circuit_idx = j;
                    biggest_size = circuits[j].size;
                }
            }
        }
        biggest_circuits.push_back(biggest_circuit_idx);
        for (int i = 0 ; i < circuits[biggest_circuit_idx].nodes.size() ; i++) {
            //cout << circuits[biggest_circuit_idx].nodes[i] << ";";
        }
        //cout << endl;
        //cout << biggest_size << endl;
        prod *= biggest_size;
    }
    cout << "resultat : " << prod << endl;
    junction_boxes[0].display();
    junction_boxes[1].display();
    cout << get_distance(junction_boxes[0],junction_boxes[1]) << endl;
    return 0;
}