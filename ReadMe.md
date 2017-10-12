## libuv学习笔记

### libuv介绍

#### 背景

​	[libuv](http://libuv.org/)是一个跨平台的异步IO库实现，刚开始是为Node.js而开发，Node.js完全构建于libuv之上。

#### 跨平台构建

##### 支持平台

+ Windows
+ Unix
+ Android
+ OS X   **注：ios需要自己移植。**

##### 支持构建工具：

+ autotools
+ Visual Studio
+ Ninja
+ GYP
+ Xcode

#### 特性

- Full-featured event loop backed by epoll, kqueue, IOCP, event ports.
- Asynchronous TCP and UDP sockets
- Asynchronous DNS resolution
- Asynchronous file and file system operations
- File system events
- ANSI escape code controlled TTY
- IPC with socket sharing, using Unix domain sockets or named pipes (Windows)
- Child processes
- Thread pool
- Signal handling
- High resolution clock
- Threading and synchronization primitives

### 快速入门

**注**： 实例代码可以参考test目录下面的测试用例。

+ [timer](./timer/timer.c) 定时器实现，实现了简单的计时器功能，100毫秒之后开始触发每隔1000毫秒重复一次。
+ [threadpool](./threadpool/threadpool.c) 使用内部的线程池，即工作队列。

### 参考资料

+ [libuv](http://libuv.org/)
+ [libuv源码剖析：高效线程池(threadpool)的实现](http://www.cnblogs.com/chenyangyao/p/libuv_threadpool.html)
+ [libuv的线程池，即工作队列](http://blog.csdn.net/lc250123/article/details/52619314)

