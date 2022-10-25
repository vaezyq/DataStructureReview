//
// Created by 王明龙 on 2022/10/23.
//

#include <vector>

using namespace std;

// 对于两个有序向量[lo,lo+n) 与 [lo2,lo2+n2)查找合并后的中位数
int trivial_median(vector<int> &v, int lo, int n, vector<int> &v2, int lo2, int n2) {
    vector<int> res;       //构造归并后的结果向量
    int hi = lo + n, hi2 = lo2 + n;
    while ((lo < hi) && (lo2 < hi2)) {      //依次将两个向量中更小的元素放入结果容器中
        if (v[lo] <= v2[lo2]) {
            res.emplace_back(v[lo++]);
        } else {
            res.emplace_back(v[lo2++]);
        }
    }
    while (lo < hi) { res.emplace_back(v[lo++]); };
    while (lo2 < hi2) { res.emplace_back(v[lo2++]); };
    return res[(n + n2) / 2];
}

int median(vector<int> &v, int lo, vector<int> &v2, int lo2, int n) {
    if (n < 3) return trivial_median(v, lo, n, v2, lo2, n);
    int mi = lo + n / 2, mi2 = lo + (n - 1) / 2;
    if (v[mi] < v2[mi2]) {
        return median(v, mi, v2, lo2, n + lo - mi);
    } else if (v2[mi2] < v[mi]) {
        return median(v, lo, v2, mi2, n + lo2 - mi2);
    } else {
        return v[mi];
    }
}

int median(vector<int> &v, int lo, int n, vector<int> &v2, int lo2, int n2) {
    if (n > n2) {      //确保 n <= n2
        return median(v2, lo2, n2, v, lo, n);
    }
    if (n2 < 6) {   //当范围很小时，直接调用暴力求解
        return trivial_median(v, lo, n, v2, lo2, n);
    }



    if (2 * n < n2) {   //当v2 的长度大于二倍的v时,可以直接读v2 剪去两边的元素
        return median(v, lo, n, v2, lo2 + (n2 - n - 1) / 2, n + 2 - (n2 - n) % 2);
    }

}


int main() {
    vector<int> v{1, 2, 3, 4, 5};
    vector<int> v2{8, 9, 10};



}