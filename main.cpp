#include<iostream>
#include<map>
#include<vector>
#include<cmath>
#include"custom_allocator.h"
#include"my_list.h"

int factorial(int n){
    if(n==1 || n==0){
        return 1;
    }
    return n*factorial(n-1);
}
int main(){
    /*
    c_allocator<int>alloc;
    std::vector<int, c_allocator<int>>my_v(alloc);
    my_v.resize(10);
    for(int i=0;i<10;i++){
        my_v[i]=i;
    }
    for(int i=0;i<my_v.size();i++){
        std::cout<<my_v[i]<<" ";
    }
    std::cout<<"\n";
    */
    std::cout<<"Allocator map(int int), without restriction\n";
    
    std::map<int, int, std::less<int>, c_allocator<std::pair<const int, int>>> map_cont;

    for (int i = 0; i < 10; ++i) {
        map_cont[i] = factorial(i);
    }

    for (const auto& pair : map_cont) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << '\n';
    }
    
    std::cout<<"Allocator map(int int), with restriction\n";
    c_allocator<std::pair<const int, int>> alloc(10);
    std::map<int, int, std::less<int>, c_allocator<std::pair<const int, int>>> map_cont_r(alloc);

    for (int i = 0; i < 10; ++i) {
        map_cont_r[i] = factorial(i);
    }

    for (const auto& pair : map_cont_r) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << '\n';
    }
    std::cout<<"Allocator my_list(int), without restriction\n";
    my_list<int, c_allocator<int>>myl;
    for(int i=0;i<10;i++){
        myl.push_back(i);
    }
    for(auto it:myl){
        std::cout<<it<<" ";
    }
    std::cout<<"\n";
    std::cout<<"Allocator my_list(int), with restriction\n";
    c_allocator<int>a(10);
    my_list<int, c_allocator<int>>myl_r(a);
    for(int i=0;i<10;i++){
        myl_r.push_back(i);
    }
    for(auto it:myl_r){
        std::cout<<it<<" ";
    }
    return 0;
}