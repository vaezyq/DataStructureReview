#include <stack>
#include <queue>
#include <iostream>
#include <memory>

enum class RBColor {    //节点颜色
    RB_RED,
    RB_BLACK
};

template<typename T>
class BinNode;

template<typename T>
using bin_node_ptr = std::shared_ptr<BinNode<T>>;

template<typename T>
class BinNode : public std::enable_shared_from_this<BinNode<T>> {      //二叉树节点模板类
public:

    explicit BinNode(const T &data, bin_node_ptr<T> parent = nullptr, bin_node_ptr<T> lChild = nullptr,
                     bin_node_ptr<T> rChild = nullptr, int height = 0, int npl = 1,
                     RBColor color = RBColor::RB_RED) : m_data(data), m_parent(parent),
                                                        m_l_child(lChild),
                                                        m_r_child(rChild),
                                                        m_height(height), m_npl(npl),
                                                        m_color(color) {}           //节点构造函数

    BinNode() : m_data(0), m_parent(nullptr), m_l_child(nullptr), m_r_child(nullptr), m_height(0), m_npl(-1),
                m_color(RBColor::RB_RED) {}          //构造函数

    bin_node_ptr<T> insert_as_lc(T const &e);         //作为当前节点的左孩子插入新节点

    bin_node_ptr<T> insert_as_rc(T const &e);     //作为当前节点的右孩子插入新节点

    auto successor();          //取当前节点的直接后继

    bool operator<(BinNode<T> const &bn) { return m_data < bn.m_data; };     //小于

    bool operator==(BinNode<T> const &bn) { return m_data == bn.m_data; }    //等于

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
    static void traver_in_I_by_successor_ac_func(bin_node_ptr<T> x, VST &visit);         //子树中序遍历，通过successor后继函数直接调用

    template<class VST>
    static void traver_in_I_by_successor_no_back(bin_node_ptr<T> x, VST &visit);       //子树中序遍历，通过successor，但是不再需要标志位

    template<class VST>
    static void traver_post_r(bin_node_ptr<T> x, VST &visit);      //子树后序遍历

    template<class VST>
    static void traver_post_r_by_ac_func(bin_node_ptr<T> x, VST &visit);

    virtual ~BinNode() = default;   //析构此节点

private:
    T m_data;     //节点存储的数值
    bin_node_ptr<T> m_parent;    //父亲节点
    bin_node_ptr<T> m_l_child;     //左孩子节点
    bin_node_ptr<T> m_r_child;    //右孩子节点
    int m_height;        //节点的高度
    int m_npl;        //左式堆需要使用的非空路径长度(null Path Length)
    RBColor m_color;       //颜色(红黑树)

public:
// get and set access interface
    inline T getData() const;

    inline void setData(T data);

    [[nodiscard]] inline int getHeight() const;

    inline void setHeight(int height);

    [[nodiscard]] inline int getNpl() const;

    inline void setNpl(int npl);

    [[nodiscard]]inline RBColor getColor() const;

    inline void setColor(RBColor color);

    inline bin_node_ptr<T> getParent() const;

    inline void setParent(bin_node_ptr<T> parent);

    inline bin_node_ptr<T> getLChild() const;

    inline void setLChild(bin_node_ptr<T> lChild);

    inline bin_node_ptr<T> getRChild() const;

    inline void setRChild(bin_node_ptr<T> rChild);
};

template<typename T>
T BinNode<T>::getData() const {
    return m_data;
}

template<typename T>
void BinNode<T>::setData(T data) {
    this->m_data = data;
}

template<typename T>
int BinNode<T>::getHeight() const {
    return m_height;
}

template<typename T>
void BinNode<T>::setHeight(int height) {
    this->m_height = height;
}

template<typename T>
int BinNode<T>::getNpl() const {
    return m_npl;
}

template<typename T>
void BinNode<T>::setNpl(int npl) {
    this->m_npl = npl;
}

