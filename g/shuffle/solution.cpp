// shuffle the array such that A[0] <= A[1] >= A[2] <= A[3] >= A[4] <= ...

#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

void randomShuffle(int A[], int n)
{
    // random shuffle
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        swap(A[j], A[i]);
    }
}

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

class Solution
{
    public:
        // Approach 1: sort, reverse, insert, O(NlogN)
        void shuffle1(int A[], int n)
        {
            int tmp[n];
            for (int i = 0; i < n; i++)
            {
                tmp[i] = A[i];
            }

            sort(tmp, tmp+n);
            int m = n/2;
            for (int i = 0; i < m; i++)
            {
                A[2*i] = tmp[i];
            }
            for (int i = m; i < n; i++)
            {
                A[n-1-2*(i-m)] = tmp[i];
            }
        }

        // Approach 2: swap neighboring element
        void shuffle2(int A[], int n)
        {
            // case 1: i = even, should be A[i-1] <= A[i] >= A[i+1]
            // case 2: i = odd, should be A[i-1] >= A[i] <= A[i+1]
            // loop invariance: A[0...i] satifies the requirement after each iteartion
            // suppose A[0..i-1] works, prove for A[0...i]
            // if i = even and A[i-1] > A[i]
            // since A[i-2] >= A[i-1] > A[i], after swap A[i-2] > A[i] < A[i-1]
            // if i = odd and A[i-1] < A[i]
            // since A[i-2] <= A[i-1] < A[i], after swap A[i-2] < A[i] > A[i-1]
            bool odd = true;    // i's polarity
            for (int i = 1; i < n; i++)
            {
                if ((odd && A[i] < A[i-1]) || (!odd && A[i] > A[i-1]))
                {
                    swap(A[i], A[i-1]);
                }
                odd = !odd;
            }
        }
};


int main()
{
    int n = 10;
    int A[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = i+1;
    }

    randomShuffle(A, n);
    printArray(A, n);

    Solution solu;
    solu.shuffle2(A, n);
    printArray(A, n);

    return 0;
}
