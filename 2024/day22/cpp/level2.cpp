#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <cstdint>

using namespace std;

using serie_type = tuple<int64_t,int64_t,int64_t,int64_t>;


template<>
struct std::hash<serie_type> {
    size_t operator()(const serie_type & serie) const {
        return get<0>(serie) * 7 + get<1>(serie) *13 + get<2>(serie) * 17 + get<3>(serie) *19;
    }
};

int64_t get_next_secret(int64_t secret_number) {
    secret_number = ((secret_number*64)^secret_number)%16777216;
    secret_number = ((secret_number/32)^secret_number)%16777216;
    secret_number = ((secret_number*2048)^secret_number)%16777216;
    return secret_number;
}

 unordered_map<serie_type,int64_t>  get_differences(int64_t secret_number) {
    unordered_map<serie_type,int64_t> series;
    vector<int64_t> differences;
    int64_t last_price = secret_number%10;
    vector<int64_t> prices = {};
    for (int i = 0 ; i < 2000 ; i++) {
        secret_number = get_next_secret(secret_number);
        int64_t price = secret_number%10;
        differences.push_back(price - last_price);
        last_price = price;
        prices.push_back(price);
    }
    for (int i = 0 ; i < differences.size() - 3 ; i++) {
        serie_type serie = make_tuple(differences[i],differences[i+1],differences[i+2],differences[i+3]);
        if (series.find(serie) == series.end()) series[serie] = prices[i+3];
    }
    return series;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "file opening error" << endl;
        return 1;
    }
    string buffer;


    unordered_map<serie_type,int64_t> series;

    while (getline(file,buffer)) {
        unordered_map<serie_type,int64_t> new_series = get_differences(stoull(buffer));
        for (auto paire : new_series) {
            if (series.find(paire.first) == series.end()) {
                series.insert(paire);
            } else {
                series[paire.first] += paire.second;
            }
        }

    }

   int64_t max_price = 0;
    for (auto paire : series) {
        if (paire.second > max_price) max_price = paire.second;
    }

    cout << max_price << endl;




    return 0;
}