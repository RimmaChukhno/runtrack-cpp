#ifndef BOX_POINTER_HPP
#define BOX_POINTER_HPP

template <typename T>
class Box
{
private:
    T content;

public:
    Box(const T &item) : content(item) {}

    T &get() { return content; }
    const T &get() const { return content; }
    void set(const T &item) { content = item; }
};

// Specialization for pointer types
template <typename T>
class Box<T *>
{
private:
    T *content;

public:
    Box(T *item = nullptr) : content(item) {}

    T &get()
    {
        return *content;
    }

    const T &get() const
    {
        return *content;
    }

    void set(T *item)
    {
        content = item;
    }
};

#endif // BOX_POINTER_HPP