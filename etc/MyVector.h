/* 自定义定义一个简单的vector */
#define DEFAULT_CAPACITY 20 /* 默认容量大小，可以理解为预留空间大小 */
#include <iostream>
template <typename T>
class vector
{
protected:
    int _capacity; /* 总容量大小 */
    int _size;     /* 已使用容量大小（用户被允许访问的部分） */
    T *elem;       /* 元素指针 */

public:
    /* 构造函数，分配 size（用户指定大小，此处可空缺）+ DEFAULT_CAPACITY（预留空间） */
    vector(int size = 0) : _capacity(size + DEFAULT_CAPACITY), _size(size), elem(new T[size + DEFAULT_CAPACITY]()){};

    /* 通过已有的数组构造容器，允许选择数组中的某一序列进行构造，注意：选定序列时，high 和 low 应为对应位置的下标 */
    vector(T *const origin, int high, int low = 0)
    {
        CopyFrom(origin, high, low);
    }
    /* 复制构造函数 */
    vector(vector<T> &origin)
    {
        if (_size)
        {
            CopyFrom(origin.elem, origin._size - 1);
        }
        else
        {
            vector();
        }
    }
    /* 返回已使用容量大小 */
    int size() const
    {
        return _size;
    }
    /* 允许用户通过 [] 运算符访问对应下标的单个元素，注意：只允许访问 _size 范围之中的元素，访问 _size 以外的元素将提示 access overflow（访问越界） */
    T &operator[](int i)
    {
        if (i >= _size)
        {
            std::cout << "access overflow" << std::endl;
        }
        return elem[i];
    }

    /* 判断是否需要拓展容量大小 */
    bool isOverflow()
    {
        return _size >= _capacity;
    }
    /* 将 newElem 放入到末尾（相对于 _size 的末尾） */
    void push_back(T newElem)
    {
        if (isOverflow())
        {
            T *temp = elem;
            CopyFrom(elem, _size - 1);
            delete[] temp;
            elem[_size] = newElem;
        }
        else
        {
            elem[_size] = newElem;
        }
        _size++;
    }

    /* 移除最后一个元素（相对于 _size 的最后一个元素） */
    void pop_back()
    {
        _size--;
    }
    void CopyFrom(T *const origin, int high, int low = 0)
    {
        _capacity = (high - low + 1) + DEFAULT_CAPACITY;
        elem = new T[_capacity];
        for (_size = 0; low <= high; elem[_size++] = origin[low++])
        {
        }
    };
    ~vector()
    {
        delete[] elem;
    }
};
