#ifndef BOX_HPP
#define BOX_HPP

template <typename T>
class Box
{
private:
    T content;

public:
    Box(const T &item) : content(item) {}

    T &get()
    {
        return content;
    }

    const T &get() const
    {
        return content;
    }

    void set(const T &item)
    {
        content = item;
    }
};

#endif // BOX_HPP