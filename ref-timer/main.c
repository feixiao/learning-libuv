#include <stdio.h>

#include <uv.h>

// gcc -Wall main.c -o timer  -luv

uv_loop_t *loop;
uv_timer_t gc_req;
uv_timer_t fake_job_req;

void gc(uv_timer_t *handle) {
    fprintf(stderr, "Freeing unused objects\n");
}

void fake_job(uv_timer_t *handle) {
    fprintf(stdout, "Fake job done\n");
}

int main() {
    loop = uv_default_loop();

    uv_timer_init(loop, &gc_req);
    uv_unref((uv_handle_t*) &gc_req);       // 减少event-loop的引用计数

    uv_timer_start(&gc_req, gc, 0, 2000);

    // could actually be a TCP download or something
    uv_timer_init(loop, &fake_job_req);
    uv_timer_start(&fake_job_req, fake_job, 9000, 0);  // 只触发一次，所以这边执行完程序就退出了()
    return uv_run(loop, UV_RUN_DEFAULT);
}
