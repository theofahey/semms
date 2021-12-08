#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/shm.h>
#define KEY 12345
#define KEY2 54321
 // union semun{
 //   int val;
 //   struct semid_ds *buf;
 //   unsigned short *array;
 //   struct seminfo *__buf;

 // };
 int main(){
   int semd;
   int * data;
   int r;
   int v;
   int shmd;
   int fd;
   char input[20];
   printf("type creating or removing \n");
   fgets(input, 20, stdin);
   char * hold = input;
   char * temp;
   temp = strsep(&hold, "\n");
   if (strcasecmp(temp, "creating") == 0){
    shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
    data = shmat(shmd,0,0);
    * data = 0;
    shmdt(data);
    fd = open("story.txt", O_RDWR | O_CREAT , 0777);
    semd = semget(KEY2, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      semd = semget(KEY2, 1, 0);
      v = semctl(semd, 0, GETVAL, 0);
    }
    else {
    union semun us;
    us.val = 1;
    r = semctl(semd, 0, SETVAL, us);
  }
   }
   else if (strcasecmp(temp, "removing") == 0){
     shmctl(shmd, IPC_RMID, 0);
     semctl(semd, IPC_RMID, 0);
     fd = open("story.txt", O_RDWR , 0777);
     char story[5000];
     read(fd,story,5000);
     printf("Full Story: %s \n", story);
   }


   //semop(semd.&sb,1) Interacts with semaphore
   return 0;
 }
