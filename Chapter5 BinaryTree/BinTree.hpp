#include <algorithm>
#include "BinNode.hpp"

template<typename T>
class BinTree {
protected:
    int m_size;        //树的规模
    bin_node_ptr<T> m_root;    //树根节点
    virtual int update_height(bin_node_ptr<T> &x);    //更新节点x的高度

    void update_height_above(bin_node_ptr<T> x);     //更新节点x及其祖先的高度

public:
    BinTree() : m_size(0), m_root(nullptr) {}    //默认构造函数

    ~BinTree() { if (0 < m_size) { remove(m_root); }}      //析构函数

    [[nodiscard]]
    int size() const { return m_size; }        //返回规模

    [[nodiscard]]
    bool empty() const { return !m_root; }      //判断树是否空

    bin_node_ptr<T> root() { return m_root; }  //返回树根节点

    bin_node_ptr<T> insert_as_root(T const &e);   //作为根节点插入

    bin_node_ptr<T> insert_as_lc(bin_node_ptr<T> &x, T const &e);  //e作为x的左孩子插入(原先x无左孩子)

    bin_node_ptr<T> insert_as_rc(bin_node_ptr<T> &x, T const &e);  //e作为x的右孩子插入(原先x无右孩子)

    bin_node_ptr<T> attach_as_lc(bin_node_ptr<T> &x, BinTree<T> *bt);     //bt作为x的左子树接入

    bin_node_ptr<T> attach_as_rc(bin_node_ptr<T> &x, BinTree<T> *bt);     //bt作为x的右子树接入

    int remove(bin_node_ptr<T> &x);       //删除以节点x为根的子树，并返回子树规模

    static int remove_at(bin_node_ptr<T> x);      //删除二叉树中位置为x的节点及其后代，返回被删除的节点数值

    BinTree<T> *secede(bin_node_ptr<T> &x);      //将子树x从当前树中摘除，将其转化为一颗独立树

    template<class VST>
    void traver_level(VST &visit) {
        if (m_root) { m_root->traver_level(visit); }
    }

    template<class VST>
    void traver_pre(VST &visit, int flag) {
        if (m_root) {
            switch (flag) {
                case 0:
                    BinNode<T>::traver_pre_r(m_root, visit);     //使用默认版本的递归遍历
                    break;
                case 1:
                    BinNode<T>::traver_pre_I_S(m_root, visit);   //使用尾递归模
                    break;
                case 2:
                default:
                    BinNode<T>::traver_pre_I_by_ac_func(m_root, visit);   //使用辅助函数实现前序遍历
                    break;
            }
        }
    }

    template<class VST>
    void traver_in(VST &visit, int flag) {
        if (m_root) {
            switch (flag) {
                case 0:
                default:
                    BinNode<T>::traver_in_r(m_root, visit);      //递归版中序遍历
                    break;
                case 1:
                    BinNode<T>::traver_in_I_by_ac_func(m_root, visit);    //通过辅助函数与栈实现迭代版中序遍历
                    break;
                case 2:
                    BinNode<T>::traver_in_I_by_stack(m_root, visit);
                    break;
                case 3:
                    BinNode<T>::traver_in_I_by_successor_ac_func(m_root, visit);     //通过后继辅助函数实现迭代版中序遍历
                    break;
                case 4:
                    BinNode<T>::traver_in_I_by_successor_no_back(m_root, visit); //通过后继辅助函数访问，不再需要回溯标志
            }
        }
    }

    template<class VST>
    void traver_post(VST &visit) {
        if (m_root) { m_root->traver_post(visit); }
    }

    bool operator==(BinTree<T> &bt) {
        return m_root && bt->m_root && (m_root == bt.m_root);
    }

//    static BinTree<T> construct_bin_tree_by_pre_in(std::vector<T> pre, std::vector<T> in);

};

template<typename T>
int BinTree<T>::update_height(bin_node_ptr<T> &x) {
    auto height{0};
    if (x->getLChild()) { height = std::max(height, x->getLChild()->getHeight()); }
    if (x->getRChild()) { height = std::max(height, x->getRChild()->getHeight()); }
    x->setHeight(height);
    return height;
}

template<typename T>
void BinTree<T>::update_height_above(bin_node_ptr<T> x) {
    while (x) {
        update_height(x);
        x = x->getParent();
    }
}

template<typename T>
bin_node_ptr<T> BinTree<T>::insert_as_root(const T &e) {
    m_size = 1;
    return m_root = std::make_shared<BinNode<T>>(e);   //将e作为根节点插入空的二叉树
}


template<typename T>
bin_node_ptr<T> BinTree<T>::insert_as_lc(bin_node_ptr<T> &x, const T &e) {
    m_size++;
    x->insert_as_lc(e);
    update_height_above(x);
    return x->getLChild();
}

template<typename T>
bin_node_ptr<T> BinTree<T>::insert_as_rc(bin_node_ptr<T> &x, const T &e) {
    m_size++;
    x->insert_as_rc(e);
    update_height_above(x);
    return x->getRChild();
}

template<typename T>
bin_node_ptr<T> BinTree<T>::attach_as_lc(bin_node_ptr<T> &x, BinTree<T> *bt) {
    if (bt->m_root) {
        x->setLChild(bt->m_root);
        x->getLChild()->setParent(x);  //将bt根节点接入x左子树
    }
    m_size += bt->m_size;     //更新规模
    update_height_above(x);   //更新高度
    bt->m_root = nullptr;
    bt->m_size = 0;
    bt = nullptr;    //释放原树
    return x;
}

template<typename T>
bin_node_ptr<T> BinTree<T>::attach_as_rc(bin_node_ptr<T> &x, BinTree<T> *bt) {
    if (bt->root()) {
        x->setRChild(bt->root());
        x->getRChild()->setParent(x);    //将bt根节点接入x右子树
    }
    m_size += bt->size();      //更新规模
    update_height_above(x);    //更新高度
    bt->m_root = nullptr;
    bt->m_size = 0;
    bt = nullptr;    //释放原树
    return x;
}


template<typename T>
int BinTree<T>::remove_at(bin_node_ptr<T> x) {
    if (!x) {    //抵达递归基
        return 0;
    }
    int n = remove_at(x->getLChild()) + remove_at(x->getRChild());    //递归释放左右子树
    return n;
}

template<typename T>
int BinTree<T>::remove(bin_node_ptr<T> &x) {
    if (x != m_root) {
        if (x->getParent()->getLChild() == x) {
            x->getParent()->setLChild(nullptr);
        } else {
            x->getParent()->setRChild(nullptr);
        }
    }
    update_height_above(x->getParent());
    int n = remove_at(x);
    m_size -= n;
    return n;
}

template<typename T>
BinTree<T> *BinTree<T>::secede(bin_node_ptr<T> &x) {
    if (x != m_root) {
        if (x->getParent()->getLChild() == x) {
            x->getParent()->setLChild(nullptr);
        } else {
            x->getParent()->setRChild(nullptr);
        }
    }
    update_height_above(x->getParent());
    auto S = new BinTree<T>;
    S->m_root = x;
    x->setParent(nullptr);
    S->m_size = x->size();
    m_size -= S->m_size;
    return S;
}

//template<typename T>
//BinTree<T>
//BinTree<T>::construct_bin_tree_by_pre_in(std::vector<T> pre, std::vector<T> in, int start, int mid, int end) {
//    if (start > end) { return; }
//    auto head= std::make_shared<BinNode<T>>(mid);
//    auto left= construct_bin_tree_by_pre_in()
//
//
//
//}














