
#include <stack>
#include <queue>
#include <iostream>

enum class RBColor {    //节点颜色
    RB_RED,
    RB_BLACK
};

template<typename T>
class BinNode;

template<typename T>
using bin_node_ptr = BinNode<T> *;

template<typename T>
class BinNode {      //二叉树节点模板类
public:

    explicit BinNode(const T &data, bin_node_ptr<T> parent = nullptr, bin_node_ptr<T> lChild = nullptr,
                     bin_node_ptr<T> rChild = nullptr, int height = 0, int npl = 1,
                     RBColor color = RBColor::RB_RED) : data(data), parent(parent), l_child(lChild), r_child(rChild),
                                                        height(height), npl(npl),
                                                        color(color) {}           //节点构造函数

    BinNode() : data(0), parent(parent), l_child(nullptr), r_child(nullptr), height(0), npl(-1),
                color(RBColor::RB_RED) {}          //构造函数

    bin_node_ptr<T> insert_as_lc(T const &e);         //作为当前节点的左孩子插入新节点

    bin_node_ptr<T> insert_as_rc(T const &e);     //作为当前节点的右孩子插入新节点

    bin_node_ptr<T> successor() const;          //取当前节点的直接后继

    bool operator<(BinNode<T> const &bn) { return data < bn.data; };     //小于

    bool operator==(BinNode<T> const &bn) { return data == bn.data; }    //等于

    static int get_height(bin_node_ptr<T> bn) { return (bn) ? bn->height : -1; }

    T getData() const;

    void setData(T data);

    int getHeight() const;

    void setHeight(int height);

    int getNpl() const;

    void setNpl(int npl);

    RBColor getColor() const;

    void setColor(RBColor color);

    bin_node_ptr<T> getParent() const;

    void setParent(bin_node_ptr<T> parent);

    bin_node_ptr<T> getLChild() const;

    void setLChild(bin_node_ptr<T> lChild);

    bin_node_ptr<T> getRChild() const;

    void setRChild(bin_node_ptr<T> rChild);

    template<class VST>
    void traver_level(VST &visit);         //子树层次遍历

    template<class VST>
    static void traver_pre_r(bin_node_ptr<T> x, VST &visit);         //子树先序遍历

    template<class VST>
    static void traver_pre_I_S(bin_node_ptr<T> x, VST &visit);      //子树先序遍历：使用栈模拟递归

    template<class VST>
    static void traver_pre_I_by_ac_func(bin_node_ptr<T> x, VST &visit);        //子树先序遍历，通过辅助函数实现迭代访问

    template<class VST>
    static void traver_in_r(bin_node_ptr<T> x, VST &visit);         //递归版子树中序遍历

    template<class VST>
    static void traver_in_I_by_ac_func(bin_node_ptr<T> x, VST &visit);    //子树中序遍历，通过辅助函数实现迭代访问

    template<class VST>
    static void traver_in_I_by_stack(bin_node_ptr<T> x, VST &visit);         //子树中序遍历，通过栈模拟，不在需要辅助函数

    template<class VST>
    void traver_post(VST &visit);      //子树后序遍历


private:
    T data;     //节点存储的数值
    bin_node_ptr<T> parent;    //父亲节点
    bin_node_ptr<T> l_child;     //左孩子节点
    bin_node_ptr<T> r_child;    //右孩子节点
    int height;        //节点的高度
    int npl;        //左式堆需要使用的非空路径长度(null Path Length)
    RBColor color;       //颜色(红黑树)
};


template<typename T>
bin_node_ptr<T> BinNode<T>::insert_as_lc(const T &e) {    //将e作为当前节点的左孩子插入二叉树

    return this->l_child = new BinNode<T>(e, this);
}


template<typename T>
bin_node_ptr<T> BinNode<T>::insert_as_rc(const T &e) {     //将e作为当前节点的右孩子插入
    return this->r_child = new BinNode<T>(e, this);
}

template<typename T>
T BinNode<T>::getData() const {
    return data;
}

template<typename T>
void BinNode<T>::setData(T data) {
    BinNode::data = data;
}

