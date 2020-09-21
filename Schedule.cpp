/*
 * @Author: your name
 * @Date: 2020-09-18 20:35:35
 * @LastEditTime: 2020-09-20 23:45:41
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Coroutine/Schedule.cpp
 */

#include <assert.h>
#include <cstring>

#include "Schedule.hpp"


// 共享栈模型
/*
 *++++++++++ stack_ + STACK_SIZE <=> top 高地址
 *                                          |
 *                                          | 
 *                                          |    
 *                                          |                
 *++++++++++ &dummy                         |
 *                                          |                    
 *                                          |
 *++++++++++ stack_                         |
 *                                       低地址                
 *
 */

#include <iostream>

void funcPack(){
    auto& scheduler = instance<Schedule>();
 
    auto id = scheduler.currentCoroutineId();
    
    auto coroutine = scheduler.idToCoroutine[id];
    coroutine->funcPtr()();
    
    coroutine->setStatus(CO_STATUS::FINSHED);
}


Schedule::Schedule():
idToCoroutine(),
ctx_(),
currentCoroutineId_(-1),
stack_()
{


}



int Schedule::create(FuncPtr funcPtr){
    
    int id = idToCoroutine.size();

    auto coroutine = std::make_shared<Coroutine>(funcPtr, id);

    idToCoroutine[id] = coroutine;
    return id;
}



void Schedule::resume(int coId){

    //如果没找到协程id，就直接返回
    auto found = idToCoroutine.find(coId);
    if (found == idToCoroutine.end()) {
        return;
    }
    

    
    auto coroutine = found->second;
    CO_STATUS coStatus = coroutine->status();
    
    //如果协程状态为ready
    if (coStatus == CO_STATUS::READY){
        getcontext(&coroutine->context());
        
        coroutine->context().uc_stack.ss_sp = stack_;
        coroutine->context().uc_stack.ss_size = STACK_SIZE;
        coroutine->context().uc_link = &ctx_;
        
        //设置当前运行协程的id
        currentCoroutineId_ = coroutine->id();

        //设置协程状态
        coroutine->setStatus(CO_STATUS::RUNNING);
        makecontext(&coroutine->context(), funcPack, 0);
        swapcontext(&ctx_, &coroutine->context());

    }

    //如果协程状态为suspend
    if (coStatus == CO_STATUS::SUSPEND){
        memcpy(stack_ + STACK_SIZE - coroutine->stackSize(), coroutine->stack(), coroutine->stackSize());            
        currentCoroutineId_ = coId;
        coroutine->setStatus(CO_STATUS::RUNNING);
        swapcontext(&ctx_, &coroutine->context());

    }
        
}

void Schedule::yield(){
    
    //获取当前协程id
    int id = currentCoroutineId_;
    assert(id >= 0);
    //获取当前协程
    auto coroutine = idToCoroutine[id];
    
    // 将当前协程的栈内容保存起来
    coroutine->saveStack(stack_ + STACK_SIZE);    
    
    coroutine->setStatus(CO_STATUS::SUSPEND);
    currentCoroutineId_ = -1;
    swapcontext(&coroutine->context(), &ctx_);

}


bool Schedule::isAlive(int coId){
    return idToCoroutine[coId]->status() != CO_STATUS::FINSHED;
}





ptrdiff_t Schedule::currentCoroutineId(){
    return currentCoroutineId_;
}

