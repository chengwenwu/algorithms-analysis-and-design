#include <iostream>
#include <memory.h>
using namespace std;
int* M = NULL;
int fibonacci(int aaa)
{
  if(M[aaa] == -1)
    M[aaa] = fibonacci(aaa-1)+fibonacci(aaa-2);
  return M[aaa];
}

int top_down(int xxx)
{
  M = new int[xxx+1];
  memset(M,-1,(xxx+1)*sizeof(int));
  M[0] = 0;
  M[1] = 1;
  return fibonacci(xxx);
}
int main()
{
  cout<<top_down(5);
  if(M == NULL)
    delete []M;
  return 0;
}