template<typename T>
int BinNode<T>::getHeight() const {
    return height;
}

template<typename T>
void BinNode<T>::setHeight(int height) {
    BinNode::height = height;
}

template<typename T>
int BinNode<T>::getNpl() const {
    return npl;
}

template<typename T>
void BinNode<T>::setNpl(int npl) {
    BinNode::npl = npl;
}

template<typename T>
RBColor BinNode<T>::getColor() const {
    return color;
}

template<typename T>
void BinNode<T>::setColor(RBColor color) {
    BinNode::color = color;
}


template<typename T>
template<class VST>
void BinNode<T>::traver_pre_r(bin_node_ptr<T> x, VST &visit) {    //传入根节点x、访问函数visit
    if (!x) {          // 递归基：传入空树
        return;
    }
    visit(x->getData());     //访问节点x
    traver_pre_r(x->getLChild(), visit);      //递归访问左子树
    traver_pre_r(x->getRChild(), visit);      //递归访问右子树
}


template<typename T>
template<class VST>
void BinNode<T>::traver_pre_I_S(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;    //栈用于保存孩子节点
    if (x) { S.push(x); }             //节点非空则入栈
    while (!S.empty()) {            //当栈非空时反复的
        x = S.top(), S.pop();
        visit(x->getData());     //弹出头节点并访问
        if (x->getRChild()) { S.push(x->getRChild()); }  //若有右孩子则入栈
        if (x->getLChild()) { S.push(x->getLChild()); }   //若有左孩子则入栈
    }
}

template<typename T, typename VST>
void traver_in_r(bin_node_ptr<T> x, VST &visit) {     //传入根节点与访问函数
    if (!x) { return; }      //递归基：抵达空节点
    traver_R(x->getLChild(), visit);    //递归访问左子树
    visit(x);       //访问节点x
    traver_R(x->getRChild(), visit);    //递归访问右子树
}


template<typename T, typename VST>
[[noreturn]]
void traver_in_v2(bin_node_ptr<T> x, VST &visit) {    //传入根节点与访问函数
    std::stack<bin_node_ptr<T>> S;
    while (true) {
        if (x) { //没有抵达空节点
            S.push(x);   //将左侧藤节点都压如栈中
            x = x->getLChild();     //继续向左探索
        } else if (!S.empty()) {
            x = S.top(), visit(x->getData());  //弹出栈并访问数据
            x = x->getRChild();    //转入右孩子访问
        } else {
            break;    //遍历完成
        }
    }
}

template<typename T>
bin_node_ptr<T> BinNode<T>::successor() const {
    auto s = this;     //用于记录后继的临时变量
    if (this->getRChild()) {     //如果有右孩子,则直接后继必在右子树中
        s = this->getLChild();       //从右子树节点开始
        while (s->getLChild())  {      //有左孩子，则不停的向左走
            s = s->getLChild();
        }
    }
}

template<typename T>
template<class VST>
void BinNode<T>::traver_level(VST &visit) {
    std::queue<bin_node_ptr<T>> Q;       //辅助队列
    Q.push(this);     //根节点入队

    while (!Q.empty()) {        //队列非空
        auto x = Q.front();
        Q.pop();
        visit(x->getData());     //弹出头节点元素并访问
        if (x->getLChild) {
            Q.push(x->getLChild);   //队列加入非空左孩子
        }
        if (x->getLRhild) {
            Q.push(x->getLRhild);    //队列加入非空右孩子
        }
    }
}


template<typename T, typename VST>
[[noreturn]]
void traver_in_v3(bin_node_ptr<T> x, VST &visit) {    //传入根节点与访问函数
    bool back_track = false;      //前一步是否为回溯：即从右子树回溯回来
    while (true) {
        if ((!back_track) && (x->getLChild())) {    //不是回溯且有左孩子
            x = x->getLChild();  //不停向左侧探索
        } else {         //没有左子树或者刚刚已经回溯
            visit(x->getData());        //访问该节点
            if (x->getRChild()) {  //有右孩子
                x = x->getRChild();        //深入右子树遍历
                back_track = false;
            } else {
                if (!(x = x->succ())) {
                    break;
                }
                back_track = true;
            }
        }
    }
}


