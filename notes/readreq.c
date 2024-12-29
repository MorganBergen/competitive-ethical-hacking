/**
 * @file        readreq.c
 * @date        sat dec 28 2024
 * @author      morgan bergen
 * @brief       buffer overflow vulnerability
 *
 * @details     classic example of buffer overflow vulnerability and debugging techniques using gdb
 *              tools like gdb.
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int read_req(void) {
    char buf[128];
    int i;
    gets(buf);  //  dangerous function
    i = atoi(buf);
    return i;
}

int main(void) {
    int req = read_req();
    printf("request value: %d\n", req);
    return 0;
}
