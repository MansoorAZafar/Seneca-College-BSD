#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
 
static char *student_id = "100305226";
static int lab_number = 4;
 
module_param(student_id, charp, 0444);
MODULE_PARM_DESC(student_id, "Student ID");
 
module_param(lab_number, int, 0444);
MODULE_PARM_DESC(lab_number, "Lab number");
 
static int __init lab_status_init(void)
{
    printk(KERN_INFO "DPS912 Lab Status Module: loaded.\n");
    printk(KERN_INFO "DPS912 Lab Status Module: student ID = %s\n", student_id);
    printk(KERN_INFO "DPS912 Lab Status Module: related lab = Lab %d\n", lab_number);
    printk(KERN_INFO "DPS912 Lab Status Module: module_init function has executed.\n");
 
    return 0;
}
 
static void __exit lab_status_exit(void)
{
    printk(KERN_INFO "DPS912 Lab Status Module: module_exit function has executed.\n");
    printk(KERN_INFO "DPS912 Lab Status Module: unloaded for student ID = %s\n", student_id);
}
 
module_init(lab_status_init);
module_exit(lab_status_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("DPS912 Student");
MODULE_DESCRIPTION("A simple lab status kernel module");
MODULE_VERSION("1.0");