template<typename T>
RBColor BinNode<T>::getColor() const {
    return m_color;
}

template<typename T>
void BinNode<T>::setColor(RBColor color) {
    this->m_color = color;
}

template<typename T>
bin_node_ptr<T> BinNode<T>::getParent() const {
    return m_parent;
}

template<typename T>
void BinNode<T>::setParent(bin_node_ptr<T> parent) {
    this->m_parent = parent;
}

template<typename T>
bin_node_ptr<T> BinNode<T>::getLChild() const {
    return m_l_child;
}

template<typename T>
void BinNode<T>::setLChild(bin_node_ptr<T> lChild) {
    this->m_l_child = lChild;
}

template<typename T>
bin_node_ptr<T> BinNode<T>::getRChild() const {
    return m_r_child;
}

template<typename T>
void BinNode<T>::setRChild(bin_node_ptr<T> rChild) {
    this->m_r_child = rChild;
}


template<typename T>
bin_node_ptr<T> BinNode<T>::insert_as_lc(const T &e) {    //将e作为当前节点的左孩子插入二叉树
    return this->m_l_child = std::make_shared<BinNode<T>>(BinNode<T>(e, BinNode<T>::shared_from_this()));
}


template<typename T>
bin_node_ptr<T> BinNode<T>::insert_as_rc(const T &e) {     //将e作为当前节点的右孩子插入
    return this->m_r_child = std::make_shared<BinNode<T>>(BinNode<T>(e, BinNode<T>::shared_from_this()));
}


template<typename T>
template<class VST>
void BinNode<T>::traver_pre_r(bin_node_ptr<T> x, VST &visit) {    //传入根节点x、访问函数visit
    if (!x) { return; }      // 递归基：传入空树
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
        visit(x->getData());     //弹出栈顶节点并访问
        if (x->getRChild()) { S.push(x->getRChild()); }  //若有右孩子则入栈
        if (x->getLChild()) { S.push(x->getLChild()); }   //若有左孩子则入栈
    }
}

template<class T, class VST>
void visit_along_left_branch(bin_node_ptr<T> x, std::stack<bin_node_ptr<T>> &S, VST &visit) {
    while (x) {
        visit(x->getData());        //访问数据d
        if (x->getRChild()) {   //如果有右孩子
            S.push(x->getRChild());     //右孩子入栈
        }
        x = x->getLChild();  //不断向左
    }
}

