#include <iostream>
#include <bits/stdc++.h>
using namespace std;

const int JUNC_COUNT = 1000;


// Helper function to parse the data into map of coordinates
void parse_data(ifstream& f, map<int, tuple<int, int, int>>& junc_cords) {
    string buff, temp;

    // Parse data into map
    int idx = 0;
    while (getline(f, buff)) {
        stringstream ss(buff);
        string x, y, z;

        getline(ss, x, ',');
        getline(ss, y, ',');
        getline(ss, z, ',');
        junc_cords[idx] = {stoi(x), stoi(y), stoi(z)};
        idx++;
    }
}


// Helper function to calculate the euclidean distance
long long euclidean_distance(tuple<int, int, int> p1, tuple<int, int, int> p2) {
    long long dx = get<0>(p1) - get<0>(p2);
    long long dy = get<1>(p1) - get<1>(p2);
    long long dz = get<2>(p1) - get<2>(p2);
    return dx * dx + dy * dy + dz * dz;
}


// Helper function that finds and returns index of set that p1 is in
int find_circuit(int p1, vector<set<int>>& circuits) {
    for (int i = 0; i < circuits.size(); i++) {
        if (circuits[i].find(p1) != circuits[i].end())
            return i;
    }

    return -1;
}

/**
 * Solution for day 8 part I
 * Calculates distances between all points, sorts and picks the JUNC_COUNT shortest to connect
 */
long long get_circuits(ifstream& f) {
    map<int, tuple<int, int, int>> junc_cords;
    vector<set<int>> circuits;
    vector<tuple<int, int, long long>> distance_vec;
    parse_data(f, junc_cords);

    int n = junc_cords.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            tuple<int, int, long long> dist;
            get<0>(dist) = i;
            get<1>(dist) = j;
            get<2>(dist) = euclidean_distance(junc_cords[i], junc_cords[j]);
            distance_vec.push_back(dist);
        }
    }

    sort(distance_vec.begin(), distance_vec.end(), [](const auto& a, const auto& b) {
        return get<2>(a) < get<2>(b);
    });
    for(int i = 0; i < JUNC_COUNT; i++) {
        int s1 = find_circuit(get<0>(distance_vec[i]), circuits), s2 = find_circuit(get<1>(distance_vec[i]), circuits);
        if (s1 == s2 && s1 != -1)
            continue;
        else if (s1 == -1 && s2 == -1)
            circuits.push_back({get<0>(distance_vec[i]), get<1>(distance_vec[i])});
        else if (s1 == -1 && s2 != -1)
            circuits[s2].insert(get<0>(distance_vec[i]));
        else if (s1 != -1 && s2 == -1)
            circuits[s1].insert(get<1>(distance_vec[i]));
        else {
            if (s1 > s2) swap(s1, s2);
            set<int> result;
            set_union(circuits[s1].begin(), circuits[s1].end(),
                    circuits[s2].begin(), circuits[s2].end(),
                    inserter(result, result.begin()));

            circuits.erase(circuits.begin() + s2);
            circuits.erase(circuits.begin() + s1);
            circuits.push_back(result);
        }
    }

    sort(circuits.begin(), circuits.end(),
    [](set<int> s1, set<int> s2) {
        return s1.size() > s2.size();
    });
    return circuits[0].size() * circuits[1].size() * circuits[2].size();
}


/**
 * Solution for day 8 part II
 * Calculates distances between all points, sorts and connects all junctions until none are left alone
 */
long long get_max_circuits(ifstream& f) {
    map<int, tuple<int, int, int>> junc_cords;
    vector<set<int>> circuits;
    vector<tuple<int, int, long long>> distance_vec;
    set<int> curr;
    parse_data(f, junc_cords);

    int n = junc_cords.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            tuple<int, int, long long> dist;
            get<0>(dist) = i;
            get<1>(dist) = j;
            get<2>(dist) = euclidean_distance(junc_cords[i], junc_cords[j]);
            distance_vec.push_back(dist);
        }
    }

    sort(distance_vec.begin(), distance_vec.end(), [](const auto& a, const auto& b) {
        return get<2>(a) < get<2>(b);
    });

    for(int i = 0; i < distance_vec.size(); i++) {
        int s1 = find_circuit(get<0>(distance_vec[i]), circuits), s2 = find_circuit(get<1>(distance_vec[i]), circuits);
        if (s1 == s2 && s1 != -1)
            continue;
        else if (s1 == -1 && s2 == -1)
            circuits.push_back({get<0>(distance_vec[i]), get<1>(distance_vec[i])});
        else if (s1 == -1 && s2 != -1) {
            circuits[s2].insert(get<0>(distance_vec[i]));
            curr = circuits[s2];
        } else if (s1 != -1 && s2 == -1) {
            circuits[s1].insert(get<1>(distance_vec[i]));
            curr = circuits[s1];
        } else {
            if (s1 > s2) swap(s1, s2);
            set<int> result;
            set_union(circuits[s1].begin(), circuits[s1].end(),
                    circuits[s2].begin(), circuits[s2].end(),
                    inserter(result, result.begin()));

            circuits.erase(circuits.begin() + s2);
            circuits.erase(circuits.begin() + s1);
            circuits.push_back(result);
            curr = result;
        }

        if (curr.size() == n)
            return 1LL * get<0>(junc_cords[get<0>(distance_vec[i])]) * get<0>(junc_cords[get<1>(distance_vec[i])]);
    }

    return -1;
}


int main(int argc, char* argv[]) {
    ifstream f("../data/data.txt");
    if (!f.is_open()) {
        cerr << "Error opening data file";
        return 1;
    }

    cout << get_max_circuits(f) << "\n";

    return 0;
}