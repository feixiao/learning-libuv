#include <assert.h>
#include <sys/time.h>
#include "uv.h"


// gcc -Wall threadpool.c  -o  threadpool  -luv


#define FIB_UNTIL 8
uv_loop_t *loop;

long fib_(long t)
{
    if (t == 0 || t == 1)
        return 1;
    else
        return fib_(t-1) + fib_(t-2);
}

void fib(uv_work_t *req)
{
    int n = *(int *) req->data;
    fprintf(stderr, "%dth fibonacci\n", n);
    if (random() % 2)
    {
        sleep(5);
    }
    else
    {
        sleep(10);
    }
    long fib = fib_(n);
    fprintf(stderr, "%dth fibonacci is [%ld] done \n", n,fib);
}

void after_fib(uv_work_t *req, int status)
{
   fprintf(stderr, "Done calculating %dth fibonacci\n", *(int *) req->data);
}

int main()
{
    loop = uv_default_loop();

    int data[FIB_UNTIL];
    uv_work_t req[FIB_UNTIL];
    int i;
    for (i = 0; i < FIB_UNTIL; i++)
    {
        data[i] = i;
        req[i].data = (void *) &data[i];
        uv_queue_work(loop, &req[i], fib, after_fib);
    }
    uv_cancel(&req[7]); // 取消任务

    return uv_run(loop, UV_RUN_DEFAULT);
}