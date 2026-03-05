#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * Solution for day 5 part I.
 * Given file f, parses the data and counts how many id's are in an interval
 */
int count_ingredients(ifstream& f) {
    vector<pair<long long, long long>> interval_vec;
    int count = 0;
    long long ingred_id;
    string buff;

    while (getline(f, buff) && buff.compare("") != 0) {
        size_t separator_idx = buff.find('-');
        interval_vec.push_back({
            stoll(buff.substr(0, separator_idx)), 
            stoll(buff.substr(separator_idx + 1))
        });
    }

    while (getline(f, buff)) {
        ingred_id = stoll(buff);
        for (int i = 0; i < interval_vec.size(); i++) {
            if (ingred_id >= interval_vec[i].first && ingred_id <= interval_vec[i].second) {
                count++;
                break;
            }
        }
    }

    return count;
}

/**
 * Solution for day 5 part II.
 * Given file f, parses the data and counts how many id's are in all the intervals combined (overlap accounted)
 */
long long count_ingredients_all(ifstream& f) {
    vector<pair<long long, long long>> interval_vec, res;
    long long count = 0;
    string buff;

    while (getline(f, buff) && buff != "") {
        size_t separator_idx = buff.find('-');
        interval_vec.push_back({
            stoll(buff.substr(0, separator_idx)),
            stoll(buff.substr(separator_idx + 1))
        });
    }

    sort(interval_vec.begin(), interval_vec.end());

    for (int i = 0; i < interval_vec.size(); i++) {
        long long start = interval_vec[i].first;
        long long end = interval_vec[i].second;

        if (!res.empty() && res.back().second >= end)
            continue;

        int j = i + 1;
        for (; j < interval_vec.size(); j++) {
            if (interval_vec[j].first <= end)
                end = max(end, interval_vec[j].second);
            else
                break;
        }

        res.push_back({start, end});
        i = j - 1;
    }

    for (pair<long long, long long> interval : res)
        count += interval.second - interval.first + 1;

    return count;
}

int main(int argc, char* argv[]) {
    ifstream f("../data/day5.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    cout << count_ingredients_all(f) << "\n";
    return 0;
}