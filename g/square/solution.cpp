// Given a sorted array, which may contain negative numbers,
// output the sorted array which contains square of each element.

#include <iostream>

using namespace std;

class Solution
{
    public:
        // O(n) time and space complexity
        void square(int A[], int n)
        {
            // find the first non-negative element
            int p = 0;
            for (; p < n && A[p] < 0; p++);

            int l1 = p;
            int l2 = n-l1;

            int q = p;
            p = p-1;
            int tmp[n];     // extra buffer
            int i = 0;
            // NOTE: not stable, since can have duplicated negative numbers
            //       they are output in reverse order
            while (p >= 0 && q < n)
            {
                if (-A[p] <= A[q])
                {
                    tmp[i] = A[p]*A[p];
                    i++;
                    p--;
                }
                else
                {
                    tmp[i] = A[q]*A[q];
                    i++;
                    q++;
                }
            }
            if (q == n)
            {
                while (p >= 0)
                {
                    tmp[i] = A[p]*A[p];
                    i++;
                    q--;
                }
            }
            else
            {
                while (q < n)
                {
                    tmp[i] = A[q]*A[q];
                    i++;
                    q++;
                }
            }

            // copy buffer back
            for (int i = 0; i < n; i++)
            {
                A[i] = tmp[i];
            }
        }
};

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

int main()
{
    Solution solu;

    int A[] = {-10, -8, -4, -3, 0, 1, 2, 3, 5, 7, 8, 11};
    printArray(A, 12);
    solu.square(A, 12);
    printArray(A, 12);

    return 0;
}