template<typename T>
template<class VST>
void BinNode<T>::traver_pre_I_by_ac_func(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;     //记录回溯时用于访问的节点(访问左节点，栈存入右节点)
    while (true) {
        visit_along_left_branch(x, S, visit);    //调用辅助函数访问左节点，并存入右节点
        if (S.empty()) { break; }        //栈空则递归结束
        x = S.top(), S.pop();   //弹出头结点,即栈中记录的右子树头节点(用于深入访问右子树)
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
        if (S.empty()) { break; }
        x = S.top(), S.pop();
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

template<typename T>
auto BinNode<T>::successor() {
//    const int *const p = new int;
//    auto s = std::make_shared<bin_node_ptr<T>>(const_cast<bin_node_ptr<T>>(BinNode<T>::shared_from_this().get()));
//    auto s = this;
    auto s = BinNode<T>::shared_from_this();       //用于记录后继的临时变量
    if (this->getRChild()) {     //如果有右孩子,则直接后继必在右子树中
        s = this->getRChild();       //从右子树节点开始
        while (s->getLChild()) {      //有左孩子，则不停的向左走
            s = s->getLChild();
        }
    } else {
        while (s->getParent() && s->getParent()->getRChild() == s) {//逆向地沿右向分支，不停地朝左上方移动
            s = s->getParent();
        }
        s = s->getParent();     //再朝右上方一步
    }

    return s;
}

template<typename T>
template<class VST>
void BinNode<T>::traver_in_I_by_successor_ac_func(bin_node_ptr<T> x, VST &visit) {
    bool back_track = false;
    while (true) {
        if ((x->getLChild()) && (!back_track)) {
            x = x->getLChild();   //深入左子树
        } else {
            visit(x->getData());      //访问本节点
            if (x->getRChild()) {   //如果右子树非空
                back_track = false;
                x = x->getRChild();
            } else {   //右子树空
                if (!(x = x->successor())) {
                    break;      //已经访问完树根，后继节点为空，退出遍历
                }
                back_track = true;
            }
        }
    }
}

template<typename T>
template<class VST>
void BinNode<T>::traver_in_I_by_successor_no_back(bin_node_ptr<T> x, VST &visit) {
    while (true) {
        if (x->getLChild()) {    //如果有右孩子
            x = x->getLChild();     //深入遍历左子树
        } else {
            visit(x->getData());
            while (!x->getRChild()) {   //没有右孩子
                if (!(x = x->successor())) {
                    return;
                } else {
                    visit(x->getData());
                }
            }
            x = x->getRChild();
        }
    }
}

template<typename T>
template<class VST>
void BinNode<T>::traver_post_r(bin_node_ptr<T> x, VST &visit) {
    if (!x) { return; }
    traver_post_r(x->getLChild());      //递归访问左子树
    traver_post_r(x->getRChild());      //递归访问右子树
    visit(x->getData());       //访问节点数据
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

template<typename T>
template<class VST>
void BinNode<T>::traver_post_r_by_ac_func(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;
    if (x) { S.push(x); }
    while (!S.empty()) {
        if (S.top() != x->parent) {
            go_along_left_branch(S);
        }
        x = S.top(), S.pop();
        visit(x->data);
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

//BinNode状态性质判断
template<typename T>
bool is_root(std::shared_ptr<BinNode<T>> &x) { return !x.getParent(); }   //判断是否为根节点

template<typename T>
bool is_left_child(std::shared_ptr<BinNode<T>> &x) {      //判断是否为左孩子
    return !is_root(x) && (x == x.getParent.getLChild());
}

template<typename T>
bool is_right_child(std::shared_ptr<BinNode<T>> &x) {      //判断是否为右孩子
    return !is_root(x) && (x == x.getParent.getRChild());
}

template<typename T>
bool has_parent(std::shared_ptr<BinNode<T>> &x) { return !is_root(x); }    //判断是否有父亲节点

template<typename T>
bool has_left_child(std::shared_ptr<BinNode<T>> &x) { return !x.getLChild(); }    //判断是否有左孩子

template<typename T>
bool has_right_child(std::shared_ptr<BinNode<T>> &x) { return !x.getRChild(); }   //判断是否有右孩子

template<typename T>
bool has_children(std::shared_ptr<BinNode<T>> &x) { return has_left_child(x) || has_right_child(x); } //至少有一个孩子

template<typename T>
bool has_both_children(std::shared_ptr<BinNode<T>> &x) { return has_left_child(x) && has_right_child(x); }  //拥有两个孩子


template<typename T>
bool is_leaf(std::shared_ptr<BinNode<T>> &x) { return !has_right_child(x); }   //判断是否为叶子节点

template<typename T>
std::shared_ptr<BinNode<T>> sibling(const std::shared_ptr<BinNode<T>> &x) {  //寻找兄弟节点
    if (is_left_child(x)) {
        return x->getParent.getRChild();
    } else {
        return x->getParent.getLChild();
    }
}

template<typename T>
std::shared_ptr<BinNode<T>> uncle(const std::shared_ptr<BinNode<T>> &x) {    //寻找叔叔节点
    return sibling(x.getParent);
}

template<typename T>
void set_parent_child(std::shared_ptr<BinNode<T>> &x, const std::shared_ptr<BinNode<T>> &res) {
    if (is_root(x)) {
        x = res;
    } else {
        if (is_left_child(x)) { x->setLChild(res); }
        else { x->setRChild(res); }
    };
}






