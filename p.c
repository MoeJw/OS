#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <sys/mman.h>
#include <unistd.h>

int main() 
{ 
	/* the size (in bytes) of shared memory object */
	const int SIZE = 4096; 

	/* name of the shared memory object */
	const char* name = "OS"; 

	/* strings written to shared memory */
	const char* message_0 = "Hello"; 
	const char* message_1 = "World!"; 

	/* shared memory file descriptor */
	int shm_fd; 

	/* pointer to shared memory obect */
	void* ptr; 

	/* create the shared memory object */
	shm_fd = shm_open(name, O_CREAT |O_RDWR, 0600); 

	/* configure the size of the shared memory object */
	ftruncate(shm_fd, SIZE); 

	/* memory map the shared memory object */
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); 
	
	int * temp= (int * ) ptr;
	int * head= &temp[0];
	int * tail= &temp[1];
	int * buffer= &temp[2];
	int size =10;
	buffer[0]=1;
	*tail=0;
	*head=0;
	
	/* write to the shared memory object */
   	int i=1;
	while(1){

	sleep(1);
	/*printf("%d ",*tail);
	printf("%d ",*head);
	printf("%d\n",*buffer);
	printf("head %x %x\n",head,buffer);*/
	int item=i;
	while((*tail+1) % size == *head);
	printf("produce %d\n",item);
	buffer[*tail]=i;
	*tail=(*tail+1)%size;
	i++;
	}


	return 0; 
} 

