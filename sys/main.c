/*
MIT License

Copyright (c) 2022 junan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "mem.h"

void __attribute__((noreturn)) start_kernel()
{
    /**
     * 内存初始化
     *  1. 内核页表建立
     *  2. 开启MMU
     *
     */

    /**
     * trap初始化
     *  1. 设置trap处理函数
     *
     */

    /**
     * 文件系统初始化
     *  1. 初始化磁盘块缓冲区
     *  2. 初始化inode表
     *  3. 初始化file表
     *
     */

    /**
     * 进程调度初始化
     *  1. 创建第一个用户进程
     */

    /**
     * 执行调度器
     *
     */

    mem_init();
    __builtin_unreachable();
}