#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    vector<vector<uint64_t>> numbers; //each element is a line
    ifstream input ("input.txt");
    string buffer;

    uint64_t total = 0;

    int line_counter = 0;
    while (getline(input,buffer)) {
        numbers.push_back({});
        stringstream line_stream  (buffer);
        string token;
        if (buffer[0] != '*' && buffer[0] != '+') {
            while(getline(line_stream,token,' ')) {
                if (token.size() == 0) continue;
                numbers[line_counter].push_back(stoll(token));
            }
            cout << endl;
        } else {
            int column = 0;
            while(getline(line_stream,token,' ')) {
                if (token.size() == 0) continue;
                else if (token[0] == '+') {
                    uint64_t local_result = 0;
                    for (int j = 0; j < line_counter ; j++) {
                        local_result += numbers[j][column];
                    }
                    column ++;
                    cout << "local result : " << local_result << endl;
                    total += local_result;
                } else if (token[0] == '*') {
                    uint64_t local_result = 1;
                    for (int j = 0; j < line_counter ; j++) {
                        local_result *= numbers[j][column];
                    }
                    column ++;
                    cout << "local result : " << local_result << endl;
                    total += local_result;
                }
            }
        }
        line_counter++;
    }
    cout << "total : " << total << endl;

    return 0;
}