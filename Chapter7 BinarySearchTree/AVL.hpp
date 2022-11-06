#include "BST.hpp"

template<typename T>
class AVL : public BST<T> {
public:
    virtual bin_node_ptr<T> insert(const T &e);    //插入

    virtual std::optional<std::shared_ptr<BinNode<T>>> remove(const T &e);     //删除

    bin_node_ptr<T>
    connect34(bin_node_ptr<T>, bin_node_ptr<T>, bin_node_ptr<T>, bin_node_ptr<T>, bin_node_ptr<T>, bin_node_ptr<T>,
              bin_node_ptr<T>);         //3+4重构算法

    bin_node_ptr<T> rotate_at(bin_node_ptr<T> &x);     //对节点x及其父亲节点、祖父节点重构

};

template<class T>
int get_height(std::shared_ptr<BinNode<T>> x) {
    if (!x) { return -1; }
    return x->getHeight();
}

template<class T>
bool balanced(const std::shared_ptr<BinNode<T>> &x) {        //判断是否理想平衡
    return get_height(x->getLChild()) == get_height(x->getRChild());
}

template<class T>
int bal_fac(const std::shared_ptr<BinNode<T>> &x) {      //平衡因子
    return get_height(x->getLChild()) - get_height(x->getRChild());
}

template<class T>
int avl_balanced(const std::shared_ptr<BinNode<T>> &x) {
    return ((-2 < bal_fac(x)) && (bal_fac(x) < 2));
}

template<class T>
std::shared_ptr<BinNode<T>> taller_child(const std::shared_ptr<BinNode<T>> &x) {
    if (get_height(x->getLChild()) > get_height(x.getRChild())) {
        return x->getLChild();
    } else if (get_height(x.getRChild()) < get_height(x.getLChild())) {
        return x.getRChild();
    } else {
        if (x->getParent().getLChild() == x) {
            return x.getLChild();
        } else {
            return x.getRChild();
        }
    }
}

template<typename T>
bin_node_ptr<T> AVL<T>::insert(const T &e) {
    auto &x = search(e);      //查找目标节点
    if (x) { return x; }     //目标节点已经存在
    auto xx = x = std::make_shared<BinNode<T>>({e, this->m_hot});
    for (auto g = this->m_hot; g; g = g->getParent()) {
        if (!avl_balanced(x)) {    //一旦发现失衡

        }
    }
}

template<typename T>
bin_node_ptr<T>
AVL<T>::connect34(bin_node_ptr<T> a, bin_node_ptr<T> b, bin_node_ptr<T> c, bin_node_ptr<T> t, bin_node_ptr<T> t2,
                  bin_node_ptr<T> t3,
                  bin_node_ptr<T> t4) {
    a->setLChild(t);
    if (t) { t.setParent(a); }
    a.setRChild(t2);
    if (t2) { t2.setParent(a); }
    c.setLChild(t3);
    if (t3) { t3.setParent(c); }
    c.setRChild(t4);
    if (t4) { t4.setParent(c); }
    b.setLChild(a), a.setParent(b), b.setRChild(c), c.setParent(b);
    this->update_height(a), this->update_height(b), this->update_height(c);
    return b;
}

template<typename T>
bin_node_ptr<T> AVL<T>::rotate_at(bin_node_ptr<T> &x) {

}
