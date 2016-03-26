#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include<linux/uaccess.h>
#include<linux/vmalloc.h>
MODULE_LICENSE("GPL");

static  struct proc_dir_entry *pDir = NULL;

struct student {
	char name[50];
	struct list_head list;
};

struct list_head gStudentList;

ssize_t list_read(struct file *file, char __user * buffer, size_t count, loff_t *offset)
{
	struct list_head *pos;
	struct student *pStu;
	int num = 0;

	printk("call list_read\n");
	list_for_each(pos, &gStudentList) {
		pStu = list_entry(pos, struct student, list);	
		printk("num:%d, name %s\n", num++, pStu->name);
	}
	return 0;
}

ssize_t list_write(struct file *file, const char __user *buffer, size_t count, loff_t *offset)
{
	struct student * pStu = vmalloc(sizeof(struct student));

	memset(pStu->name, 0, sizeof(pStu->name));
	copy_from_user(pStu->name, buffer, count > sizeof(pStu->name) ? sizeof(pStu->name) : count);
	printk("write %s\n", pStu->name);
	
	list_add_tail(&pStu->list, &gStudentList);
	return count;
}


static struct file_operations fop = {
	.read = list_read,
	.write = list_write,
};

void list_create_proc(void)
{
	pDir = proc_create("list_test", 0644, NULL, &fop);
}

static int __init list_init(void)
{
	printk("init myList\n");
	list_create_proc();
	INIT_LIST_HEAD(&gStudentList);
	return 0;
}

static void __exit list_exit(void)
{
	struct student *pStu;
	struct list_head *pos;

	printk("remove mylist\n");
	proc_remove(pDir);
	list_for_each(pos, &gStudentList) {
		pStu = list_entry(pos, struct student, list);
		printk("free %s\n", pStu->name);
		vfree(pStu);
	}
	return;
}

module_init(list_init);
module_exit(list_exit);
