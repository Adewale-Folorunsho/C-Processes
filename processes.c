#include  <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include <time.h>
#include  <sys/types.h>

#define   MAX_COUNT  200
#define   BUF_SIZE   100

void childrenProcesses();
  
void childProcess();

void parentProcess();
  

int main(){
  time_t t;
  srandom((unsigned) time( & t));
  
  pid_t pid;
  pid = fork();
  char buf[BUF_SIZE];
  if(pid == 0){
    printf("got here\n");
    childProcess();
  }else{
    parentProcess();
  }
}

void childrenProcesses(){
  int status;
  pid_t pid;
  char buf[BUF_SIZE];
  int numProcesses = 2;
  
  while (numProcesses > 0){
    pid = wait(&status);
    sprintf(buf, "Child Pid: %d has completed\n", getpid());
    write(1, buf, strlen(buf));
    numProcesses -= 1; 
  }
}
  
    
void childProcess(){
  unsigned int rand = (random() % 29) + 1;
  unsigned int i;
  char buf[BUF_SIZE];
  for(i = 0; i < rand; i++){
    sprintf(buf, "Child Pid: %d is going to sleep!\n", getpid());
    write(1, buf, strlen(buf));
    sleep((random() % 9) + 1);
    sprintf(buf, "Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    write(1, buf, strlen(buf));
  }
  exit(0);
}

void parentProcess(){
  pid_t pid;
  fork();
  pid = getpid();
  
  if (pid == 0){
    childProcess();
  }else{
    childrenProcesses();
    }
  }