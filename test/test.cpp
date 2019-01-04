
#include <iostream>
using namespace std;
template<typename T>
class A
{
public:
    void fun(void (*a)(T &), int b){ cout<<"1"<< endl;}
};
class B
{};
void Fun(B &b) {}

int main()
{
    A<B> xxx;
    xxx.fun(Fun, 1);
    return 0;
}
