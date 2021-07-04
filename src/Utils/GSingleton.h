#ifndef GSINGLETON_H
#define GSINGLETON_H


namespace MyNote {

template <class T>
class GSingleton {
public:
    static T* getInstance() {
        if (m_pInstance == nullptr)
            m_pInstance = new T();
        return m_pInstance();
    }

private:
    //禁止拷贝构造和赋值运算符
    GSingleton(const GSingleton& src) {}
    GSingleton &operator=(const GSingleton& src) {}

    class Garbo {
    public:
        ~Garbo() {
            if (GSingleton::m_pInstance) {
                delete GSingleton::m_pInstance;
                GSingleton::m_pInstance = nullptr;
            }
        }
    };

private:
    static T* m_pInstance;
    static Garbo garbo;
};

template <class T>
T* GSingleton<T>::m_pInstance = nullptr;

}


#endif // GSINGLETON_H
