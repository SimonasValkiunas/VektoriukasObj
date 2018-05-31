#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "mVector.h"

std::vector<int> v1;
mVector<int> v2;

using get_time = std::chrono::steady_clock ;
void ValdiskasVektorius(std::vector<int> &v, int i){

    auto t1 = get_time::now();
    for (int x = 0; x <i; x++){
        v1.push_back(x);
    }
    auto t2 = get_time::now();
    auto t = t2-t1;
    std::cout<<"Valdiskas vektoriukas  " << std::to_string(i)<<"  vnt  "<<(double)(std::chrono::duration_cast<std::chrono::microseconds>(t).count())/1000000<< "  seconds"<<std::endl;
    v1.clear();
}
void ZaibasMcVynas(mVector<int> &v, int i){

    auto t3 =get_time::now();
    for (int x = 0; x <i; x++)
        v2.push_back(x);
    auto t4 = get_time::now();
    auto tv2 = t4-t3;
    std::cout<<"Mano vektoriukas  " << std::to_string(i)<<" vnt  "<<(double)(std::chrono::duration_cast<std::chrono::microseconds>(tv2).count())/1000000<< "  seconds"<<std::endl;
    v2.clear();
}



int main() {


for (int x=10000; x <= 10000000; ){
     x *= 10;
    ValdiskasVektorius(v1,x);
    ZaibasMcVynas(v2,x);
}





    return 0;
}