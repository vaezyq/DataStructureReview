
#include <stack>
#include <queue>
#include <iostream>

enum class RBColor {    //�ڵ���ɫ
    RB_RED,
    RB_BLACK
};

template<typename T>
class BinNode;

template<typename T>
using bin_node_ptr = BinNode<T> *;

template<typename T>
class BinNode {      //�������ڵ�ģ����
public:

    explicit BinNode(const T &data, bin_node_ptr<T> parent = nullptr, bin_node_ptr<T> lChild = nullptr,
                     bin_node_ptr<T> rChild = nullptr, int height = 0, int npl = 1,
                     RBColor color = RBColor::RB_RED) : data(data), parent(parent), l_child(lChild), r_child(rChild),
                                                        height(height), npl(npl),
                                                        color(color) {}           //�ڵ㹹�캯��

    BinNode() : data(0), parent(parent), l_child(nullptr), r_child(nullptr), height(0), npl(-1),
                color(RBColor::RB_RED) {}          //���캯��

    bin_node_ptr<T> insert_as_lc(T const &e);         //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�

    bin_node_ptr<T> insert_as_rc(T const &e);     //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�

    bin_node_ptr<T> successor() const;          //ȡ��ǰ�ڵ��ֱ�Ӻ��

    bool operator<(BinNode<T> const &bn) { return data < bn.data; };     //С��

    bool operator==(BinNode<T> const &bn) { return data == bn.data; }    //����

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
    void traver_post(VST &visit);      //�����������


private:
    T data;     //�ڵ�洢����ֵ
    bin_node_ptr<T> parent;    //���׽ڵ�
    bin_node_ptr<T> l_child;     //���ӽڵ�
    bin_node_ptr<T> r_child;    //�Һ��ӽڵ�
    int height;        //�ڵ�ĸ߶�
    int npl;        //��ʽ����Ҫʹ�õķǿ�·������(null Path Length)
    RBColor color;       //��ɫ(�����)
};


template<typename T>
bin_node_ptr<T> BinNode<T>::insert_as_lc(const T &e) {    //��e��Ϊ��ǰ�ڵ�����Ӳ��������

    return this->l_child = new BinNode<T>(e, this);
}


template<typename T>
bin_node_ptr<T> BinNode<T>::insert_as_rc(const T &e) {     //��e��Ϊ��ǰ�ڵ���Һ��Ӳ���
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
void BinNode<T>::traver_pre_r(bin_node_ptr<T> x, VST &visit) {    //������ڵ�x�����ʺ���visit
    if (!x) {          // �ݹ�����������
        return;
    }
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
        visit(x->getData());     //����ͷ�ڵ㲢����
        if (x->getRChild()) { S.push(x->getRChild()); }  //�����Һ�������ջ
        if (x->getLChild()) { S.push(x->getLChild()); }   //������������ջ
    }
}

template<typename T, typename VST>
void traver_in_r(bin_node_ptr<T> x, VST &visit) {     //������ڵ�����ʺ���
    if (!x) { return; }      //�ݹ�����ִ�սڵ�
    traver_R(x->getLChild(), visit);    //�ݹ����������
    visit(x);       //���ʽڵ�x
    traver_R(x->getRChild(), visit);    //�ݹ����������
}


template<typename T, typename VST>
[[noreturn]]
void traver_in_v2(bin_node_ptr<T> x, VST &visit) {    //������ڵ�����ʺ���
    std::stack<bin_node_ptr<T>> S;
    while (true) {
        if (x) { //û�еִ�սڵ�
            S.push(x);   //������ٽڵ㶼ѹ��ջ��
            x = x->getLChild();     //��������̽��
        } else if (!S.empty()) {
            x = S.top(), visit(x->getData());  //����ջ����������
            x = x->getRChild();    //ת���Һ��ӷ���
        } else {
            break;    //�������
        }
    }
}

template<typename T>
bin_node_ptr<T> BinNode<T>::successor() const {
    auto s = this;     //���ڼ�¼��̵���ʱ����
    if (this->getRChild()) {     //������Һ���,��ֱ�Ӻ�̱�����������
        s = this->getLChild();       //���������ڵ㿪ʼ
        while (s->getLChild())  {      //�����ӣ���ͣ��������
            s = s->getLChild();
        }
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


template<typename T, typename VST>
[[noreturn]]
void traver_in_v3(bin_node_ptr<T> x, VST &visit) {    //������ڵ�����ʺ���
    bool back_track = false;      //ǰһ���Ƿ�Ϊ���ݣ��������������ݻ���
    while (true) {
        if ((!back_track) && (x->getLChild())) {    //���ǻ�����������
            x = x->getLChild();  //��ͣ�����̽��
        } else {         //û�����������߸ո��Ѿ�����
            visit(x->getData());        //���ʸýڵ�
            if (x->getRChild()) {  //���Һ���
                x = x->getRChild();        //��������������
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

template<typename T, typename VST>
void traver_post_v(bin_node_ptr<T> x, VST &visit) {
    std::stack<bin_node_ptr<T>> S;
    S.push(x);     //���ڵ���ջ
    while (!S.empty()) {
        if (S.top() != x->getParent()) {     //ջ�����ǵ�ǰ�ڵ�ĸ��ڵ㣬��˵��ջ��һ���������ֵ�����
            goto_HLVFL(S);     //�����ֵ�����ִ�б���
        }
        x = S.top();
        S.pop();
        visit(x->getData());      //����ջ�����ݲ�����
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
        visit(x->getData());        //��������
        if (x->getRChild()) {   //������Һ���
            S.push(x->getRChild());     //�Һ�����ջ
        }
        x = x->getLChild();  //��������
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
        x = S.top(), S.pop();   //����ͷ��㣬�����δ������ �������
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



