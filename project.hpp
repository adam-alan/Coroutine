/*
 * @Author: your name
 * @Date: 2020-09-18 20:46:32
 * @LastEditTime: 2020-09-20 16:41:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Coroutine/project.hpp
 */
#if !defined(PROJECT_HPP)
#define PROJECT_HPP


#include <functional>
#include <ucontext.h>
#include <memory>

using FuncPtr = void(*)();

template<typename T, typename ... Args>
auto& instance(Args ... args){
    static T obj(std::forward<Args>(args)...);
    return obj;
}


#endif // PROJECT_HPP





