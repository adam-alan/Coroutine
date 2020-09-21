<!--
 * @Author: your name
 * @Date: 2020-09-19 20:29:03
 * @LastEditTime: 2020-09-19 20:45:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Coroutine/ucontext函数簇.md
-->

函数簇头文件
=============
ucontext.h


函数标签与功能描述
=============




int getcontext(ucontext_t *ucp);

int setcontext(const ucontext_t *ucp);

void makecontext(ucontext_t *ucp, void (*func)(void), int argc, ...);

int swapcontext(ucontext_t *oucp, const ucontext_t *ucp);

typedef struct {
    ucontext_t *uc_link;
    sigset_t    uc_sigmask;
    stack_t     uc_stack;
    mcontext_t  uc_mcontext;
    ...
} ucontext_t;

其中:


​    uc_link:当前上下文结束时要跳转到的上下文, 其中上下文由makecontext()创建

​    uc_sigmask:当前上下文要响应的信号集

​    uc_stack:上下文使用的stack

​    uc_mcontext:机器特定的上下文的表示

​    上下文：cpu中的寄存器信息

用户上下文的获取和设置
-------------

将当前的context保存在ucp中，成功返回0，错误时返回-1并设置errno

int getcontext(ucontext_t *ucp);



恢复用户上下文为ucp指向的上下文,成功调用不用返回。错误时返回-1并设置errno。ucp所指向的上下文应该是由getcontext()或makecontext产生。

如果上下文是由getcontext()产生，则切换到该上下文之后，程序的在getcontext()后继续执行。

如果上下文是由makecontext()产生，则切换到该上下文后，程序的执行切换到makecontext()所指定的第二个参数。当函数返回后，如果ucp.uc_link为NULL，则结束运行，否则跳转到对应的上下文

int setcontext(const ucontext_t *ucp);





操纵用户上下文
------------

修改通过getcontext取得的上下文ucp。
当上下文通过setcontext或swapcontext激活后，执行func函数，argc为func的参数个数，后面是func的参数序列。当func执行返回后，切换到uc_link指向的上下文，若uc_link为NULL,则退出

void makecontext(ucontext_t *ucp, void (*func)(void), int argc, ...);

保存当前的上下文到oucp，然后切换到ucp所指向的上下文。成功后不返回，失败返回-1并设置errno

int swapcontext(ucontext_t *oucp, const ucontext_t *ucp);





