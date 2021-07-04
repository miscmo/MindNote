#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace MyNote {

class Noncopyable {
protected:
    Noncopyable() = default;
    virtual ~Noncopyable() = default;

    Noncopyable(const Noncopyable&) = delete;
    Noncopyable &operator=(const Noncopyable&) = delete;
};

}

#endif // NONCOPYABLE_H
