/*
 * @Author: your name
 * @Date: 2020-09-18 18:47:24
 * @LastEditTime: 2020-09-20 23:54:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Coroutine/main.cpp
 */

#include <iostream>
#include "Schedule.hpp"

using namespace std;




void print1(){
    for (int i = 0;i < 5;i++){
        cout << "Ha Ha Ha" << endl;
        instance<Schedule>().yield();
    }
    cout << "Ha Ha Ha" << endl;

}

void print2(){

    for (int i = 0;i < 5;i++){
        cout << "Hei Hei Hei" << endl;
        instance<Schedule>().yield();
    }
    cout << "Hei Hei Hei" << endl;
}


int main(int argc, char const *argv[])
{

    auto id1 = instance<Schedule>().create(print1);
    auto id2 = instance<Schedule>().create(print2);

    while (instance<Schedule>().isAlive(id1) and instance<Schedule>().isAlive(id2)){
        instance<Schedule>().resume(id1);
        instance<Schedule>().resume(id2);

    }

    // char stack[1024*1024];
    
    // auto func = [](){
    //     cout << "ha ha ha" << endl;
    // };
    
    // ucontext_t ctx;

    // getcontext(&ctx);

    // ctx.uc_link = nullptr;
    // ctx.uc_stack.ss_size = 1024*1024;
    // ctx.uc_stack.ss_sp = stack;

    // makecontext(&ctx, func, 0);    
    // setcontext(&ctx);
    return 0;
}


