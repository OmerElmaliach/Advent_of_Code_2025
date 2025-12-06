#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * Solution for day 3.
 * Given a file f and an integer k, iterates through each number in the file
 * and finds the maximum number comprising of k digits for each.
 *
 * Part 1: k = 2
 * Part 2: k = 12
 */
long long k_biggest_number(ifstream& f, int k) {
    long long sum = 0;
    string buff;
    while (getline(f, buff)) {
        int n = buff.size(), currIdx = 0;
        for (int i = k - 1; i >= 0; i--) {
            int maxDigit = 0;
            // Find biggest digit from the left starting from currIdx
            for (int j = currIdx; j < n - i; j++) {
                if (maxDigit < buff[j] - '0') {
                    maxDigit = buff[j] - '0';
                    currIdx = j + 1;
                }
            }

            sum += maxDigit * (pow(10, i));
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {
    ifstream f("../data/day3.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    cout << k_biggest_number(f, 12) << '\n';
    return 0;
}