


makefile version: 1
```makefile
obj-m := lkm.o

 CURRENT_DIR :=$(shell pwd)

 KERNEL_DIR := /usr/src/linux-headers-$(shell uname -r)
all:
    $(MAKE) -C $(KERNEL_DIR) M=$(CURRENT_DIR) modules

clean:
    rm -rf %.o
```

makefile version: 2
```makefile
obj-m := lkm.o
 
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
 
default:
    $(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
```


装载LKM：
``` 
insmod lkm.ko
```
卸载LKM：
```
rmmod lkm.ko
```

```
dollarkillerx@ubuntu:/demo2$ sudo insmod lkm.ko 
insmod: ERROR: could not insert module lkm.ko: Required key not available
内核所有模块都必须使用 UEFI Secure key 签名 淦
```