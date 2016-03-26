kernel struct list_head结构体介绍
1/ 注册节点
LIST_HEAD(struct list_head *head);	// 新建一个head的结构体,然后初始化
INIT_LIST_HEAD(struct list_head *head);	//初始化head,注意head是提前定义好的.		

2/ 增加节点
list_add(struct list_head *new, struct list_head *head);  //将new 添加到head->next  相当于head链表的第一个元素.head本身不是元素.
list_add_tail(struct list_head *new, struct list_head *head); //将new 添加到head->prev  相当于head链表的最后一个元素

3/ 删除节点
list_del(struct list_head *head);   //将head从所在的链表中删除.head->prev head->next 赋值为无效的值

4/ 遍历链表
#define list_entry(ptr, type, member)  container_of(ptr, type, member)

#define list_for_each(pos, struct list_head *head) \
	for(pos = head->next; pos != head; pos = pos->next)

exp: 
struct student {
	char name[50];
	struct list_head list;
};

struct list_head *pos;
list_for_each(pos, head) {
	struct student * pStu = list_entry(pos, struct student, list);
}

5/ 判断是否为空
list_empty(struct list_head *head);

参考代码:https://github.com/generalharry/kernel_list_head/tree/master

for kernel code study: struct list_head
file path in kernel: kernel/include/linux/list.h
