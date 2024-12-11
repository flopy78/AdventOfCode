#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <chrono>
using namespace std;

template<>
struct std::hash<tuple<int,long long>> {
    size_t operator()(const tuple<int, long long> &key) const {
        return 2 * get<0>(key) + 3 * get<1>(key);
    }
};


using namespace chrono;
using memo = unordered_map<tuple<int,long long>,long long>;
memo memoizator;




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

long long get_n_stones(vector<long long> stones,int depth) {
    if (depth == 75) {
        return stones.size();
    }
    long long n_stones = 0;
    long long n_more_stones = 0;
    for (long long stone : stones) {

        if (memoizator[make_pair(stone,depth)] != 0) {
            n_more_stones = memoizator[make_pair(stone,depth)];
        } else {
            vector<long long> next_step = simulate_stone(stone);
            n_more_stones = get_n_stones(next_step,depth+1);
            memoizator[make_pair(stone,depth)] = n_more_stones;
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


    long long n_stones = get_n_stones(stones,0);

    cout << n_stones << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout << duration.count()/1e6 << "s" << endl;


    return 0;
}