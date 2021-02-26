#ifndef __SINGLETON_H__
#define __SINGLETON_H__


#include <memory>

template<class T>
class Singleton {
public:
//    static T *instance() {
//        if (!m_instance)
//            m_instance = new T();
//        return m_instance;
//    }

    static std::shared_ptr<T> instance() {
        static std::shared_ptr<T> s = std::make_shared<T>();
        return s;
    }

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

    ~Singleton() = default;

protected:
    Singleton() = default;


//
//private:
//    static T *m_instance;

};

//template<class T>
//T *Singleton<T>::m_instance = nullptr;

#endif//__SINGLETON_H__
