#include<iostream>
#include <cstdint>
#include <unistd.h>
#include<thread>
#include"../../headerFiles/intel8080.h"	
#include "../../headerFiles/RAM.h"

using namespace std;

I8080::I8080(){

}

void I8080::step(){
    clock();
}

void I8080::clock(){
    cout<<"Clock!"<<endl;
}
