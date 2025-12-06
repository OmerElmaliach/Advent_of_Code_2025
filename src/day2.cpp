#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<string> parse_data(ifstream& f) {
    string line;
    vector<string> data;
    while (getline(f, line, ',')) {
        data.push_back(line);
    }

    return data;
}

/**
 * Solution for part one
 */
long part_one(const vector<string>& data) {
    long sum = 0;
    for (string range : data) {
        string start = range.substr(0, range.find('-')), end = range.substr(range.find('-') + 1);
        long start_num = stoll(start.c_str()), end_num = stoll(end.c_str());
        for (long i = start_num; i <= end_num; i++) {
            string i_str = to_string(i);
            if (i_str.size() % 2 == 1)
                continue;

            if (i_str.substr(0, i_str.size() / 2) == i_str.substr(i_str.size() / 2))
                sum += i;
        }
    }

    return sum;
}

/**
 * Solution for part two
 */
long part_two(const vector<string>& data) {
    long sum = 0;
    for (string range : data) {
        string start = range.substr(0, range.find('-')), end = range.substr(range.find('-') + 1);
        long start_num = stoll(start.c_str()), end_num = stoll(end.c_str());
        for (long i = start_num; i <= end_num; i++) {
            string i_str = to_string(i);
            for (int j = 1; j < (i_str.size() / 2) + 1; j++) {
                if (i_str.size() % j != 0)
                    continue;
                
                bool con = true;
                for (int k = 0; k < i_str.size() - j; k += j) {
                    if (i_str.substr(k, j) != i_str.substr(k + j, j)) {
                        con = false;
                        break;
                    }
                }

                if (con) {
                    sum += i;
                    break;
                }
            }
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {
    ifstream f("../data/day2.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    cout << part_two(parse_data(f)) << '\n';
    return 0;
}