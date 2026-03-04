#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * Solution for day 4.
 * Given a vector of binary strings, iterate each string and count each 'roll of paper' (1 surrounded by less than 4 1's) found
 */
pair<int, vector<string>> count_rolls(vector<string> data) {
    vector updated = data;
    long long line_size = data[0].length(), sum, count = 0;
    for (int i = 1; i < data.size() - 1; i++) {
        for (int j = 1; j < line_size - 1; j++) {
            if (data[i][j] == '1') {
                sum = data[i - 1][j - 1] + data[i - 1][j] + data[i - 1][j + 1] + 
                        data[i + 1][j - 1] + data[i + 1][j] + data[i + 1][j + 1] + 
                        data[i][j - 1] + data[i][j + 1] - (8 * '0');

                if (sum < 4) {
                    count++;
                    updated[i].replace(j, 1, 1, '0');
                }
            }
        }
    }

    return {count, updated};
}

/**
 * Function for parsing the data into binary string vector, padding with a layer of 0
 */
vector<string> parse_input(ifstream& f) {
    string buff;
    vector<string> data;
    while (getline(f, buff)) {
        replace(buff.begin(), buff.end(), '@', '1');
        replace(buff.begin(), buff.end(), '.', '0');
        buff = '0' + buff + '0';
        data.push_back(buff);
    }

    // Padding
    data.insert(data.begin(), string(buff.length(), '0'));
    data.push_back(string(buff.length(), '0'));
    return data;
}

int main(int argc, char* argv[]) {
    ifstream f("../data/day4.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    int sum = 0;
    vector<string> data = parse_input(f);
    pair<int, vector<string>> res = count_rolls(data);
    while(res.first != 0) {
        sum += res.first;
        res = count_rolls(res.second);
    }

    cout << sum << '\n';
    return 0;
}