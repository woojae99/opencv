#include <iostream>
#include <opencv2/opencv.hpp>


int main(void)
{
    int a=0, b=1;

    try
    {
        if(a==0)
        {
            throw a;
        }
        std::cout<<"a = " << a <<std::endl;
    }
    catch(int e)
    {
        std::cout<<"a = 0입니다"<<std::endl;
    }



    return 0;
}
