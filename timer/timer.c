#include <assert.h>
#include <sys/time.h>
#include "uv.h"


// gcc -Wall timer.c -o  timer -luv

int repeat_cb_called = 0;

static long timestamp() {    
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*1000 + tv.tv_usec/1000;  //毫秒
}

static void repeat_close_cb(uv_handle_t* handle) {
    printf("REPEAT_CLOSE_CB\n");
}


static void repeat_cb(uv_timer_t* handle) {
    printf("[%ld]REPEAT_CB %d \n",timestamp(),repeat_cb_called+1);
  
    assert(handle != NULL);
    assert(1 == uv_is_active((uv_handle_t*) handle));
  
    repeat_cb_called++;
  
    if (repeat_cb_called == 5) {
      uv_close((uv_handle_t*)handle, repeat_close_cb);
    }
}


int main() {
    uv_timer_t once;
    int ret;
    ret = uv_timer_init(uv_default_loop(), &once);
    printf("[%ld]start timer\n",timestamp());
    ret = uv_timer_start(&once, repeat_cb, 100,1000); // 100毫秒之后第一次触发，之后的每1000毫秒触发一次
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    // uv_run(uv_default_loop(), UV_RUN_ONCE); // 只运行一次
}