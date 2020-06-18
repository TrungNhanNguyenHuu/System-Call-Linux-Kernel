#include <get_proc_info.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv){
	int input_num = atoi(argv[1]);
	struct procinfos info;
	if (sys_get_proc_info(input_num, &info) == 0){
		printf("My student ID is: %ld\n", info.studentID);
		printf("Process:		%d	%s\n", info.proc.pid, info.proc.name);
		printf("Parent Process:		%d 	%s\n", info.parent_proc.pid, info.parent_proc.name);
		printf("Oldest child Process:	%d	%s\n", info.oldest_child_proc.pid, info.oldest_child_proc.name);	
	}
	else{
		printf("My student ID is: %ld\n", info.studentID);
		printf("The PID %d does not exist\n", input_num);
	}
	return 0;
}
