//
// Created by 王明龙 on 2022/10/22.
//
#include <vector>
#include <optional>
#include <algorithm>

using namespace std;

int major_candidate(const vector<int> &v) {
    int maj{0};

    for (int c = 0, i = 0; i < v.size(); ++i) {
        if (c == 0) {
            maj = v[i];
            c++;
        } else {
            maj == v[i] ? c++ : c--;
        }
    }
    return maj;
}


optional<int> majority(const vector<int> &v) {
    optional<int> op;
    auto maj = major_candidate(v);
    auto occurrence = count_if(v.begin(), v.end(), [maj](int i) {
        return i == maj;
    });
    if (2 * occurrence > v.size()) {
        return (op = maj);
    }
}

