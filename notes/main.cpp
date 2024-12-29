/**
 * @file        main.cpp
 * @date        sat dec 28 2024
 * @author      morgan bergen
 * @brief       buffer overflow vulnerability
 *
 * @details     classic example of buffer overflow vulnerability and debugging techniques using gdb
 *              tools like gdb.
 * 
 * 
 * 
 */

/**
 * int read_req(void) {
 *      char buf[128];        //  array of type char with 128 elements
 *      int i;                //  integer variable
 *      gets(buf);            //  reads input from stdin and stores it in buf
 *      i = atoi(buf);        //  converts the string in buf to an integer and stores it in i
 *      return i;             //  returns the integer value stored in i
 * }
 */
