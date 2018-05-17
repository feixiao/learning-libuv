#include "uv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// gcc -Wall server.c -o udp_server -luv
static uv_loop_t *loop;
static uv_udp_t server;

static void alloc_cb(uv_handle_t* handle,
    size_t suggested_size,
    uv_buf_t* buf) 
{
    static char slab[65536];

    buf->base = slab;
    buf->len = sizeof(slab);
}

static void close_cb(uv_handle_t* handle) 
{
    uv_is_closing(handle);
}

static void sv_send_cb(uv_udp_send_t* req, int status) 
{
    uv_close((uv_handle_t*) req->handle, close_cb);
    free(req);
}

static void sv_recv_cb(uv_udp_t* handle,
    ssize_t nread,
    const uv_buf_t* rcvbuf,
    const struct sockaddr* addr,
    unsigned flags) 
{
    uv_udp_send_t* req;
    uv_buf_t sndbuf;

    if (nread < 0) 
    {

    }

    if (nread == 0) 
    {
        return;
    }

    printf("I receive the message from client:%s.\n", rcvbuf->base);

    uv_udp_recv_stop(handle);

    req = malloc(sizeof *req);

    sndbuf = uv_buf_init("PONG", 4);
    uv_udp_send(req, handle, &sndbuf, 1, addr, sv_send_cb);
}

int main(void) 
{
    struct sockaddr_in addr;
    uv_udp_send_t req;
    uv_buf_t buf;
    int r;
    
    loop = uv_default_loop();
    r = uv_ip4_addr("0.0.0.0", 8899, &addr);
    r = uv_udp_init(loop, &server);    
    r = uv_udp_bind(&server, (const struct sockaddr*) &addr, 0);  
    r = uv_udp_recv_start(&server, alloc_cb, sv_recv_cb);

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}