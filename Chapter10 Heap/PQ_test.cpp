//
// Created by 王明龙 on 2022/10/24.
//

//堆测试
#include "PQ_ComplHeap.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v{3, 2, 5, 6, 1, 2};
//    v.insert(v.end(), 2);

    PQ_ComplHeap<int> pq(v);
    cout << pq.get_max() << endl;

    vector<int> res;
    pq.heap_sort(res);
    for_each(res.begin(), res.end(), [](int i) { cout << i << " "; });
}




//0010 template <typename PQ, typename T> //堆类型、词条类型
//0011 void  testHeap ( int n ) {
//    0012    T* A = new T[2*n/3]; //创建容量为2*n/3的数组，并
//    0013    for ( int i = 0; i < 2 * n / 3; i++ ) A[i] = dice ( ( T ) 3 * n ); //在其中随机生成2*n/3个词条
//    0014    PQ heap ( A + n / 6, n / 3 ); //批量建堆（PQ_ComplHeap实现了Robert Floyd算法）
//    0015    delete [] A;
//    0016    while ( heap.size() < n ) { //随机测试
//        0017       if ( dice ( 100 ) < 70 ) { //70%概率插入新词条
//            0018          T e = dice ( ( T ) 3 * n );
//            0019          heap.insert ( e );
//            0020       } else { //30%概率摘除最大词条
//            0021          if ( !heap.empty() ) {
//                0022             T e = heap.delMax();
//                0023          }
//            0024       }
//        0025    }
//    0026    while ( !heap.empty() ) { //清空
//        0027       T e = heap.delMax();
//        0028    }
//    0029 }
//0030
//0031 /******************************************************************************************
//0032  * 优先级队列测试
//0033  ******************************************************************************************/
//0034 int main ( int argc, char* argv[] ) {
//    0035    if ( 2 > argc ) { printf ( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
//    0036    srand ( ( unsigned int ) time ( NULL ) );
//    0037    //srand( 1234567 );
//    0038 #if defined(DSA_PQ_LEFTHEAP)
//    0039    testHeap<PQ_LeftHeap<int>, int> ( atoi ( argv[1] ) ); //词条类型可以在这里任意选择
//    0040 #elif defined(DSA_PQ_COMPLHEAP)
//    0041    testHeap<PQ_ComplHeap<int>, int> ( atoi ( argv[1] ) ); //词条类型可以在这里任意选择
//    0042 #elif defined(DSA_PQ_LIST)
//    0043    testHeap<PQ_List<int>, int> ( atoi ( argv[1] ) ); //词条类型可以在这里任意选择
//    0044 #else
//    0045    printf ( "PQ type not defined yet\n" );
//    0046 #endif
//    0047    return 0;
//    0048 }
//
//
