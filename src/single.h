#ifndef _SINGLE_H
#define _SINGLE_H

//模板单例设计模式
template<typename T>
class Single{
public:
    static T& getInstance(){
        static T t;
        return t;
    }
    Single(const Single&) = delete;
    Single operator=(const Single&) = delete;
protected:
    Single() = default;
    ~Single() = default;
};

#endif
