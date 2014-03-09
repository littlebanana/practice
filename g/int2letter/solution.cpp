// Write a function which takes a 10-based integer as an input, and output a 26-based string.
// Use alphabet letters to output (i.e., a = 0, b = 1, ..., z = 26).

#include <iostream>
#include <string>

using namespace std;

class Solution
{
    public:
        string int2letter(int x)
        {
            if (x == 0)
            {
                return "a";
            }

            bool sign = (x > 0);
            x = (x < 0 ? -x : x);   // possibly overflow

            // conversion
            string result = (sign ? "" : "-");
            do
            {
                int digit = x % 26;
                result += (digit + 'a');
                x /= 26;
            } while (x > 0);

            // reverse string
            int p = (sign ? 0 : 1);
            int q = result.length()-1;
            while (p < q)
            {
                swap(result[p++], result[q--]);
            }

            return result;
        }

        int letter2int(string s)
        {
            // assume valid input

            int L = s.length();

            // parse an optional sign
            int start = (s[0] == '-' || s[0] == '+' ) ? 1 : 0;
            bool sign = (s[0] != '-');

            // Horner's rule
            int result = 0;
            for (int i = start; i < L; i++)
            {
                result *= 26;
                result += (s[i]-'a');
            }

            return (sign ? result : -result);
        }
};

int main()
{
    Solution solu;

    cout << "mapping =" << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << i << "->" << (char)(i+'a') << " ";
        if (i % 8 == 7)
        {
            cout << endl;
        }
    }
    cout << endl;

    int x = 0;
    string s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;
    x = 1;
    s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;
    x = -1;
    s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;
    x = -17;
    s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;
    x = 17;
    s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;
    x = 26;
    s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;
    x = 27;
    s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;
    x = 30;
    s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;
    x = 51;
    s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;
    x = 52;
    s = solu.int2letter(x);
    cout << "x = " << x << ", " << s << ", " << solu.letter2int(s) << endl;

    return 0;
}
