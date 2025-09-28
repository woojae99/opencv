#include <iostream>
#include <opencv2/opencv.hpp>


int main(void)
{
    std::vector<double> v1;
    v1.push_back(100);
    v1.push_back(1000);
    v1.insert(v1.begin()+1,1);
    std::cout<<v1[1]<<std::endl;
    std::cout<<v1.at(1)<<std::endl;
    std::cout<<"size : "<< v1.size()<<std::endl;
    v1.erase(v1.begin()+1);
    std::cout<<v1.size()<<std::endl;
    v1.pop_back();
    std::cout<<"size : "<<v1.size()<<std::endl;



    return 0;
}
