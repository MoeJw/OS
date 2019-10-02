// C program for Consumer process illustrating 
// POSIX shared-memory API. 
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() 
{ 
	/* the size (in bytes) of shared memory object */
	const int SIZE = 4096; 

	/* name of the shared memory object */
	const char* name = "OS"; 

	/* shared memory file descriptor */
	int shm_fd; 

	/* pointer to shared memory object */
	void* ptr; 

	/* open the shared memory object */
	shm_fd = shm_open(name, O_CREAT |O_RDWR, 0666); 

	/* memory map the shared memory object */
	ptr = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0); 

	int * temp= (int * ) ptr;
	int * head= temp;
	int * tail= temp+1;
	int * buffer= temp+2;
	int size =10;

	/* read from the shared memory object */
	int i=0;
	while(1){
		//sleep(0.5);
		while(*tail==*head);
		//printf("head %d %d\n",*head,*tail);
		int item=buffer[*head];
		*head=(*head+1)% size;
		printf("consume %d\n",item);
		i++;
	}

	/* remove the shared memory object */
	shm_unlink(name); 
	return 0; 
} 

