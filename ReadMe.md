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

+ [hello](./hello/main.c) 启动一个loop，其他什么事情都没有做。
+ [idle-basic](./idle-basic/main.c) 一个使用空转handle的例子。


+ [timer](./timer/timer.c) 定时器实现，实现了简单的计时器功能，100毫秒之后开始触发每隔1000毫秒重复一次。
+ [threadpool](./threadpool/threadpool.c) 使用内部的线程池，即工作队列。
+ [uvcat](./uvcat/main.c) 基于libuv实现的cat工具。
+ [uvtee](./uvtee/main.c) 基于libuv实现的tee工具(把标准输入中的内容输出到文件)。
+ [onChange](./onchange/main.c) 监控文件变化。
+ [tcp-echo-server](./tcp-echo-server/main.c)  基于libuv的echo server实现。
+ [udp-dhcp](./udp-dhcp/main.c) 一个从DCHP服务器获取ip的例子。
+ [dns](./dns/dns.c) 异步解析DNS。
+ [interfaces](./interfaces/main.c) 打印出所有可以获取的网卡信息。
+ [thread-create](./thread-create/main.c) 线程的创建和停止。
+ [locks](./locks/main.c) 简单读写锁使用。
+ [queue-work](./queue-work/main.c) 工作队列使用的例子。
+ [queue-cancel](./queue-cancel/main.c) 取消未开始的工作队列。
+ [progress](./progress/main.c) 演示了一个下载管理程序向用户展示各个下载线程的进度。  
+ [spawn](./spawn/main.c) 创建子进程。
+ [detach](./detach/main.c) 创建守护进程。
+ [signal](./signal/main.c) 向进程发生信号。
+  

### 参考资料

+ [libuv](http://libuv.org/)
+ [《User Guide》](http://docs.libuv.org/en/v1.x/guide.html)
+ [libuv源码剖析：高效线程池(threadpool)的实现](http://www.cnblogs.com/chenyangyao/p/libuv_threadpool.html)
+ [libuv的线程池，即工作队列](http://blog.csdn.net/lc250123/article/details/52619314)
+ [Chinese-uvbook](https://github.com/feixiao/Chinese-uvbook)

