#include "PQ.hpp"
#include<vector>
#include <optional>
#include <memory>

using namespace std;

template<typename T>
class PQ_ComplHeap : public PQ<T> {      //基于抽象类PQ与vector构造完全二叉堆

public:
    explicit PQ_ComplHeap() = default;       //默认构造函数

    explicit PQ_ComplHeap(vector<T> &vec) {
        copy(vec.begin(), vec.end(), back_inserter(complete_bin_heap));
        heapify();
    }

    void insert(T &&elem);   //插入元素

    T get_max() const;        //读取优先级最高的词条

    T del_max();      //删除优先级最高的词条

    void heap_sort(vector<T> &res);

protected:
    using Rank = typename vector<T>::difference_type;      //定义向量下表类型的别名

    Rank percolate_down(int i);    //下滤

    [[deprecated("old up algorithm")]]     //普通的上滤算法
    Rank percolate_up_old(int i);   //上滤

    Rank percolate_up(int i);   //上滤

    void heapify();   //floyd建堆

    inline static bool parent_valid(Rank i) { return 0 < i; };    //判断节点i是否有父亲节点

    inline static Rank parent(Rank i) { return (i - 1) >> 1; }       //返回i的父亲节点

    inline Rank proper_child(Rank i);         //返回节点i及其孩子中优先级最高的节点坐标

    inline bool is_valid(Rank i);          //判断编号i是否有效

private:

    vector<T> complete_bin_heap;     //基于向量存储完全二叉堆
};

template<typename T>
T PQ_ComplHeap<T>::get_max() const {
    return *complete_bin_heap.begin();
}


template<typename T>
void PQ_ComplHeap<T>::insert(T &&elem) {
    complete_bin_heap.insert(complete_bin_heap.end(), forward<T>(elem));   //将词条插入二叉堆中(插入到向量的末尾)
    percolate_up(complete_bin_heap.size() - 1);   //执行上滤操作
}

template<typename T>
typename PQ_ComplHeap<T>::Rank PQ_ComplHeap<T>::percolate_up_old(int i) {   //对节点i执行上滤操作
    while (parent_valid(i)) {     //只要i有父亲
        auto j = parent(i);   //得到其父亲索引
        if (complete_bin_heap[i] <= complete_bin_heap[j]) {
            break;    //一旦不再逆序，则上滤结束
        }
        swap(complete_bin_heap[i], complete_bin_heap[j]);   //交换i,j元素内容，完成上滤
        i = j;  //i指向父亲节点j，继续进行长滤
    }
    return i;        //返回上滤最终抵达的位置
}

template<typename T>
typename PQ_ComplHeap<T>::Rank PQ_ComplHeap<T>::percolate_up(int i) {       //不需要每次都执行交换(交换需要三次赋值操作)
    auto value{complete_bin_heap[i]};
    while (parent_valid(i)) {     //只要i有父亲
        auto j = parent(i);   //得到其父亲索引
        if (complete_bin_heap[i] <= complete_bin_heap[j]) {
            break;    //一旦不再逆序，则上滤结束
        }
        complete_bin_heap[i] = complete_bin_heap[j]; //将小元素下滤
        i = j;  //i指向父亲节点j，继续进行长滤
    }
    complete_bin_heap[i] = value;   //将上滤的元素归位
    return i;        //返回上滤最终抵达的位置
}

template<typename T>
T PQ_ComplHeap<T>::del_max() {
    auto max_elem = complete_bin_heap[0];    //取出堆顶元素
    complete_bin_heap[0] = *(complete_bin_heap.end() - 1);        //将堆顶元素与堆尾元素交换
    complete_bin_heap.erase(complete_bin_heap.end() - 1);       //删除堆尾元素
    percolate_down(0);       //执行下滤
    return max_elem;
}

template<typename T>
typename PQ_ComplHeap<T>::Rank PQ_ComplHeap<T>::percolate_down(int i) {
    Rank j = 0;
    while (i != (j = proper_child(i))) {
        swap(complete_bin_heap[i], complete_bin_heap[j]);
        i = j;
    }
    return i;
}

template<typename T>
typename PQ_ComplHeap<T>::Rank PQ_ComplHeap<T>::proper_child(PQ_ComplHeap::Rank i) {
    auto idx = i;
    if (is_valid(2 * i + 1)) {
        if (complete_bin_heap[2 * i + 1] > complete_bin_heap[i]) {
            idx = 2 * i + 1;
        }
    }
    if (is_valid(2 * i + 2)) {
        if (complete_bin_heap[2 * i + 2] > complete_bin_heap[idx]) {
            idx = 2 * i + 2;
        }
    }
    return idx;
}

template<typename T>
void PQ_ComplHeap<T>::heapify() {
    for (auto i = parent(complete_bin_heap.size() - 1); 0 <= i; --i) {
        percolate_down(i);     //下滤内部节点
    }
}


template<typename T>
void PQ_ComplHeap<T>::heap_sort(vector<T> &res) {
    while (!complete_bin_heap.empty()) {
        res.emplace_back(del_max());
    }
}

template<typename T>
bool PQ_ComplHeap<T>::is_valid(PQ_ComplHeap::Rank i) {
    return i < complete_bin_heap.size();
}

