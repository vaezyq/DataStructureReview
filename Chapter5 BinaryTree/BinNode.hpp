#include <stack>
#include <queue>
#include <iostream>
#include <memory>

enum class RBColor {    //�ڵ���ɫ
    RB_RED,
    RB_BLACK
};

template<typename T>
class BinNode;

template<typename T>
using bin_node_ptr = std::shared_ptr<BinNode<T>>;

template<typename T>
class BinNode : public std::enable_shared_from_this<BinNode<T>> {      //�������ڵ�ģ����
public:

    explicit BinNode(const T &data, bin_node_ptr<T> parent = nullptr, bin_node_ptr<T> lChild = nullptr,
                     bin_node_ptr<T> rChild = nullptr, int height = 0, int npl = 1,
                     RBColor color = RBColor::RB_RED) : m_data(data), m_parent(parent),
                                                        m_l_child(lChild),
                                                        m_r_child(rChild),
                                                        m_height(height), m_npl(npl),
                                                        m_color(color) {}           //�ڵ㹹�캯��

    BinNode() : m_data(0), m_parent(nullptr), m_l_child(nullptr), m_r_child(nullptr), m_height(0), m_npl(-1),
                m_color(RBColor::RB_RED) {}          //���캯��

    bin_node_ptr<T> insert_as_lc(T const &e);         //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�

    bin_node_ptr<T> insert_as_rc(T const &e);     //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�

    auto successor();          //ȡ��ǰ�ڵ��ֱ�Ӻ��

    bool operator<(BinNode<T> const &bn) { return m_data < bn.m_data; };     //С��

    bool operator==(BinNode<T> const &bn) { return m_data == bn.m_data; }    //����

    template<class VST>
    void traver_level(VST &visit);         //������α���

    template<class VST>
    static void traver_pre_r(bin_node_ptr<T> x, VST &visit);         //�����������

    template<class VST>
    static void traver_pre_I_S(bin_node_ptr<T> x, VST &visit);      //�������������ʹ��ջģ��ݹ�

    template<class VST>
    static void traver_pre_I_by_ac_func(bin_node_ptr<T> x, VST &visit);        //�������������ͨ����������ʵ�ֵ�������

    template<class VST>
    static void traver_in_r(bin_node_ptr<T> x, VST &visit);         //�ݹ�������������

    template<class VST>
    static void traver_in_I_by_ac_func(bin_node_ptr<T> x, VST &visit);    //�������������ͨ����������ʵ�ֵ�������

    template<class VST>
    static void traver_in_I_by_stack(bin_node_ptr<T> x, VST &visit);         //�������������ͨ��ջģ�⣬������Ҫ��������

    template<class VST>
    static void traver_in_I_by_successor_ac_func(bin_node_ptr<T> x, VST &visit);         //�������������ͨ��successor��̺���ֱ�ӵ���

    template<class VST>
    static void traver_in_I_by_successor_no_back(bin_node_ptr<T> x, VST &visit);       //�������������ͨ��successor�����ǲ�����Ҫ��־λ

    template<class VST>
    static void traver_post_r(bin_node_ptr<T> x, VST &visit);      //�����������

    template<class VST>
    static void traver_post_r_by_ac_func(bin_node_ptr<T> x, VST &visit);

