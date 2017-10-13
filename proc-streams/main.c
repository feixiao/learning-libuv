#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <uv.h>


// gcc -Wall main.c -o proc-streams  -luv

uv_loop_t *loop;
uv_process_t child_req;
uv_process_options_t options;

void on_exit(uv_process_t *req, int64_t exit_status, int term_signal) {
    fprintf(stderr, "Process exited with status %" PRId64 ", signal %d\n", exit_status, term_signal);
    uv_close((uv_handle_t*) req, NULL);
}

int main() {
    loop = uv_default_loop();

    size_t size = 500;
    char path[size];
    uv_exepath(path, &size); // 获取可执行程序的路径
    strcpy(path + (strlen(path) - strlen("proc-streams")), "test");

    char* args[2];
    args[0] = path;
    args[1] = NULL;


    // 配置选项
    options.stdio_count = 3;
    uv_stdio_container_t child_stdio[3];
    // 忽略标准输入输出
    child_stdio[0].flags = UV_IGNORE;
    child_stdio[1].flags = UV_IGNORE;
    // 使用标准错误输出
    child_stdio[2].flags = UV_INHERIT_FD;
    child_stdio[2].data.fd = 2;
    options.stdio = child_stdio;

    options.exit_cb = on_exit;
    options.file = args[0];
    options.args = args;

    int r;
    // 根据配置的选项创建子进程
    if ((r = uv_spawn(loop, &child_req, &options))) {
        fprintf(stderr, "%s\n", uv_strerror(r));
        return 1;
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}
