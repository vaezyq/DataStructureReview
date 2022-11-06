//
// Created by 王明龙 on 2022/10/25.
//

#include "BinTree.hpp"
#include <iostream>

using namespace std;

template<typename T>
void visit(T i) {
    cout << i << " ";
}

int main() {
    // 定义一颗二叉树
    BinTree<char> bt;
    auto root = bt.insert_as_root('a');  //根节点
    auto b = bt.insert_as_lc(root, 'b');
    auto c = bt.insert_as_rc(root, 'c');
    auto d = bt.insert_as_lc(c, 'd');
    auto f = bt.insert_as_rc(c, 'f');
    auto e = bt.insert_as_rc(d, 'e');
    auto g = bt.insert_as_lc(f, 'g');

    cout << "节点c的高度: " << c->getHeight();
    cout << endl;
    cout << "递归版前序遍历结果: ";
    bt.traver_pre(visit<char>, 0);
    cout << endl;
    cout << "栈模拟迭代版前序遍历结果: ";
    bt.traver_pre(visit<char>, 1);
    cout << endl;
    cout << "使用辅助函数与栈实现迭代版前序遍历结果: ";
    bt.traver_pre(visit<char>, 2);

    cout << endl;
    cout << "递归版中序遍历结果: ";
    bt.traver_in(visit<char>, 0);
    cout << endl;
    cout << "通过辅助函数实现迭代版中序遍历结果: ";
    bt.traver_in(visit<char>, 1);
    cout << endl;
    cout << "通过辅助函数(不需要栈)实现迭代版中序遍历结果: ";
    bt.traver_in(visit<char>, 2);
    cout << endl;
    cout << "通过successor辅助函数(不需要栈)实现迭代版中序遍历结果: ";
    bt.traver_in(visit<char>, 3);
    cout << endl;
    cout << "通过successor辅助函数(不需要栈)实现迭代版中序遍历结果(不需要回溯标志): ";
    bt.traver_in(visit<char>, 4);
    cout << endl;
}

