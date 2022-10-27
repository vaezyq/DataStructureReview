
enum class RBColor {    //节点颜色
    RB_RED,
    RB_BLACK
};


template<typename T>
class BinNode {      //二叉树节点模板类
public:
    using bin_node_ptr = BinNode<T> *;

    explicit BinNode(T data, const BinNode<T> *parent = nullptr, const BinNode<T> *lChild = nullptr,
                     const BinNode<T> *rChild = nullptr, int height = 0, int npl = 1,
                     RBColor color = RBColor::RB_RED) : data(data), parent(parent), l_child(lChild), r_child(rChild),
                                                        height(height), npl(npl),
                                                        color(color) {}

    BinNode() : data(0), parent(parent), l_child(nullptr), r_child(nullptr), height(0), npl(-1),
                color(RBColor::RB_RED) {}


    int size();     //统计当前节点的后继总数(以当前节点为根的子树规模)

    bin_node_ptr insert_as_lc(T const &e);         //作为当前节点的左孩子插入新节点

    bin_node_ptr insert_as_rc(T const &e);     //作为当前节点的右孩子插入新节点

    bin_node_ptr succ() const;          //取当前节点的直接后继

    template<class VST>
    void trav_level(VST &visit);         //子树层次遍历


private:
    T data;     //节点存储的数值
    bin_node_ptr parent;    //父亲节点
    bin_node_ptr l_child;     //左孩子节点
    bin_node_ptr r_child;    //右孩子节点
    int height;        //节点的高度
    int npl;        //左式堆需要使用的非空路径长度(null Path Length)
    RBColor color;       //颜色(红黑树)


};