template<typename T, typename VST>
void traver_post_r(bin_node_ptr<T> x, VST &visit) {
    if (!x) { return; }
    traver_R(x->getLChild(), visit);
    traver_R(x->getRChild(), visit);
    visit(x);
}

template<typename T>
void goto_HLVFL(std::stack<bin_node_ptr<T>> &S) {
    while (auto x = S.top()) {             //反复的检查栈顶节点
        if (x->getLChild()) {     //如果有左孩子，则向左走
            if (x->getRChild()) {   //如果有右孩子，右孩子入栈
                S.push(x->getRChild());
            }
            S.push(x->getLChild());   //左孩子入栈
        } else {    //没有左孩子，才向右走
            S.push(x->getRChild());    //右孩子入栈
        }
    }
    S.pop();    //弹出栈顶的空元素
}

template<typename T, typename VST>
void traver_post_v(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;
    S.push(x);     //跟节点入栈
    while (!S.empty()) {
        if (S.top() != x->getParent()) {     //栈顶不是当前节点的父节点，则说明栈顶一定是其右兄弟子树
            goto_HLVFL(S);     //对右兄弟子树执行遍历
        }
        x = S.top();
        S.pop();
        visit(x->getData());      //弹出栈顶数据并访问
    }
}


template<typename T>
bin_node_ptr<T> BinNode<T>::getParent() const {
    return parent;
}

template<typename T>
void BinNode<T>::setParent(bin_node_ptr<T> parent) {
    BinNode::parent = parent;
}

template<typename T>
bin_node_ptr<T> BinNode<T>::getLChild() const {
    return l_child;
}

template<typename T>
void BinNode<T>::setLChild(bin_node_ptr<T> lChild) {
    l_child = lChild;
}

template<typename T>
bin_node_ptr<T> BinNode<T>::getRChild() const {
    return r_child;
}

template<typename T>
void BinNode<T>::setRChild(bin_node_ptr<T> rChild) {
    r_child = rChild;
}

template<class T, class VST>
void visit_along_left_branch(bin_node_ptr<T> x, std::stack<bin_node_ptr<T>> &S, VST &visit) {
    while (x) {
        visit(x->getData());        //访问数据
        if (x->getRChild()) {   //如果有右孩子
            S.push(x->getRChild());     //右孩子入栈
        }
        x = x->getLChild();  //不断向左
    }
}

template<typename T>
template<class VST>
void BinNode<T>::traver_pre_I_by_ac_func(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;
    while (true) {
        visit_along_left_branch(x, S, visit);
        if (S.empty()) {
            break;
        }
        x = S.top(), S.pop();   //弹出头结点，即最后未右子树 树根结点
    }
}

template<typename T>
template<class VST>
void BinNode<T>::traver_in_r(bin_node_ptr<T> x, VST &visit) {
    if (!x) { return; }
    traver_in_r(x->getLChild(), visit);
    visit(x->getData());
    traver_in_r(x->getRChild(), visit);
}

template<typename T>
void go_along_left_branch(bin_node_ptr<T> x, std::stack<bin_node_ptr<T>> &S) {
    while (x) {  //当节点x非空时
        S.push(x);   //将左孩子推入栈中
        x = x->getLChild();   //不停向左探索
    }
}


template<typename T>
template<class VST>
void BinNode<T>::traver_in_I_by_ac_func(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;
    while (true) {
        go_along_left_branch(x, S);
        if (S.empty()) { break; };
        x = S.top();
        S.pop();
        visit(x->getData());
        x = x->getRChild();
    }
}

template<typename T>
template<class VST>
void BinNode<T>::traver_in_I_by_stack(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;
    while (true) {
        if (x) {
            S.push(x);
            x = x->getLChild();
        } else if (!S.empty()) {
            x = S.top(), S.pop();
            visit(x->getData());
            x = x->getRChild();
        } else {
            break;
        }
    }
}



