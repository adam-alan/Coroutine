/*
 * @Author: your name
 * @Date: 2020-09-18 20:35:26
 * @LastEditTime: 2020-09-20 23:05:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Coroutine/Coroutine.hpp
 */
#if !defined(COROUTINE_HPP)
#define COROUTINE_HPP

#include "project.hpp"


enum class CO_STATUS{
  FINSHED,
  READY,
  RUNNING,
  SUSPEND  
};


class Coroutine: public std::enable_shared_from_this<Coroutine> {
public:
    Coroutine(FuncPtr funcPtr, std::size_t id);
    ~Coroutine();
    Coroutine(const Coroutine&) = delete;
    Coroutine& operator=(const Coroutine&) = delete;

    FuncPtr funcPtr();

    void setStatus(CO_STATUS status);
    CO_STATUS status();

    ucontext_t& context();
    void setContext(ucontext_t);

    ptrdiff_t id();

    void setStack(char*);
    char* stack();

    ptrdiff_t stackSize();
    ptrdiff_t stackCapacity();

    void setStackCapacity(ptrdiff_t cap);
    void setStackSize(ptrdiff_t size);


    void saveStack(char* top);
    
private:
      
    std::ptrdiff_t id_;
    FuncPtr funcPtr_;
    CO_STATUS status_;
    ucontext_t ctx_;
    
    
    ptrdiff_t size_;
    ptrdiff_t capacity_;
    char * stack_;
};









#endif // COROUTINE_HPP
