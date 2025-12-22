#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<deque>
#include<assert.h>

using namespace std;

class List {
    public:
        vector<uint64_t> head;
        List* tail;

        List(vector<uint64_t> head, List* tail) {
            this->head = head;
            this->tail = tail;
        }
};


class Machine {
    public:
        List* buttons;
        vector<uint64_t> lights_requirement;

        Machine(vector<uint64_t> lights_requirement,List* buttons) {
            this->buttons = buttons;
            this->lights_requirement = lights_requirement;
        }
};




uint64_t find_min_path(List* buttons,vector<uint64_t> target, vector<uint64_t> start, uint64_t depth) {

    if (buttons == NULL) {
        return target.size()+1;
    } else if (start == target) {
        return depth;
    }
    vector<uint64_t> first_button = buttons->head;
    vector<bool> new_start = start;


    for (int i = 0 ; i < first_button.size() ; i++) {
        //cout << new_start.size() << " " << first_button[i] << endl; 
         new_start[first_button[i]] = ! new_start[first_button[i]];
    }
    
    uint64_t path_without_button = find_min_path(buttons->tail,target,start,depth);

    uint64_t path_with_button = find_min_path(buttons->tail,target,new_start,depth+1);
    return (path_with_button<=path_without_button)?path_with_button:path_without_button;

}



int main() {

    /*
    ********************INPUT PARSING******************
    */
    ifstream input ("input.txt");
    string buffer;
    vector<Machine*> machines;
    vector<List*> buttons = {};
    if (input.is_open()) {
        while (getline(input,buffer)) {
            stringstream buffer_stream = stringstream (buffer);
            string lights_requirements;
            getline(buffer_stream,lights_requirements,' ');

            string button_buffer;
            buttons.push_back(new List({},NULL));
            while (getline(buffer_stream,button_buffer,' ') && button_buffer[0] == '(') {
                stringstream button_stream (button_buffer.substr(1,button_buffer.size()-2));
                string number_buffer;
                vector<uint64_t> numbers = {};
                while (getline(button_stream,number_buffer,',')) {
                    numbers.push_back(stoll(number_buffer));
                }
                buttons[buttons.size()-1] = new List(numbers,buttons[buttons.size()-1]);
            }
            
            getline(buffer_stream,lights_requirements,' ');
            lights_requirements = lights_requirements.substr(1,lights_requirements.size()-2);
            vector<uint64_t> bool_light_requirements;
            

            for (int i = 0 ; i < lights_requirements.size() ; i++) {
                if (lights_requirements[i] == '#') {
                    bool_light_requirements.push_back(true);
                } else {
                    bool_light_requirements.push_back(false);
                }
            }
            machines.push_back(new Machine(bool_light_requirements,buttons[buttons.size()-1]));
            //cout << machines.back().buttons->head.size() << endl;
        }

        /*
        PROBLEM RESOLUTION
         */


        uint64_t result = 0;

        for (int i = 0 ; i < machines.size() ; i++) {
            vector<uint> start = {};
            for (int j = 0 ; j < machines[i]->lights_requirement.size() ; j++) {
                start.push_back(0);
            }
            uint64_t temp = find_min_path(machines[i]->buttons,machines[i]->lights_requirement,start,0);
            cout << temp << endl;
            result += temp;
        }
        cout << result << endl;

        


    } else {
        cerr << "erreur fichier" << endl;
    }

}   
