#include <iostream>
#include "my_unique_ptr.h"
#include <utility>

class exampl {    
public:
    char a;
    exampl(char A) : a(A) { std::cout << "Constructor- " << a << std::endl; }
    ~exampl()  { std::cout << " destructor~ " << a << std::endl; }
};


int main()
{
    exampl r('r');

    my::unique_ptr<exampl> g = new exampl('g');
    my::unique_ptr<exampl> h = new exampl('h');
    //g = h;
    //my::unique_ptr<exampl> e(g);
    //my::unique_ptr<exampl> p = h;

    {
        my::unique_ptr<exampl> v = new exampl('v');
        (*v)->a = 'w';
    }
    my::unique_ptr<exampl> y = new exampl('y');
    my::unique_ptr<exampl> mov(std::move(y));

    exampl* smpl = h.release();
    delete smpl;
}
