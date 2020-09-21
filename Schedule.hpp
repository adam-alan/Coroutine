/*
 * @Author: your name
 * @Date: 2020-09-18 20:30:00
 * @LastEditTime: 2020-09-20 23:02:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Coroutine/Schedule.hpp
 */
#if !defined(SCHEDULE_HPP)
#define SCHEDULE_HPP



#include <map>
#include "project.hpp"

#include "Coroutine.hpp"



class Schedule{
public:

    static const int STACK_SIZE = 1024*1024;
    static const int MAX_CO = 100;

    friend void funcPack();

    Schedule();
    //创建一个协程
    
    int create(FuncPtr funcPtr);
    bool isAlive(int coId);
    void resume(int coId);
    void yield();

    ptrdiff_t currentCoroutineId();


private:
    std::map<int,std::shared_ptr<Coroutine>> idToCoroutine;
    char stack_[STACK_SIZE];
    ucontext_t ctx_;

    ptrdiff_t currentCoroutineId_;
    
};









#endif // SCHEDULE_HPP
