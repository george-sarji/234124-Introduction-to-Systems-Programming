#include <iostream>

using namespace std;

class B
{
private:
    int n;

public:
    B(int x) : n(x) {}
    B operator+(B &b)
    {
        return B(n + b.n);
    }
    friend ostream &operator<<(ostream &out, const B &b)
    {
        out << "B: " << b.n;
        // Simply using n will not work, as there is no B object that calls this function, but it is rather an ostream.
        // Therefore, the function has to use the reference to the B object in order to retrieve n.
        return out;
    }
    bool operator<(const B &rhs) const
    {
        return n < rhs.n;
    }
};

B smaller(const B &b1, const B &b2)
{
    // b1 is a const, while the function is not. Therefore it assums that it will change the contents of the object.
    // For the fix, the operater overload function was changed to be a const function.
    if (b1 < b2)
        return b1;
    else
        return b2;
}

int main()
{
    B b1(1), b2(2), b3(3);
    // Operator overloads cant take temporary values. Therefore, we have to start a new variable.
    B b_temp = b2 + b3;
    const B b4 = b1 + b_temp;
    cout << smaller(b1, b2) << endl;
    return 0;
}