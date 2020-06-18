#include <linux/module.h>
//#include <linux/moduleparam.h>
#include <linux/kernel.h>//
#include <linux/init.h>
#include <linux/stat.h>

#include <linux/unistd.h> //
#include <linux/sched.h> //
#include <linux/sched/signal.h>//
#include <linux/string.h>//
#include <linux/list.h>//
#include <linux/syscalls.h>//
#include <linux/types.h>//
#include <linux/errno.h>//

struct proc_info {// 
	pid_t pid; 
	char name [16];
};

struct procinfos {// 
	long studentID; 
	struct proc_info proc; 
	struct proc_info parent_proc; 
	struct proc_info oldest_child_proc;
}; 

//asmlinkage long sys_get_proc_info (pid_t PID , struct procinfos *info) {
SYSCALL_DEFINE2(get_proc_info, pid_t, PID, struct procinfos*, info){

	int found_pid = 0;
	struct task_struct *task_list;
	struct task_struct *temp01;
	struct task_struct *temp02;

	info->studentID = 1752392;
	printk(KERN_INFO "My Student ID: %ld\n", info->studentID);
	//return 0;//
	
	if (PID == -1){
		info->proc.pid = current->pid;
		strcpy(info->proc.name, current->comm);
		
		info->parent_proc.pid = current->parent->pid;
		strcpy(info->parent_proc.name, current->parent->comm);
		
		if (list_empty(&current->children)){
			info->oldest_child_proc.pid = -1;
			strcpy(info->oldest_child_proc.name, "Nothing");
			return 0;
		}
		temp02 = list_first_entry_or_null(&current->children, struct task_struct, sibling);
		info->oldest_child_proc.pid = temp02->pid;
		strcpy(info->oldest_child_proc.name, temp02->comm);
		return 0;
	}
	
	for_each_process(task_list){
		if (task_list->pid == PID){
			found_pid = 1;
			info->proc.pid = PID;
			strcpy(info->proc.name, task_list->comm);
			
			info->parent_proc.pid = task_list->parent->pid;
			strcpy(info->parent_proc.name, task_list->parent->comm);

			if (list_empty(&task_list->children)){
				info->oldest_child_proc.pid = -1;
				strcpy(info->oldest_child_proc.name, "Nothing");
				return 0;		
			}
			temp01 = list_first_entry_or_null(&task_list->children, struct task_struct, sibling);
			info->oldest_child_proc.pid = temp01->pid;
			strcpy(info->oldest_child_proc.name, temp01->comm);
		}
	}

	if (found_pid == 0){
		return EINVAL;
	}
	
	return 0;
}
