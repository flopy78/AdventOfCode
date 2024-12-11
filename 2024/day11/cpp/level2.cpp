#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <chrono>

using namespace std;
using namespace chrono;
using memo = map<tuple<int,long long>,long long>;

vector<long long> simulate_stone(long long stone) {
    vector<long long> next_step {};
    if (stone == 0) {
        next_step = {1};
    } else if (to_string(stone).length()%2==0) {
        string digits = to_string(stone);
        next_step.push_back(stoll(digits.substr(0,digits.length()/2)));
        next_step.push_back(stoll(digits.substr(digits.length()/2,digits.length())));
    } else {
        next_step = {2024*stone};
    }
    return next_step;
}

long long get_n_stones(vector<long long> stones,memo * memo_ptr,int depth) {
    if (depth == 75) {
        return stones.size();
    }
    long long n_stones = 0;
    long long n_more_stones = 0;
    for (long long stone : stones) {
        if ((*memo_ptr)[make_pair(stone,depth)] != 0) {
            n_more_stones = (*memo_ptr)[make_pair(stone,depth)];
        } else {
            vector<long long> next_step = simulate_stone(stone);
            n_more_stones = get_n_stones(next_step,memo_ptr,depth+1);
            (*memo_ptr)[make_pair(stone,depth)] = n_more_stones;
        }

        n_stones += n_more_stones;
    }
    return n_stones;
}

vector<long long> split(string str,char delim) {
    string buffer = "";
    vector<long long> split {};

    for (char c : str) {
        if (c == delim) {
            split.push_back(stoll(buffer));
            buffer = "";
        } else {
            buffer += c;
        }
    }
    if (buffer.size() > 0) {
        split.push_back(stoll(buffer));
    }
    return split;
}

int main() {
    auto start = high_resolution_clock::now();
    ifstream file("input.txt");
    string line;
    getline(file,line);
    vector<long long> stones {split(line,' ')};

    memo memoizator {};

    long long n_stones = get_n_stones(stones,&memoizator,0);

    cout << n_stones << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout << duration.count()/1e6 << "s" << endl;


    return 0;
}