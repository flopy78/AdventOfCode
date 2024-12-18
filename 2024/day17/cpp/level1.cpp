#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;
using reg_map = unordered_map<char,int>;

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

vector<int> map_stoi(vector<string> input) {
    vector<int> output {};
    for (string number : input) {
        output.push_back(stoi(number));
    }
    return output;
} 

int power(int x, int n) {
    int p = 1;
    for (int i = 0 ; i < n ; i++) {
        p *= x;
    }
    return p;
}

int get_combo_arg(int x, reg_map & registers) {
    int arg = x;
    if (x == 4) arg = registers['A'];
    else if (x == 5) arg = registers['B'];
    else if (x == 6) arg = registers['C'];
    return arg;
}

int adv(int x,reg_map & registers) {
    int arg = get_combo_arg(x, registers);

    registers['A'] = registers['A']/power(2,arg);
    return 2; //numbers of ptr steps
}

int bxl(int x,reg_map & registers) {
    registers['B'] = registers['B'] ^ x;
    return 2;
}

int bst(int x, reg_map & registers) {
    registers['B'] = get_combo_arg(x,registers)%8;
    return 2;
}

int jnz(int x,reg_map & registers, int ptr) {
    if (registers['A'] == 0) {
        return 2;
    } else {
        return x-ptr;
    }
}

int bxc(int x, reg_map & registers) {
    registers['B'] = registers['B'] ^ registers['C'];
    return 2;
}

int out(int x, reg_map & registers, vector<int> & output) {
    output.push_back(get_combo_arg(x,registers)%8);
    return 2;
}

int bdv(int x,reg_map & registers) {
    int arg = get_combo_arg(x, registers);

    registers['B'] = registers['A']/power(2,arg);
    return 2; //numbers of ptr steps
}

int cdv(int x,reg_map & registers) {
    int arg = get_combo_arg(x, registers);

    registers['C'] = registers['A']/power(2,arg);
    return 2; //numbers of ptr steps
}


int main() {
    ifstream file("input.txt");
    string buffer;
    reg_map registers;

    for (int i = 0 ; i < 3 ; i++) {
        getline(file,buffer);
        vector<string> data = split(buffer,':');
        char register_name = split(data[0],' ')[1][0];
        int register_value = stoi(data[1].substr(1,data[1].size()));
        registers[register_name] = register_value;
    }

    getline(file,buffer); // empty line

    getline(file,buffer); // program


    
    vector<int> program = map_stoi(split(split(buffer,' ')[1],','));

    vector<int> output {};

    int program_ptr = 0;
    int n_i = 0;
    int opcode,arg;
    while (program_ptr < program.size() - 1) {
        opcode = program[program_ptr];
        arg = program[program_ptr+1];
        /*cout << program_ptr << endl;
        cout << opcode << " " << arg << endl;
        cout << "A : " << registers['A'] << " B : " << registers['B'] << " C : " << registers['C'] << endl;
        */
        switch(opcode) {
            case 0:
                program_ptr += adv(arg,registers);
                break;
            case 1:
                program_ptr += bxl(arg,registers);
                break;
            case 2:
                program_ptr += bst(arg,registers);
                break;
            case 3:
                program_ptr += jnz(arg,registers,program_ptr);
                break;
            case 4:
                program_ptr += bxc(arg,registers);
                break;
            case 5:
                program_ptr += out(arg,registers,output);
                break;
            case 6:
                program_ptr += bdv(arg,registers);
                break;
            case 7:
                program_ptr += cdv(arg,registers);
                break;
        }

        n_i ++;
        //if (n_i >= 5) return 0;
    }

    for (int n : output) {
        cout << n << ",";
    }

    cout << endl;
    
    return 0;
}

