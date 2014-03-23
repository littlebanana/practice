#include <iostream>
#include <cstdlib>       // rand
#include <cassert>
#include <algorithm>

using namespace std;

void printArray(int A[], int n)
{
    cout << "[";
    for (int i = 0; i < n; i++)
    {
        cout << A[i];
        if (i < n-1)
        {
            cout << " ";
        }
    }
    cout << "]" << endl;
}

class MaxHeap
{
    public:
        MaxHeap(int _capacity = 10) : capacity(_capacity), size(0), data(new int[_capacity]) {}

        MaxHeap(int A[], int n) : capacity(n), size(n), data(new int[n])
        {
            for (int i = 0; i < n; i++)
            {
                data[i] = A[i];
            }
            heapify();
        }

        ~MaxHeap()
        {
            delete [] data;
        }

        bool isEmpty() const
        {
            return (size == 0);
        }

        int getMax() const
        {
            return data[0];
        }

        int extractMax()
        {
            assert(!isEmpty());

            int max = data[0];
            data[0] = data[--size];
            sink(0);

            return max;
        }

    private:
        inline int parent(int i)
        {
            return (i-1)/2;
        }

        inline int lchild(int i)
        {
            return (i*2+1);
        }

        inline int rchild(int i)
        {
            return (i*2+2);
        }

        void swim(int i)
        {
            while (i > 0 && data[parent(i)] < data[i])
            {
                swap(data[i], data[parent(i)]);
                i = parent(i);
            }
        }

        void sink(int i)
        {
            while (i < size)
            {
                int idx = i;
                int l = lchild(i);
                if (l < size && data[idx] < data[l])
                {
                    idx = l;
                }
                int r = rchild(i);
                if (r < size && data[idx] < data[r])
                {
                    idx = r;
                }
                if (idx == i)
                {
                    break;
                }
                swap(data[i], data[idx]);
                i = idx;
            }
        }

        void heapify()
        {
            int m = size/2;
            for (int i = m; i >= 0; i--)
            {
                sink(i);
            }
        }

        int capacity;
        int size;
        int *data;
};

class Sort
{
    public:
        void bubbleSort(int A[], int n)
        {
            // bubble down approach
            // after each iteration A[0...i] is sorted
            // right elements are bubbled down
            for (int i = 0; i < n-1; i++)
            {
                for (int j = n-1; j > i; j--)
                {
                    if (A[j] < A[j-1])      // exclude "==" for stability
                    {
                        swap(A[j], A[j-1]);
                    }
                }
            }

            // bubble up approach
            // after each iteration A[i...(n-1)] is sorted
            // right elements are bubbled up
            /*
               for (int i = n-1; i > 0; i--)
               {
               for (int j = 0; j < i; j++)
               {
               if (A[j] > A[j+1])      // exclude "==" for stability
               {
               swap(A[j], A[j+1]);
               }
               }
               }
             */
        }

        void selectionSort(int A[], int n)
        {
            // select min approach
            // min of A[i...(n-1)] is seleted
            // after each iteration A[0...i] is sorted
            for (int i = 0; i < n-1; i++)
            {
                int idx = i;
                for (int j = i; j < n; j++)
                {
                    if (A[j] < A[idx])
                    {
                        idx = j;
                    }
                }
                swap(A[i], A[idx]);
            }

            // select max approach
            // min of A[i...(n-1)] is seleted
            // after each iteration A[0...i] is sorted
            /*
               for (int i = n-1; i > 0; i--)
               {
               int idx = i;
               for (int j = 0; j <= i; j++)
               {
               if (A[j] > A[idx])
               {
               idx = j;
               }
               }
               swap(A[i], A[idx]);
               }
             */
        }

        void insertionSort(int A[], int n)
        {
            // insert in the front
            for (int i = 1; i < n; i++)
            {
                int tmp = A[i];
                int j = i-1;
                while (j >= 0 && A[j] > tmp)
                {
                    A[j+1] = A[j];
                    j--;
                }
                A[j+1] = tmp;
            }

            // insert in the end
            /*
               for (int i = n-2; i >= 0; i--)
               {
               int tmp = A[i];
               int j = i+1;
               while (j < n && A[j] < tmp)
               {
               A[j-1] = A[j];
               j++;
               }
               A[j-1] = tmp;
               }
             */
        }

        void shellSort(int A[], int n)
        {
            // Hibbart's squenece,  2^k-1
            int gap = 1;
            while (gap < n)
            {
                gap++;
                gap <<= 1;
                gap--;
            }
            gap++;
            gap >>= 1;
            gap--;

            while (gap > 0)
            {
                // gapped insertion sort
                for (int i = gap; i < n; i++)
                {
                    int tmp = A[i];
                    int j = i - gap;
                    while (j >= 0 && A[j] > tmp)
                    {
                        A[j+gap] = A[j];
                        j -= gap;
                    }
                    A[j+gap] = tmp;
                }
                gap++;
                gap >>= 1;
                gap--;
            }
        }

        void mergeSort(int A[], int n)
        {
            int tmp[n];
            for (int i = 0; i < n; i++)
            {
                tmp[i] = A[i];
            }
            mergeSort(A, 0, n-1, tmp);
        }

