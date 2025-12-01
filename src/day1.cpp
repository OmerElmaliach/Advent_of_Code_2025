#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * Solution for part one
 */
int part_one(ifstream& f) {
    string s;
    int count = 0, pos = 50;
    while (getline(f, s)) {
        int rotation = atoi(s.substr(1).c_str());
        pos = (s.at(0) == 'R' ? (pos + rotation) : 100 + (pos - rotation)) % 100;
        if (pos == 0)
            count++;
    }

    return count;
}

/**
 * Solution for part two
 */
int part_two(ifstream& f) {
    string s;
    int count = 0, pos = 50;
    while (getline(f, s)) {
        int rotation = atoi(s.substr(1).c_str());
        count += (rotation / 100);  // Count full rotations
        rotation %= 100;

        if (s.at(0) == 'R') {
            pos += rotation;
            if (pos > 100)
                count++;
            pos %= 100;
        } else {
            pos -= rotation;
            if (pos < 0 && pos + rotation != 0)
                count++;
            pos = (100 + pos) % 100;
        }
        
        if (pos == 0)
            count++;
    }

    return count;
}

int main(int argc, char* argv[]) {
    ifstream f("../data/day1.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    cout << part_two(f) << '\n';

    f.close();
    return 0;
}