    virtual ~BinNode() = default;   //�����˽ڵ�

private:
    T m_data;     //�ڵ�洢����ֵ
    bin_node_ptr<T> m_parent;    //���׽ڵ�
    bin_node_ptr<T> m_l_child;     //���ӽڵ�
    bin_node_ptr<T> m_r_child;    //�Һ��ӽڵ�
    int m_height;        //�ڵ�ĸ߶�
    int m_npl;        //��ʽ����Ҫʹ�õķǿ�·������(null Path Length)
    RBColor m_color;       //��ɫ(�����)

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
bin_node_ptr<T> BinNode<T>::insert_as_lc(const T &e) {    //��e��Ϊ��ǰ�ڵ�����Ӳ��������
    return this->m_l_child = std::make_shared<BinNode<T>>(BinNode<T>(e, BinNode<T>::shared_from_this()));
}


template<typename T>
bin_node_ptr<T> BinNode<T>::insert_as_rc(const T &e) {     //��e��Ϊ��ǰ�ڵ���Һ��Ӳ���
    return this->m_r_child = std::make_shared<BinNode<T>>(BinNode<T>(e, BinNode<T>::shared_from_this()));
}


template<typename T>
template<class VST>
void BinNode<T>::traver_pre_r(bin_node_ptr<T> x, VST &visit) {    //������ڵ�x�����ʺ���visit
    if (!x) { return; }      // �ݹ�����������
    visit(x->getData());     //���ʽڵ�x
    traver_pre_r(x->getLChild(), visit);      //�ݹ����������
    traver_pre_r(x->getRChild(), visit);      //�ݹ����������
}


template<typename T>
template<class VST>
void BinNode<T>::traver_pre_I_S(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;    //ջ���ڱ��溢�ӽڵ�
    if (x) { S.push(x); }             //�ڵ�ǿ�����ջ
    while (!S.empty()) {            //��ջ�ǿ�ʱ������
        x = S.top(), S.pop();
        visit(x->getData());     //����ջ���ڵ㲢����
        if (x->getRChild()) { S.push(x->getRChild()); }  //�����Һ�������ջ
        if (x->getLChild()) { S.push(x->getLChild()); }   //������������ջ
    }
}

template<class T, class VST>
void visit_along_left_branch(bin_node_ptr<T> x, std::stack<bin_node_ptr<T>> &S, VST &visit) {
    while (x) {
        visit(x->getData());        //��������d
        if (x->getRChild()) {   //������Һ���
            S.push(x->getRChild());     //�Һ�����ջ
        }
        x = x->getLChild();  //��������
    }
}

template<typename T>
template<class VST>
void BinNode<T>::traver_pre_I_by_ac_func(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;     //��¼����ʱ���ڷ��ʵĽڵ�(������ڵ㣬ջ�����ҽڵ�)
    while (true) {
        visit_along_left_branch(x, S, visit);    //���ø�������������ڵ㣬�������ҽڵ�
        if (S.empty()) { break; }        //ջ����ݹ����
        x = S.top(), S.pop();   //����ͷ���,��ջ�м�¼��������ͷ�ڵ�(�����������������)
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
    while (x) {  //���ڵ�x�ǿ�ʱ
        S.push(x);   //����������ջ��
        x = x->getLChild();   //��ͣ����̽��
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
    auto s = BinNode<T>::shared_from_this();       //���ڼ�¼��̵���ʱ����
    if (this->getRChild()) {     //������Һ���,��ֱ�Ӻ�̱�����������
        s = this->getRChild();       //���������ڵ㿪ʼ
        while (s->getLChild()) {      //�����ӣ���ͣ��������
            s = s->getLChild();
        }
    } else {
        while (s->getParent() && s->getParent()->getRChild() == s) {//������������֧����ͣ�س����Ϸ��ƶ�
            s = s->getParent();
        }
        s = s->getParent();     //�ٳ����Ϸ�һ��
    }

    return s;
}

template<typename T>
template<class VST>
void BinNode<T>::traver_in_I_by_successor_ac_func(bin_node_ptr<T> x, VST &visit) {
    bool back_track = false;
    while (true) {
        if ((x->getLChild()) && (!back_track)) {
            x = x->getLChild();   //����������
        } else {
            visit(x->getData());      //���ʱ��ڵ�
            if (x->getRChild()) {   //����������ǿ�
                back_track = false;
                x = x->getRChild();
            } else {   //��������
                if (!(x = x->successor())) {
                    break;      //�Ѿ���������������̽ڵ�Ϊ�գ��˳�����
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
        if (x->getLChild()) {    //������Һ���
            x = x->getLChild();     //�������������
        } else {
            visit(x->getData());
            while (!x->getRChild()) {   //û���Һ���
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
    traver_post_r(x->getLChild());      //�ݹ����������
    traver_post_r(x->getRChild());      //�ݹ����������
    visit(x->getData());       //���ʽڵ�����
}

template<typename T>
void goto_HLVFL(std::stack<bin_node_ptr<T>> &S) {
    while (auto x = S.top()) {             //�����ļ��ջ���ڵ�
        if (x->getLChild()) {     //��������ӣ���������
            if (x->getRChild()) {   //������Һ��ӣ��Һ�����ջ
                S.push(x->getRChild());
            }
            S.push(x->getLChild());   //������ջ
        } else {    //û�����ӣ���������
            S.push(x->getRChild());    //�Һ�����ջ
        }
    }
    S.pop();    //����ջ���Ŀ�Ԫ��
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
    std::queue<bin_node_ptr<T>> Q;       //��������
    Q.push(this);     //���ڵ����
    while (!Q.empty()) {        //���зǿ�
        auto x = Q.front();
        Q.pop();
        visit(x->getData());     //����ͷ�ڵ�Ԫ�ز�����
        if (x->getLChild) {
            Q.push(x->getLChild);   //���м���ǿ�����
        }
        if (x->getLRhild) {
            Q.push(x->getLRhild);    //���м���ǿ��Һ���
        }
    }
}

//BinNode״̬�����ж�
template<typename T>
bool is_root(std::shared_ptr<BinNode<T>> &x) { return !x.getParent(); }   //�ж��Ƿ�Ϊ���ڵ�

template<typename T>
bool is_left_child(std::shared_ptr<BinNode<T>> &x) {      //�ж��Ƿ�Ϊ����
    return !is_root(x) && (x == x.getParent.getLChild());
}

template<typename T>
bool is_right_child(std::shared_ptr<BinNode<T>> &x) {      //�ж��Ƿ�Ϊ�Һ���
    return !is_root(x) && (x == x.getParent.getRChild());
}

template<typename T>
bool has_parent(std::shared_ptr<BinNode<T>> &x) { return !is_root(x); }    //�ж��Ƿ��и��׽ڵ�

template<typename T>
bool has_left_child(std::shared_ptr<BinNode<T>> &x) { return !x.getLChild(); }    //�ж��Ƿ�������

template<typename T>
bool has_right_child(std::shared_ptr<BinNode<T>> &x) { return !x.getRChild(); }   //�ж��Ƿ����Һ���

template<typename T>
bool has_children(std::shared_ptr<BinNode<T>> &x) { return has_left_child(x) || has_right_child(x); } //������һ������

template<typename T>
bool has_both_children(std::shared_ptr<BinNode<T>> &x) { return has_left_child(x) && has_right_child(x); }  //ӵ����������


template<typename T>
bool is_leaf(std::shared_ptr<BinNode<T>> &x) { return !has_right_child(x); }   //�ж��Ƿ�ΪҶ�ӽڵ�

template<typename T>
std::shared_ptr<BinNode<T>> sibling(const std::shared_ptr<BinNode<T>> &x) {  //Ѱ���ֵܽڵ�
    if (is_left_child(x)) {
        return x->getParent.getRChild();
    } else {
        return x->getParent.getLChild();
    }
}

template<typename T>
std::shared_ptr<BinNode<T>> uncle(const std::shared_ptr<BinNode<T>> &x) {    //Ѱ������ڵ�
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