        void shuffle(int A[], int n)
        {
            for (int i = n-1; i > 0; i--)
            {
                int j = rand() % (i+1);
                swap(A[i], A[j]);
            }
        }

        void quickSort(int A[], int n)
        {
            shuffle(A, n);
            quickSort(A, 0, n-1);
        }

        void heapSort(int A[], int n)
        {
            MaxHeap maxQ(A, n);

            for (int i = n-1; i >= 0; i--)
            {
                A[i] = maxQ.extractMax();
            }
        }

        void countingSort(int A[], int n, int low, int high)
        {
            int K = high-low+1;
            int cnt[K];
            for (int k = 0; k < K; k++)
            {
                cnt[k] = 0;
            }
            for (int i = 0; i < n; i++)
            {
                cnt[A[i]-low]++;
            }
            for (int k = 1; k < K; k++)
            {
                cnt[k] = cnt[k-1] + cnt[k];
            }

            int tmp[n];
            for (int i = 0; i < n; i++)
            {
                tmp[i] = A[i];
            }

            // reverse order for stability
            // elements which come later are put later
            for (int i = n-1; i >= 0; i--)
            {
                A[cnt[tmp[i]-low]-1] = tmp[i];
                cnt[tmp[i]-low]--;
            }
        }

        void radixSort(int A[], int n, int D)
        {
        }

        void bucketSort(int A[], int n)
        {
        }

    private:
        void merge(int A[], int left, int mid, int right, int tmp[])
        {
            int i = left;
            int p = left;
            int q = mid+1;
            while (p <= mid && q <= right)
            {
                if (A[q] < A[p])
                {
                    tmp[i++] = A[q++];
                }
                else
                {
                    tmp[i++] = A[p++];
                }
            }
            if (p > mid)
            {
                while (q <= right)
                {
                    tmp[i++] = A[q++];
                }
            }
            else
            {
                while (p <= mid)
                {
                    tmp[i++] = A[p++];
                }
            }
        }

        void mergeSort(int A[], int left, int right, int tmp[])
        {
            if (left >= right)
            {
                return;
            }

            int mid = left + (right-left)/2;
            mergeSort(A, left, mid, tmp);
            mergeSort(A, mid+1, right, tmp);
            merge(A, left, mid, right, tmp);

            for (int i = left; i <= right; i++)
            {
                A[i] = tmp[i];
            }
        }

        int partition1(int A[], int pivot, int left, int right)
        {
            swap(A[left], A[pivot]);

            int larger = right+1;
            for (int i = left+1; i < larger; i++)
            {
                if (A[i] > A[left])
                {
                    swap(A[i--], A[--larger]);
                }
            }
            swap(A[left], A[larger-1]);
            return (larger-1);
        }

        int partition2(int A[], int pivot, int left, int right)
        {
            swap(A[left], A[pivot]);

            int smaller = left;
            for (int i = left+1; i <= right; i++)
            {
                if (A[i] <= A[left])
                {
                    swap(A[++smaller], A[i]);
                }
            }
            swap(A[left], A[smaller]);
            return smaller;
        }

        int partition3(int A[], int pivot, int left, int right)
        {
            swap(A[left], A[pivot]);

            int p = left;
            int q = right+1;
            for (; ;)
            {
                while (A[++p] < A[left])
                {
                    if (p == right)
                    {
                        break;
                    }
                }
                while (A[--q] > A[left])
                {
                    if (q == left)
                    {
                        break;
                    }
                }
                if (p >= q)
                {
                    break;
                }
                swap(A[p], A[q]);
            }
            swap(A[left], A[q]);
            return q;
        }

        int partition4(int A[], int pivot, int left, int right)
        {
            swap(A[left], A[pivot]);

            int p = left+1;
            int q = right;
            while (p < q)
            {
                if (A[p] < A[left])
                {
                    p++;
                    continue;
                }
                if (A[q] > A[left])
                {
                    q--;
                    continue;
                }
                swap(A[p++], A[q--]);
            }
            if (p == q)
            {
                if (A[p] > A[left])
                {
                    p--;
                }
            }
            swap(A[left], A[p]);
            return p;
        }

        inline int partition(int A[], int pivot, int left, int right)
        {
            return partition4(A, pivot, left, right);
        }

        void quickSort(int A[], int left, int right)
        {
            if (left >= right)
            {
                return;
            }

            int mid = left + (right-left)/2;
            mid = partition(A, mid, left, right);
            quickSort(A, left, mid-1);
            quickSort(A, mid+1, right);
        }
};

int main()
{
    int n = 20;
    int A[] = {4, 2, 20, 1, 5, 3, 14, 6, 9, 4, 6, 1, 2, 5, 10, 15, 5, 3, 10, 7};
    printArray(A, n);

    Sort sort;
    //sort.countingSort(A, n, -10, 20);
    //sort.bubbleSort(A, n);
    //sort.selectionSort(A, n);
    //sort.insertionSort(A, n);
    //sort.shellSort(A, n);
    //sort.mergeSort(A, n);
    //sort.quickSort(A, n);
    sort.heapSort(A, n);
    printArray(A, n);

    return 0;
}
