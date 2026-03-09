#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// Helper function to parse dataa into a vector
void parse_data(ifstream& f, vector<pair<long long, long long>>& coords) {
    string buff;
    while (getline(f, buff))
        coords.push_back({stoi(buff.substr(buff.find(',') + 1)), stoi(buff.substr(0, buff.find(',')))});
}


/**
 * Solution for day 9 part I
 * Calculate max rectangle size between two points
 */
long long find_biggest_rect(ifstream& f) {
    vector<pair<long long, long long>> coords;
    parse_data(f, coords);

    long long width, height, max_size = 0;
    for(int i = 0; i < coords.size(); i++) {
        for(int j = i + 1; j < coords.size(); j++) {
            width = abs(coords[i].first - coords[j].first) + 1;
            width = (width == 0) ? 1 : width;

            height = abs(coords[i].second - coords[j].second) + 1;
            height = (height == 0) ? 1 : height;

            max_size = max(max_size, 1LL * width * height);
        }
    }

    return max_size;
}


int main(int argc, char* argv[]) {
    ifstream f("../data/data.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    cout << find_biggest_rect(f) << '\n';

    return 0;
}