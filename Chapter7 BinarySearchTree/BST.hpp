#include "../Chapter5 BinaryTree/BinTree.hpp"


template<typename T>
class BST : public BinTree<T> {    //继承于二叉树实现二叉搜索树

public:       //基本接口
    virtual bin_node_ptr<T> &search(const T &e);    //查找

    virtual bin_node_ptr<T> insert(const T &e);    //插入

    virtual std::optional<std::shared_ptr<BinNode<T>>> remove(const T &e);     //删除

protected:
    bin_node_ptr<T> m_hot;    //命中节点的父亲

};

template<typename T>
bin_node_ptr<T> &search_in(bin_node_ptr<T> &v, const T &e, bin_node_ptr<T> &hot) {
    if (!v || v->getData() == e) { return v; }       //抵达递归基
    hot = v;   //记录下父节点
    return search_in(((e < v->getData() ? v->getLChild() : v->getRChild()), e, hot));  //递归到相应的子树查询
}

template<typename T>
bin_node_ptr<T> &BST<T>::search(const T &e) {
    search_in(this->root(), e, this->m_hot);
}

template<typename T>
bin_node_ptr<T> BST<T>::insert(const T &e) {
    auto &x = search(e);
    if (!x) {     //禁止雷同元素插入
        x = std::make_shared<BinNode<T>>({e, this->m_hot});
        this->m_size++;
        this->update_height_above(x);
    }
    return x;
}


template<typename T>
bin_node_ptr<T> remove_at(bin_node_ptr<T> &x, bin_node_ptr<T> &hot) {
    auto w = x, successor = nullptr;
    if (!x->getLChild()) { successor = x->getRChild(); }    //左子树为空
    else if (!x->getRChild()) { successor = x->getLChild(); }    //右子树为空
    else {       //左右子树都非空
        w = w->successor();
        std::swap(x->getData(), w->getData());
        auto u = w->getParent();
        if (w == x) {
            w->getRChild() = successor = w->getRChild();
        } else {
            w->getLChild() = successor = w->getRChild();
        }
    }
}


template<typename T>
std::optional<std::shared_ptr<BinNode<T>>> BST<T>::remove(const T &e) {
    std::optional<T> value;
    auto &x = search(e);
    if (!x) return value;
    value = remove_at(x, m_hot);     //删除节点x
    this->m_size--;      //更新全树规模
    this->update_height_above(m_hot);
    return value;
}
