#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/poll.h>
#include <linux/cdev.h>

#define DEVICE_NAME "loadmod"
#define SUCCESS 0
#define BUFF_LEN 80
MODULE_LICENSE("GPL");
static int devi_open(struct inode *, struct file *);
static ssize_t devi_read(struct file *, char *, size_t, loff_t *);
static ssize_t devi_write(struct file *, const char *, size_t, loff_t *);
static int devi_release(struct inode *, struct file *);
int loadmod_initialize(void);
void loadmod_clean(void);

// Global Variables declared as static
static int Major;
static int Device_Open = 0;

static char msg[BUFF_LEN];
static char *msg_ptr;

static struct class *cls;

static struct file_operations fops = {
    .open = devi_open,
    .read = devi_read,
    .write = devi_write,
    .release = devi_release
};

// __init -> allows memory to be free after initialization 
// as loadmod_initialize
__init int loadmod_initialize(void)
{
	Major = register_chrdev(0, DEVICE_NAME, &fops);

    if(Major < 0){
        pr_alert("Registering char device failed with %d\n", Major);
        return Major;
    }

    pr_info("I was assigned major number %d.\n", Major);
    printk(KERN_INFO "I was assigned major number %d. \n", Major);
    
    cls = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(cls, NULL, MKDEV(Major,0), NULL, DEVICE_NAME);
    
	pr_info("Device created on /dev/%s\n", DEVICE_NAME);

	return SUCCESS;
}

void loadmod_clean(void)
{
    device_destroy(cls, MKDEV(Major,0));
    class_destroy(cls);



	//printk(KERN_INFO "Module has been unloaded");
    unregister_chrdev(Major,DEVICE_NAME);
}

static int devi_open(struct inode *inode_ptr, struct file *file_ptr){
    return SUCCESS;
}
static ssize_t devi_read(struct file *file_ptr, char *buffer, size_t len, loff_t *offset){
    int bytes_read = 0;

    // MESSAGES ENDED
    if(*msg_ptr == 0){
        return 0;
    }

    while(len && *msg_ptr){
        // copies data from kernel data segment to the user segment
        put_user(*(msg_ptr++), buffer++);
        len--;
        bytes_read++;
    }
    return bytes_read;
}
static ssize_t devi_write(struct file *file_ptr, const char *buffer, size_t len, loff_t *offset){
    int i;
    pr_info("Writing to device driver : %p ; %s ; %d", file_ptr, buffer,len);
    for(i = 0; i < len && i < BUFF_LEN; i++){
        get_user(msg[i], buffer+i);
        len--;
    }
    return i;
}
static int devi_release(struct inode *inode_ptr, struct file *file_ptr){
    return SUCCESS;
}

module_init(loadmod_initialize);
module_exit(loadmod_clean);

// MODULE_DESCRIPTION("READ & WRITE DEV MODULE");
// MODULE_AUTHOR("PROJECT");
// MODULE_VERSION("0.1a");