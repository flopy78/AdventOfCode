#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> product(string iter,int repeat) {
    vector<string> prod {""};
    for (int i = 0 ; i < repeat ; i++) {
        vector<string> new_prod{};
        for (string comb : prod) {
            for (char elt : iter) {
                new_prod.push_back(comb+elt);
            }
        }
        prod = new_prod;
    }
    return prod;
}

int main() {
    for (string kuplet : product("+*",2)) {
        cout << kuplet << endl;
    }
    return 0;
}