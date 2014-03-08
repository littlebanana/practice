// read a big data file to get the top K values

#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>

using namespace std;

class MinHeap
{
    public:
        MinHeap(int K) : size(0), capacity(K), data(new int[K]) {}

        ~MinHeap()
        {
            delete[] data;
        }

        bool empty()
        {
            return (size == 0);
        }

        bool full()
        {
            return (size == capacity);
        }

        void push(int x)
        {
            assert(!full());
            data[size++] = x;
            popup(size-1);
        }

        int peek()
        {
            assert(!empty());
            return data[0];
        }

        int pop()
        {
            assert(!empty());
            int tmp = data[0];
            size--;
            if (size > 0)
            {
                data[0] = data[size];
                popdown(0);
            }
            return tmp;
        }

        void buildHeap(int A[], int K)
        {
            assert(K <= capacity);
            for (int i = 0; i < K; i++)
            {
                data[i] = A[i];
            }
            size = K;
            heapify();
        }

    private:
        inline int parent(int i)
        {
            assert(i > 0);
            return (i-1)/2;
        }

        inline int left(int i)
        {
            return 2*i+1;
        }

        inline int right(int i)
        {
            return 2*i+2;
        }

        void popup(int i)
        {
            while (i > 0 && data[parent(i)] > data[i])
            {
                swap(data[parent(i)], data[i]);
                i = parent(i);
            }
        }

        void popdown(int i)
        {
            while (left(i) < size)
            {
                int idx = i;
                int min = data[i];
                if (left(i) < size && data[left(i)] < min)
                {
                    idx = left(i);
                    min = data[left(i)];
                }
                if (right(i) < size && data[right(i)] < min)
                {
                    idx = right(i);
                    min = data[right(i)];
                }
                if (idx == i)
                {
                    break;
                }
                else
                {
                    swap(data[i], data[idx]);
                    i = idx;
                }
            }
        }

        void heapify()
        {
            int last = (size-1)/2;
            for (int i = last; i >= 0; i--)
            {
                popdown(i);
            }
        }

        int size;
        int capacity;
        int* data;
};

int main()
{
    srand(0);

    int N = 100;
    int A[N];
    for (int i = 0; i < N; i++)
    {
        A[i] = i+1;
    }
    // Knuth's shuffle
    for (int i = N-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        swap(A[i], A[j]);
    }
    cout << "input stream:" << endl;
    cout << " [";
    for (int i = 0; i < N; i++)
    {
        cout << A[i] << " ";
    }
    cout << "]" << endl;

    // heap sort
    MinHeap mheap(N);
    mheap.buildHeap(A, N);
    cout << "heap sorted stream: " << endl;
    cout << " [";
    while (!mheap.empty())
    {
        cout << mheap.pop() << " ";
    }
    cout << "]" << endl;

    // extract top K elements
    int K = 20;
    MinHeap mheap2(K);
    for (int i = 0; i < N; i++)
    {
        if (mheap2.full())
        {
            if (mheap2.peek() < A[i])
            {
                mheap2.pop();
                mheap2.push(A[i]);
            }
        }
        else
        {
            mheap2.push(A[i]);
        }
    }
    cout << "top " << K << " elements: " << endl;
    cout << " [";
    while (!mheap2.empty())
    {
        cout << mheap2.pop() << " ";
    }
    cout << "]" << endl;

    return 0;
}
