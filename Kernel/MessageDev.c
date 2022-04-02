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

#define DEVICE_NAME "MessageDev"
#define SUCCESS 0
#define BUFF_LEN 200

// Functions
static int devi_open(struct inode *, struct file *);
static ssize_t devi_read(struct file *, char *, size_t, loff_t *);
static ssize_t devi_write(struct file *, const char *, size_t, loff_t *);
static int devi_release(struct inode *, struct file *);
int message_dev_init(void);
void message_dev_clean(void);

// Global Variables declared as static
static int Major;
static int Device_Open = 0;

// Device_Read : 
// the number of times the device driver have been read from kernel space
static int Device_Read = 0;

// Device_Write:
// The number of times the device driver have written into the kernel space
static int Device_Write = 0;

// used to store message sent from user space
static char msg[BUFF_LEN];

static struct class *cls;

static struct file_operations fops = {
    .open = devi_open,
    .read = devi_read,
    .write = devi_write,
    .release = devi_release
};

// __init -> allows memory to be free after initialization 
// as message_dev_init
__init int message_dev_init(void)
{
    // register_chrdev will create & register char device
    // major = 0 - is for dynamic allocation of major
    // major > 0 - attempt to reserve a device with given major & return 0 on success
    // major < 0 - Registering of char device failed
	Major = register_chrdev(0, DEVICE_NAME, &fops);

    if(Major < 0){
        pr_alert("Registering char device failed with %d\n", Major);
        return Major;
    }

    pr_info("I was assigned major number %d.\n", Major);

    // class_create
    // create a struct class pointer 
    // to be used in calls to device_create().
    cls = class_create(THIS_MODULE, DEVICE_NAME);

    // Creates device & register with sysfs
    device_create(cls, NULL, MKDEV(Major,0), NULL, DEVICE_NAME);
    
	pr_info("Device created on /dev/%s\n", DEVICE_NAME);

	return SUCCESS;
}

void message_dev_clean(void)
{
    // Clean up variable
    Device_Write = 0;
    Device_Read = 0;
    // Unregistering & Destroy character device
    device_destroy(cls, MKDEV(Major,0));
    class_destroy(cls);
    unregister_chrdev(Major,DEVICE_NAME);
}

static int devi_open(struct inode *inode_ptr, struct file *file_ptr){

    if (Device_Open)
        return -EBUSY;

    Device_Open++;

    try_module_get(THIS_MODULE);

    return SUCCESS;
}


// Function for reading from device driver
static ssize_t devi_read(struct file *file_ptr, char *buffer, size_t len, loff_t *offset){

    // Tries to Clear a block of memory in the user space
    int clear = clear_user(buffer, BUFF_LEN);
    if(clear!= 0){
        return clear;
    }

    // Copy message from kernel space to user space
    int length = strlen(skip_spaces(msg));
    if(copy_to_user(buffer, skip_spaces(msg), len) == 0){
        Device_Read += 1;
        // Print number of character that is read from kernel space to user space
        // Print number of times device driver has been read
        printk("Number of characters sent from device driver : %d", length);
        printk("Device has been read by %d times", Device_Read);

        return SUCCESS;
    }else{
        return -EFAULT;
    }
}

// Function for Writing to Device Driver from user input
static ssize_t devi_write(struct file *file_ptr, const char *buffer, size_t len, loff_t *offset){
    if(Device_Write >= 0){
        // To clean previous message
        memset(&msg, 0, BUFF_LEN);
    }

    
    // Copy the message from user space to kernal space
    if(copy_from_user(&msg, skip_spaces(buffer),len) == 0){
        // Count number of times written to device driver
        Device_Write += 1;

        // Print the message into kernel space
        printk("Message Written to device driver : %s", msg);
        printk("Number of character Written to device driver: %d", len);
        printk("Device has been written by %d times", Device_Write);

        return SUCCESS;
    }else{
        return -EFAULT;
    }
}
static int devi_release(struct inode *inode_ptr, struct file *file_ptr){
    Device_Open--;          /* We're now ready for our next caller */

    /*
     * Decrement the usage count, or else once you opened the file, you'll
     * never get get rid of the module.
     */
    module_put(THIS_MODULE);

    return SUCCESS;
}

// Module Initialize function
module_init(message_dev_init);
// Module Exit Cleaning function
module_exit(message_dev_clean);


// MODULE LICENSING
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CSC1007 Project Assignment");
MODULE_AUTHOR("P2 Group 4");
MODULE_VERSION("0.1a");
