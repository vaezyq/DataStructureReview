//
// Created by 王明龙 on 2022/10/23.
//
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int Q = 2;

int trivial_select(vector<int> &v, int k) {
    sort(v.begin(), v.end());
    return v[k - 1];
}

int select(vector<int> &v, int k) {
    if (v.size() < 3) {  //递归基：使用蛮力算法
        return trivial_select(v, k);
    }

    int d = v.size() / Q;
    vector<int> tem;
    for (int i = 0; i < d; ++i) {
        sort(v.begin() + i * Q, v.begin() + (i + 1) * Q);
        tem.emplace_back(*(v.begin() + i * Q + Q / 2));
    }
    if ((v.begin() + d * Q) != v.end()) {
        sort(v.begin() + d * Q, v.end());
        tem.emplace_back(*(v.begin() + (v.size() + Q * d) / 2));
    }


    auto mi = select(tem, tem.size() / 2);


    vector<int> less_mi;
    vector<int> equal_mi;
    vector<int> more_mi;
    for (auto e: v) {
        if (e < mi) {
            less_mi.emplace_back(e);
        } else if (mi < e) {
            more_mi.emplace_back(e);
        } else {
            equal_mi.emplace_back(e);
        }
    }
    if (k <= less_mi.size()) {
        return select(less_mi, k);
    } else if ((less_mi.size() + equal_mi.size()) >= k) {
        return mi;
    } else {
        return select(more_mi, k - less_mi.size() - equal_mi.size());
    }

}


int main() {

//    int size{0}, n{0};
//    cin >> size >> n;
//    vector<int> vec;
//    generate_n(back_inserter(vec), size, [x = 0]()mutable {
//        cin >> x;
//        return x;
//    });
    vector<int> vec = {50 ,43 ,63 ,97, 30 ,89 ,89 ,94 ,30, 33};
    cout << select(vec, 10);

}