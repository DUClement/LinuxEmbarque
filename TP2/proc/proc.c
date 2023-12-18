#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/timer.h>
#define SIZE 50
#define DRIVER_AUTHOR "Christophe Barès"
#define DRIVER_DESC "Hello world Module"
#define DRIVER_LICENSE "GPL"


static struct timer_list my_timer;

struct proc_dir_entry *proc_entry;

int time=1;
int pattern=0;

void my_timer_callback(struct timer_list  *timer);
ssize_t fops_write(struct file * file, const char __user * buffer, size_t count, loff_t * ppos);
ssize_t fops_read(struct file *file, char __user * buffer, size_t count, loff_t * ppos);


static const struct file_operations proc_fops = {
  .read = fops_read,
  .write = fops_write,
};

static int param;
module_param(param, int, 0);
MODULE_PARM_DESC(param, "Un parametre de ce module");

int __init proc_init(void)
{
	printk(KERN_INFO "Hello world!\n");
	proc_entry = proc_create("procFile", 0, NULL, &proc_fops);
	if(proc_entry == NULL)
		return -ENOMEM;
	timer_setup(&my_timer, my_timer_callback, 0);
	mod_timer(&my_timer, jiffies + param);
	printk(KERN_DEBUG "le paramètre est=%d\n", param);
	return 0;
}

void __init proc_exit(void)
{
	del_timer(&my_timer);
	remove_proc_entry("procFile", NULL);
	
	printk(KERN_ALERT "Bye bye...\n");
}
ssize_t fops_read(struct file *file, char __user * buffer,
size_t count, loff_t * ppos) {
	char message[50];
	int errno=0;
	int copy;
	if (count > SIZE) count=SIZE;
	if ((copy=copy_to_user(buffer, message, strlen(message))))
		errno = -EFAULT;
	printk(KERN_INFO "message read, %d, %p\n", copy, buffer);
	return count-copy;
}
ssize_t fops_write(struct file * file, const char __user * buffer,
size_t count, loff_t * ppos) {
	char message[50];
	int len = count;
	int size_of_message;
	if (len > SIZE) len = SIZE;
	printk(KERN_INFO "Recieving new messag\n");
	if (copy_from_user(message, buffer, count)) 
	{
		return -EFAULT;
	}
	message[count] = '\0';
	size_of_message = strlen(message);
	printk(KERN_INFO "New message : %s\n", message);
	return count;
}
void my_timer_callback(struct timer_list  *timer)
{	 
	 printk(KERN_INFO "%led d is on\n",time);
	 if (pattern==0)
	 {
		time ++;
	 }
	 else
	 {
		 time--;
	 }
	 mod_timer(&my_timer, jiffies + param);
	 if (pattern==0)
	 {
		 if (time>=10)
		 {
			 time=1;
		 }
	 }
	 else 
	 {
		 if (time<1)
		 {
			 time=9;
		 }
	 }
	 
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);