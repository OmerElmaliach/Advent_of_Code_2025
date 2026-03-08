#include <iostream>
#include <bits/stdc++.h>
using namespace std;


/**
 * Helper function to parse data into char vectors
 */
void parse_data(ifstream &f, vector<vector<char>> &data) {
    string buff;

    // Parse into char matrix
    while (getline(f, buff)) {
        vector<char> line;
        for(char chr : buff)
            line.push_back(chr);

        data.push_back(line);
    }
}


/**
 * Recursive helper function for counting all beam splits
 */
int count_beams_ox(int row, int column, vector<vector<char>> &data) {
    if (row >= data.size() || column >= data[0].size()) 
        return 0;

    while (row < data.size() && column < data[0].size()) {
        if (data[row][column] == '^') {
            data[row][column] = '*';
            return count_beams_ox(row, column + 1, data) + count_beams_ox(row, column - 1, data) + 1;
        } else if (data[row][column] == '*') {
            return 0;
        } else {
            row += 1;
        }
    }

    return 0;
}


/**
 * Solution for day 7 part I
 * Counts beam splits at character '^' using recursive function
 */
int count_beams(ifstream &f) {
    vector<vector<char>> data;
    parse_data(f, data);

    return count_beams_ox(0, data[0].size() / 2, data);
}


/**
 * Solution for day 7 part II
 * Counts all timelines from S by precalculating timelines of later ^ in the input
 */
long long count_quantum_beams(ifstream &f) {
    map<pair<int, int>, long long> timeline_dict;
    vector<vector<char>> data;
    parse_data(f, data);

    for (int row = data.size() - 2; row >= 0; row -= 2) {
        for (int column = 0; column < data[0].size(); column++) {
            if (data[row][column] == '^' || data[row][column] == 'S') {
                long long left = 0, right = 0;
                int jmp_row = 0;

                // Left calculation
                while (row + jmp_row < data.size() && data[row + jmp_row][column - 1] != '^')
                    jmp_row++;

                if (row + jmp_row == data.size())
                    left = 1;
                else
                    left = timeline_dict[{row + jmp_row, column - 1}];

                jmp_row = 0;

                // Right calculation
                while (row + jmp_row < data.size() && data[row + jmp_row][column + 1] != '^')
                    jmp_row++;

                if (row + jmp_row == data.size())
                    right = 1;
                else
                    right = timeline_dict[{row + jmp_row, column + 1}];

                timeline_dict[{row, column}] = left + right;
            }
        }
    }

    return timeline_dict[{0, data[0].size() / 2}];

}


int main(int argc, char* argv[]) {
    ifstream f("../data/data.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    cout << count_quantum_beams(f) << "\n";

    return 0;
}