#include <iostream>

int add(int x,int y)
{
    return x+y;
}
int main()
{ 
    int a=0,b=1;
    int (*p)(int,int) = add;
    if(p!=NULL)
        std::cout << p(a,b) << std::endl;
}