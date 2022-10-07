#### C 多线程

##### 运行环境

###### 问题解决

- 找不到 threads.h

  > gcc q1.c -std=c11 -lpthread 无效！
  >
  > 提示： fatal error: threads.h: No such file or directory

  1. 安装[musl库](https://wiki.musl-libc.org/)，以支持<threads.h>

     - ```shell
       sudo apt-get install musl
       sudo apt install musl-tools
       ```

  2. 编译 & 运行 

     ```shell
     musl-gcc q1.c -o q1
     ./q1
     ```

  3. 添加 includePath: 

     ```
     /usr/include/x86_64-linux-musl
     ```

  4.  windows：进行musl交叉编译