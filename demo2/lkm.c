#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int lkm_init(void)  // 模块内核加载时执行
{
    printk("Arciryas:module loaded \n");
    return 0;
}

static void lkm_exit(void)  // 模块卸载时执行
{
    printk("Arciyas: module removed \n");
}

module_init(lkm_init); 
module_exit(lkm_exit);  // 如果未定期卸载函数 则内核不允许卸载该模块