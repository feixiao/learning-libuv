#include "uv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// gcc -Wall client.c -o udp_client -luv

static uv_udp_t client;

static uv_loop_t *loop;


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

static void cl_recv_cb(uv_udp_t* handle,
    ssize_t nread,
    const uv_buf_t* buf,
    const struct sockaddr* addr,
    unsigned flags) 
{
    if (nread < 0) 
    {

    }

    if (nread == 0) 
    {
        return;
    }

    printf("I receive the message from server:%s\n", buf->base);
    
    uv_close((uv_handle_t*) handle, close_cb);
}


static void cl_send_cb(uv_udp_send_t* req, int status) 
{   
    uv_udp_recv_start(req->handle, alloc_cb, cl_recv_cb);
}

int main(void) 
{
    struct sockaddr_in addr;    
    uv_udp_send_t req;
    uv_buf_t buf;
    int r;
    
    loop = uv_default_loop();
       
    r = uv_ip4_addr("0.0.0.0", 0, &addr);  
    r = uv_udp_init(loop, &client);   
    r = uv_udp_bind(&client, (const struct sockaddr*) &addr, 0);  
    r = uv_udp_set_broadcast(&client, 1);
    uv_ip4_addr("255.255.255.255", 8899, &addr); 
    buf = uv_buf_init("PING", 4);
    printf("I am sending message to server:%s.\n", buf.base);         
    uv_udp_send(&req,
        &client,
        &buf,
        1,
        (const struct sockaddr*) &addr,
        cl_send_cb);    

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}