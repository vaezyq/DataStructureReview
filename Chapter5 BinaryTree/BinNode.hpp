
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

    explicit BinNode(T data, const BinNode<T> *parent = nullptr, const BinNode<T> *lChild = nullptr,
                     const BinNode<T> *rChild = nullptr, int height = 0, int npl = 1,
                     RBColor color = RBColor::RB_RED) : data(data), parent(parent), l_child(lChild), r_child(rChild),
                                                        height(height), npl(npl),
                                                        color(color) {}

    BinNode() : data(0), parent(parent), l_child(nullptr), r_child(nullptr), height(0), npl(-1),
                color(RBColor::RB_RED) {}


    int size();     //统计当前节点的后继总数(以当前节点为根的子树规模)

    bin_node_ptr<T> insert_as_lc(T const &e);         //作为当前节点的左孩子插入新节点

    bin_node_ptr<T> insert_as_rc(T const &e);     //作为当前节点的右孩子插入新节点

    bin_node_ptr<T> succ() const;          //取当前节点的直接后继

    template<class VST>
    void traver_level(VST &visit);         //子树层次遍历

    template<class VST>
    void traver_pre(VST &visit);         //子树先序遍历

    template<class VST>
    void traver_in(VST &visit);         //子树中序遍历

    template<class VST>
    void traver_post(VST &visit);      //子树后序遍历

    bool operator<(BinNode<T> const &bn) { return data < bn.data; };     //小于

    bool operator==(BinNode<T> const &bn) { return data == bn.data; }    //等于

    static int get_height(bin_node_ptr<T> const &bn) { return (bn) ? bn->height : -1; }

    T getData() const;

    void setData(T data);

    const BinNode<T> *getParent() const;

    void setParent(const BinNode<T> *parent);

    const BinNode<T> *getLChild() const;

    void setLChild(const BinNode<T> *lChild);

    const BinNode<T> *getRChild() const;

    void setRChild(const BinNode<T> *rChild);

    int getHeight() const;

    void setHeight(int height);

    int getNpl() const;

    void setNpl(int npl);

    RBColor getColor() const;

    void setColor(RBColor color);


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
const BinNode<T> *BinNode<T>::getParent() const {
    return parent;
}

template<typename T>
void BinNode<T>::setParent(const BinNode<T> *parent) {
    BinNode::parent = parent;
}

template<typename T>
const BinNode<T> *BinNode<T>::getLChild() const {
    return l_child;
}

template<typename T>
void BinNode<T>::setLChild(const BinNode<T> *lChild) {
    l_child = lChild;
}

template<typename T>
const BinNode<T> *BinNode<T>::getRChild() const {
    return r_child;
}

template<typename T>
void BinNode<T>::setRChild(const BinNode<T> *rChild) {
    r_child = rChild;
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
void BinNode<T>::traver_pre(VST &visit) {
}

template<typename T, typename VST>
void traver_pre_r(bin_node_ptr<T> x, VST &visit) {
    if (!x) {
        return;
    }
    visit(x);
    traver_R(x->getLChild(), visit);
    traver_R(x->getRChild(), visit);
}

template<typename T, typename VST>
void traver_in_r(bin_node_ptr<T> x, VST &visit) {
    if (!x) {
        return;
    }
    traver_R(x->getLChild(), visit);
    visit(x);
    traver_R(x->getRChild(), visit);
}

template<typename T, typename VST>
void traver_post_r(bin_node_ptr<T> x, VST &visit) {
    if (!x) {
        return;
    }
    traver_R(x->getLChild(), visit);
    traver_R(x->getRChild(), visit);
    visit(x);
}




