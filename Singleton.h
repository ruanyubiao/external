#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template<class T>
class Singleton {
public:
    static T *instance() {
        if (!m_instance)
            m_instance = new T();
        return m_instance;
    }

protected:
    //使继承者无法public构造函数和析构函数
    Singleton() = default;

    ~Singleton() = default;

private:
    static T *m_instance;

    //禁止拷贝构造和赋值运算符. The only way is getInstance()
    Singleton(const Singleton &src) = default;

    Singleton &operator=(const Singleton &src) {}

    class Garbo   //它的唯一工作就是在析构函数中析构Singleton的实例，所以private
    {
    public:
        ~Garbo() {
            if (Singleton::m_instance) {
                delete Singleton::m_instance;
                Singleton::m_instance = nullptr;
            }
        }
    };

    static Garbo garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数，我们不需要访问这个变量，所以不需要初始化
};

template<class T>
T *Singleton<T>::m_instance = nullptr;

#endif//__SINGLETON_H__
