//
// Created by 王明龙 on 2022/10/22.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void shell_sort(vector<int> &v, int lo, int hi) {
    // Using PS Sequence { 1, 3, 7, 15, 31, 63, 127, ..., 1073741823, ... }
    for (auto d = 0x3FFFFFFF; 0 < d; d >>= 1) {
        //内部使用插入排序徐来实现增量序列内部的有序
        for (auto i = lo + d; i <= hi; ++i) { //对于[lo+d,hi]中的所有元素
            auto elem = v[i], j = i - d;
            while (lo <= j && v[j] > elem) {
                v[j + d] = v[j];
                j -= d;
            }
            v[j + d] = elem;
        }
    }
}














