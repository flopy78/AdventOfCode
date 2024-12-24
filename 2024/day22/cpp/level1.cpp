#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <cstdint>

using namespace std;


uint64_t get_next_price(uint64_t secret_number) {
    secret_number = ((secret_number*64)^secret_number)%16777216;
    secret_number = ((secret_number/32)^secret_number)%16777216;
    secret_number = ((secret_number*2048)^secret_number)%16777216;
    return secret_number;
}

uint64_t get_2000th_price(uint64_t secret_number) {
    for (int i = 0 ; i < 2000 ; i++) {
        secret_number = get_next_price(secret_number);
    }
    return secret_number;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "file opening error" << endl;
        return 1;
    }
    string buffer;

    uint64_t solution = 0;

    while (getline(file,buffer)) {
        solution += get_2000th_price(stoull(buffer));
    }

    cout << solution << endl;
    return 0;
}