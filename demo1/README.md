# LD_PRELOAD 简单利用

### 文件
- normal     正常程序
- malicious  恶意链接库

normal 代码很简单就是 一个字符串比较 (ls 显示当前文件 也差不多  异曲同工 之妙)

### 编译
```
gcc libstr.c  -fPIC -shared -o libstr.so  编译为动态链接库
gcc main.c -L. -lstr -o main              // 注意如果库文件名带有lib  这里-l 就要去掉lib
export LD_LIBRARY_PATH=/home/xxx          #指定动态链接库所在目录位置
ldd main                                  // 查询 链接库依存关系
```

现在程序需要 编写我们的恶意程序 替换原来的 libstr.so库
```cpp 
#include <stdio.h>
#include <string.h>

int my_strcmp(const char *s1, const char *s2) {
    printf("内置password: %s  输入password: %s \n", s1, s2);
    return 0;  // 永远相等
}
```
build: `gcc hack.c -fPIC -shared -o hack.so`
`export LD_PRELOAD="./hack.so"`       #设置LD_PRELOAD环境变量,库中的同名函数在程序运行时优先调用

是不是非常简单蛤

### 小结:
- `strace top` 追踪命令的 so依赖
- 在`/etc/ld.so.preload` 文件写入 so路径  替换动态链接库
- 通过命令 `export LD_PRELOAD="库文件路径"`，设置要优先替换动态链接库
- 如果找不替换库，可以通过 `export LD_LIBRARY_PATH=库文件所在目录路径`，设置系统查找库的目录
- 替换结束，要还原函数调用关系，用命令`unset LD_PRELOAD` 解除
- 查询执行文件so依赖关系，可以用`ldd 程序名称`