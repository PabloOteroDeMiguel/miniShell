#include "pipex.h"


#define READ_END    0    /* index pipe extremo escritura */
#define WRITE_END   1

int hijo(t_comm_path *act, char **argv, char **envp)   
{
  int fd1[2],fd2[2];
  int fd;
  int status, pid;
	
  pipe(fd1); 
  pid = fork();     
  if(pid == 0)
  {      		
    close(fd1[READ_END]);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
      exit (0);
    dup2(fd, STDIN_FILENO);
    close(fd);
    dup2(fd1[WRITE_END], STDOUT_FILENO); 
    close(fd1[WRITE_END]);
    // ft_putstr_fd(act->comm[0], 2);
    if (execve(act->comm[0], act->comm, envp) < 0)
      exit (127);
  }
  else  
  {
    close(fd1[WRITE_END]);
    pipe(fd2);
    act = act->next;
    pid = fork();
    if(pid == 0) 
    {
      close(fd2[READ_END]);
      dup2(fd1[READ_END], STDIN_FILENO);
      close(fd1[READ_END]);
      dup2(fd2[WRITE_END], STDOUT_FILENO);			
      close(fd2[WRITE_END]);
      // ft_putstr_fd(act->comm[0], 2);
      if (execve(act->comm[0], act->comm, envp) < 0)
        exit (127);
	  }
	  else 
	  {
      close(fd1[READ_END]);
      close(fd2[WRITE_END]);
      act = act->next;
     	pid = fork();
      // fd3 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	    // if (fd3 < 0)
		  //   exit (0);
		  if(pid == 0)
      {
	      dup2(fd2[READ_END], STDIN_FILENO);
	      close(fd2[READ_END]);
        // dup2(fd3, STDOUT_FILENO);
		    // close(fd3);
        
				if (execve(act->comm[0], act->comm, envp) < 0)
			      exit (127);
	    }
    }      
  }
  close(fd2[READ_END]);
  wait(&status);   
  wait(&status);	
  wait(&status);
  return 0;	
}