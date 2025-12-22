#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<deque>
#include<assert.h>

using namespace std;


class Machine {
    public:
        vector<vector<uint64_t>> buttons;
        vector<bool> lights_requirement;

        Machine(vector<bool> lights_requirement,vector<vector<uint64_t>> buttons) {
            this->buttons = buttons;
            this->lights_requirement = lights_requirement;
        }
};


class Node {
    public:
        vector<bool> lights_config;
        vector<int> buttons_idx_used;

        Node(vector<bool> lights_config,vector<int> buttons_idx) {
            this->lights_config = lights_config;

            this->buttons_idx_used = buttons_idx;
        }

        vector<Node> get_children(vector<vector<uint64_t>> buttons) {
            vector<Node> children = {};

            for (int i = 0; i < buttons.size() ; i++) {
                vector<bool> new_light_config = this->lights_config;
                for (int j = 0 ; j < buttons[i].size() ; j++) {
                    new_light_config[buttons[i][j]] = !new_light_config[buttons[i][j]];
                }
                vector<int> new_button_idx_used = this->buttons_idx_used;
                new_button_idx_used.push_back(i);
                children.push_back(Node(new_light_config,new_button_idx_used));
            }
            return children;
        }
        
        void display() {
            string repr = "";

            for (int i = 0 ; i < lights_config.size() ; i++) {
                repr += (lights_config[i])?'#':'.';
            }
            
            cout << repr << endl;
        }
};

uint64_t is_goal_achieved(vector<Node> closed_set, Machine machine) {
    //return -1 if goal is not achieved and the number of steps needed otherwise
    for (int i = 0 ; i < closed_set.size() ; i++) {

        if (closed_set[i].lights_config == machine.lights_requirement) {
            return closed_set[i].buttons_idx_used.size();
        }
    }
    return -1;
}

int main() {

    /*
    ********************INPUT PARSING******************
    */
    ifstream input ("input.txt");
    string buffer;
    vector<Machine> machines;
    if (input.is_open()) {
        while (getline(input,buffer)) {
            stringstream buffer_stream = stringstream (buffer);
            string lights_requirements;
            getline(buffer_stream,lights_requirements,' ');
            lights_requirements = lights_requirements.substr(1,lights_requirements.size()-2);
            vector<bool> bool_light_requirements;
            for (int i = 0 ; i < lights_requirements.size() ; i++) {
                if (lights_requirements[i] == '#') {
                    bool_light_requirements.push_back(true);
                } else {
                    bool_light_requirements.push_back(false);
                }
            }
            string button_buffer;
            vector<vector<uint64_t>> buttons = {};
            while (getline(buffer_stream,button_buffer,' ') && button_buffer[0] == '(') {
                stringstream button_stream (button_buffer.substr(1,button_buffer.size()-2));
                string number_buffer;
                vector<uint64_t> numbers = {};
                while (getline(button_stream,number_buffer,',')) {
                    numbers.push_back(stoll(number_buffer));
                }
                buttons.push_back(numbers);
            }
            machines.push_back(Machine(bool_light_requirements,buttons));
        }

        /*
        PROBLEM RESOLUTION
         */

         uint64_t result = 0;

         for (int i = 19 ; i < machines.size() ; i++) {
            cout << i << endl;
            Machine machine = machines[i];
            vector<Node> closed_set = {};
            deque<Node> opened_set;
            vector<bool> start_config = {};
            for (int i = 0 ; i < machine.lights_requirement.size() ; i++) {
                start_config.push_back(false);
            }
            opened_set.push_back(Node(start_config,{}));

            int opened_set_size = 1;

            int tour_counter = 0;
            int is_finished = false;
            while (!is_finished) {
                int new_set_size = 0;
                for (int i = 0 ; i < opened_set_size ; i++) {
                    Node parent = opened_set.front();
                    opened_set.pop_front();
                    closed_set.push_back(parent);
                    vector<Node> children = parent.get_children(machine.buttons);
                    for (int j = 0 ; j < children.size() ; j++) {
                        if (children[j].lights_config == machine.lights_requirement && !is_finished) {
                            //children[j].display();
                            //cout << children[j].buttons_idx_used.size() << endl;
                            result += children[j].buttons_idx_used.size();
                            is_finished = true;
                            break;
                        }
                        bool is_double = false;

                        for (int k = 0 ; k < closed_set.size() ; k++) {
                            if (closed_set[k].lights_config == children[j].lights_config)  {
                                is_double = true;
                                cout << "double" << endl;
                                if (closed_set[k].buttons_idx_used.size() > children[j].buttons_idx_used.size()) {
                                    closed_set[k].buttons_idx_used = children[j].buttons_idx_used;
                                }
                            }
                        }
                        if (!is_double) {
                            opened_set.push_back(children[j]);
                            new_set_size ++;
                            //children[j].display();
                        }
                    }
                }
                opened_set_size = new_set_size;
                cout << opened_set_size << " " << closed_set.size() << endl;
                tour_counter ++;
                cout << "-----" << endl;
                for (int m = 0 ; m < closed_set.size() ; m++) {
                    closed_set[m].display();
                }
                if (tour_counter>=4) break;
                
            }
            break;
         }

         cout << "résultat : " << result << endl;


    } else {
        cerr << "erreur fichier" << endl;
    }

}   
