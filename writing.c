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
   int shmd;
   int semd;
   int * data;
   semd = semget(KEY2, 1, 0);
   struct sembuf sb;
   sb.sem_num = 0;
   sb.sem_flg = SEM_UNDO;
   sb.sem_op = -1;
   semop(semd, &sb, 1);
   shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
   data = shmat(shmd, 0, 0);
   printf("data: %d\n", *data);
   int fd = open("story.txt",O_RDWR, 0);
   lseek(fd, -(*data), SEEK_END);
   char line[100];
   read(fd,line,100);
   printf("Last Line Entered: %s \n",line);
   printf("Enter your Line to Write\n");
   char new[200] = {0};
   read(STDIN_FILENO,new,200);
   lseek(fd,0,SEEK_END);
   write(fd,new,strlen(new));
   (*data) = strlen(new);
   shmdt(data);
   sb.sem_op = 1;
   semop(semd, &sb, 1);
   return 0;


 }
