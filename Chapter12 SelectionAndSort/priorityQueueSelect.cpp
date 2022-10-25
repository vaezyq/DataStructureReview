//
// Created by 王明龙 on 2022/10/22.
//

#include <iostream>
#include <queue>

using namespace std;


int n_th_select_by_small_heap(const vector<int> &v, int k) {
    //将全部元素组织为小顶堆,并对小顶堆操作k次的delMin()
    priority_queue<int, vector<int>, greater<>> kq;      //组织为小顶堆kq
    for (auto &e: v) {
        kq.push(e); //将序列中的全部元素都加入kq中
    }
    while (--k) {
        kq.pop();     //删除小顶堆中的前k个元素
    }
    return kq.top();   //返回堆顶
}

int n_th_select_by_large_heap(const vector<int> &v, int k) {
    priority_queue<int> kq;
    for (auto i = 0; i < k; ++i) { kq.push(v[i]); }
    for (int i = k + 1; i < v.size(); ++i) {
        kq.push(v[i]);
        kq.pop();
    }
    return kq.top();
}


int n_th_select_by_small_large_heap(const vector<int> &v, int k) {
    priority_queue<int, vector<int>, greater<>> small_pq;
    priority_queue<int> large_pq;
    for (int i = 0; i < v.size() - k; ++i) { small_pq.push(v[i]); };
    for (int i = v.size() - k; i < v.size(); ++i) { large_pq.push(v[i]); };
    while (small_pq.top() < large_pq.top()) {
        int tem = large_pq.top();
        large_pq.push(small_pq.top());
        large_pq.pop();
        small_pq.push(tem);
        small_pq.pop();
    }
    return large_pq.top();
}


int main() {

    vector<int> v{1, 5, 6, 3, 4, 8, 9, 7};

    cout << n_th_select_by_small_heap(v, 5) << endl;
    cout << n_th_select_by_large_heap(v, 5) << endl;
    cout << n_th_select_by_small_large_heap(v, 5) << endl;
}