#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * Solution for day 6 part I
 * Given vector of numbers and operations, performs operations and sums the results
 */
long long solve_equations(vector<long long> &numbers, vector<string> &ops) {
    long long sum = 0;

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

long long solve_equations_cephalopod(vector<long long> &numbers, vector<string> &ops) {
    long long sum = 0;

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
 * Helper function to parse data into vectors
 */
void parse_data(ifstream& f, vector<long long> &numbers, vector<string> &ops) {
    string buff, temp;
    while (getline(f, buff)) {
        stringstream ss(buff);
        while(ss >> temp) {
            if (temp.compare("*") == 0 || temp.compare("+") == 0) {
                ops.push_back(temp);
            } else {
                numbers.push_back(stoll(temp));
            }
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream f("../data/data.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    vector<long long> numbers;
    vector<string> ops;
    parse_data(f, numbers, ops);

    cout << solve_equations(numbers, ops) << "\n";

    return 0;
}