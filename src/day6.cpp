#include <iostream>
#include <bits/stdc++.h>
using namespace std;


/**
 * Helper function to parse data into vectors
 */
void parse_data(ifstream& f, vector<long long> &numbers, vector<string> &ops) {
    string buff, temp;
    while (getline(f, buff)) {
        stringstream ss(buff);
        while (ss >> temp) {
            if (temp.compare("*") == 0 || temp.compare("+") == 0) {
                ops.push_back(temp);
            } else {
                numbers.push_back(stoll(temp));
            }
        }
    }
}


/**
 * Solution for day 6 part I
 * Given vector of numbers and operations, performs operations and sums the results
 */
long long solve_equations(ifstream& f) {
    long long sum = 0;
    vector<long long> numbers;
    vector<string> ops;

    parse_data(f, numbers, ops);

    int n = numbers.size(), m = ops.size();
    for (int i = 0; i < m; i++) {
        long long temp_sum = 0;
        if (ops[i].compare("+") == 0) {
            for (int j = i; j < n; j += m)
                temp_sum += numbers[j];
        } else {
            temp_sum = 1;
            for (int j = i; j < n; j += m)
                temp_sum *= numbers[j];
        }
        sum += temp_sum;
    }

    return sum;
}


/**
 * Solution for day 6 part II
 * Parses the data file into char matrix and performs 'Cephalopod math' for each column, sums and returns the result
 */
long long solve_equations_cephalopod(ifstream& f) {
    long long sum = 0;
    vector<vector<char>> data;
    string buff;

    // Parse into char matrix
    while (getline(f, buff)) {
        vector<char> line;
        for(char chr : buff)
            line.push_back(chr);

        data.push_back(line);
    }

    int column = data[0].size(), row = data.size();
    char curr_op;
    long long temp_sum = 0, temp = 0;
    for (int i = 0; i < column; i++) {
        // Reset operation cycle and add to sum
        if (data[row - 1][i] == '+' || data[row - 1][i] == '*') {
            sum += temp_sum;
            curr_op = data[row - 1][i];
            temp_sum = (curr_op == '*') ? 1 : 0;
        }

        // Build number from column
        for (int j = 0; j < row - 1; j++) {
            if (data[j][i] != ' ')
                temp = (temp * 10) + (data[j][i] - '0');
        }

        if (curr_op == '+')
            temp_sum += temp;
        else
            temp_sum *= (temp != 0 ? temp : 1);

        temp = 0;
    }

    return sum + temp_sum;
}


int main(int argc, char* argv[]) {
    ifstream f("../data/data.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    cout << solve_equations_cephalopod(f) << "\n";

    return 0;
}