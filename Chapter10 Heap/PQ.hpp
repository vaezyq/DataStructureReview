#include <optional>

template<typename T>

class PQ {      //优先级队列基类(优先级队列可能有不同的实现方式，但是各种实现方式都需要实现以下三种接口)
public:
    virtual void insert(T &&elem) = 0;        //插入元素
    virtual T get_max() const = 0;      //取出优先级最高的词条
    virtual T del_max() = 0;       // 删除优先级最高的词条
};