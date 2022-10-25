//
// Created by 王明龙 on 2022/10/22.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int partition_LUG(vector<int> &v, int lo, int hi) {
    swap(v[lo], v[lo + rand() % (hi - lo + 1)]);
    auto pivot{v[lo]};
    while (lo < hi) {
        while ((lo < hi) && (pivot <= v[hi])) { hi--; }
        v[lo] = v[hi];

        while (lo < hi && (v[lo] <= pivot)) { lo++; }
        v[hi] = v[lo];
    }
    v[lo] = pivot;
    return lo;
}


int partition_LUG_var(vector<int> &v, int lo, int hi) {
    swap(v[lo], v[lo + rand() % (hi - lo + 1)]);
    auto pivot{v[lo]};
    while (lo < hi) {
        while ((lo < hi) && (pivot <= v[hi])) { hi--; }
        if (lo < hi) {
            v[lo++] = v[hi];
        }
        while (lo < hi && (v[lo] <= pivot)) { lo++; }
        if (lo < hi) {
            v[hi--] = v[lo];
        }
    }
    v[lo] = pivot;
    return lo;
}


int partition_DUP(vector<int> &v, int lo, int hi) {
    swap(v[lo], v[lo + rand() % (hi - lo + 1)]);
    auto pivot{v[lo]};
    while (lo < hi) {
        while ((lo < hi) && (pivot < v[hi])) { hi--; }
        if (lo < hi) {
            v[lo++] = v[hi];
        }
        while (lo < hi && (v[lo] < pivot)) { lo++; }
        if (lo < hi) {
            v[hi--] = v[lo];
        }
    }
    v[lo] = pivot;
    return lo;
}


int partition_LGU(vector<int> &v, int lo, int hi) {
    swap(v[lo], v[lo + rand() % (hi - lo + 1)]);
    auto pivot{v[lo]};
    auto mi = lo;
    for (auto k = lo + 1; k <= hi; ++k) {
        if (v[k] < pivot) {
            swap(v[++mi], v[k]);
        }
    }
    swap(v[mi], v[lo]);
    return mi;
}


void quick_sort(vector<int> &v, int lo, int hi) {
    if (hi - lo <= 0) {
        return;
    }
    auto mi = partition_LUG(v, lo, hi);
    quick_sort(v, lo, mi - 1);
    quick_sort(v, mi + 1, hi);
}


#define Put(S, lo, hi)  { if(lo < hi){ S.push({lo,hi}); } }

void quick_sort_no_recursive(vector<int> &v, int lo, int hi) {
    stack<pair<int, int>> task;
    Put(task, lo, hi);
    while (!task.empty()) {
        auto idx = task.top();
        task.pop();
        lo = idx.first, hi = idx.second;
        auto mi = partition_LGU(v, lo, hi);
        if (mi - lo < hi - mi) {
            Put(task, mi + 1, hi);
            Put(task, lo, mi - 1);
        } else {
            Put(task, lo, mi - 1);
            Put(task, mi + 1, hi);
        }
    }
}

