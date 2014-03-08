// implement a reference counting smart pointer structure

#include <iostream>

using namespace std;

template<typename T>
class SharedPtr
{
    public:
        // default constructor
        explicit SharedPtr(T* p = NULL) : ptr(p), count(new int(1))
        {
        }

        // copy constructor
        SharedPtr(const SharedPtr<T> &p) : ptr(p.ptr), count(p.count)
        {
            ++(*count);
        }

        // assignment operator
        SharedPtr<T>& operator= (const SharedPtr &p)
        {
            if (this != &p)
            {
                dispose();
                ptr = p.ptr;
                count = p.count;
                ++(*count);
            }
            return *this;
        }

        // destructor
        ~SharedPtr()
        {
            dispose();
        }

        // dereference operator
        T& operator* ()
        {
            return *ptr;
        }

        // member acess operator
        T* operator-> ()
        {
            return ptr;
        }

    private:
        void dispose()
        {
            --(*count);
            if (count == 0)
            {
                delete count;
                delete ptr;
            }
        }

        int* count;
        T* ptr;
};

int main()
{
    SharedPtr<int> p1(new int(10));
    cout << "*p1 = " << *p1 << endl;

    {
        SharedPtr<int> p2(p1);
        cout << "*p2 = " << *p2 << endl;
    }
    cout << "*p1 = " << *p1 << endl;

    {
        SharedPtr<int> p3(p1);
        cout << "*p3 = " << *p3 << endl;
    }
    cout << "*p1 = " << *p1 << endl;

    SharedPtr<int> p4(p1);
    cout << "*p4 = " << *p4 << endl;
    cout << "*p1 = " << *p1 << endl;

    SharedPtr<int> q1(new int(100));
    cout << "*q1 = " << *q1 << endl;

    p1 = q1;
    cout << "*p1 = " << *p1 << endl;

    cout << "*p4 = " << *p4 << endl;

    return 0;
}
