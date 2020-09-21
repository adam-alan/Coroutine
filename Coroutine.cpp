/*
 * @Author: your name
 * @Date: 2020-09-18 22:04:45
 * @LastEditTime: 2020-09-20 23:41:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Coroutine/Coroutine.cpp
 */
#include "Coroutine.hpp"
#include <assert.h>
#include <cstring>



void Coroutine::saveStack(char * top){
    //这个变量地址就是当前栈的栈顶
    char dummy = 0;
    if (capacity_ <  top - &dummy){
        delete stack_;
        capacity_ = top - &dummy;
        stack_ = new char[capacity_];
    }
    size_ = top - &dummy;
    memcpy(reinterpret_cast<void*>(stack_), reinterpret_cast<void*>(&dummy), size_);
}




Coroutine::Coroutine(FuncPtr funcPtr, std::size_t id)
:id_(id),
status_(CO_STATUS::READY),
ctx_(),
funcPtr_(funcPtr),
size_(0),
capacity_(0),
stack_(nullptr)
{
    
}


Coroutine::~Coroutine(){
    if (stack_ != nullptr){
        delete stack_;
    }
}

FuncPtr Coroutine::funcPtr(){
    return funcPtr_;
}

void Coroutine::setStatus(CO_STATUS status){
    status_ = status;
}


CO_STATUS Coroutine::status(){
    return status_;    
}

ucontext_t& Coroutine::context(){
    return ctx_;
}

ptrdiff_t Coroutine::id(){
    return id_;
}

void Coroutine::setContext(ucontext_t ctx){
    ctx_ = ctx;
}

void Coroutine::setStack(char* stack){
    stack_ = stack;
}

char* Coroutine::stack(){
    return stack_;
}

ptrdiff_t Coroutine::stackSize(){
    return size_;    
}
ptrdiff_t Coroutine::stackCapacity(){
    return capacity_;
}

void Coroutine::setStackCapacity(ptrdiff_t cap){
    capacity_ = cap;
}


void Coroutine::setStackSize(ptrdiff_t size){
    size_ = size;
}




