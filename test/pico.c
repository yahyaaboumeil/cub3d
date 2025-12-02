#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
    int fd[2];
    int save_fd = 0;

    for(int i = 0; cmds[i]; i++)
    {
        if(cmds[i + 1] && pipe(fd) == -1)
            return 1;
        if(fork() == 0)
        {
            dup2(save_fd, 0);
            if(cmds[i + 1])
            {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
            }
            if(i)
                close(save_fd);
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        if(i)
                close(save_fd);
        if(cmds[ i + 1])
            close(fd[1]);
        save_fd = fd[0];
    }
    while(wait(NULL) != -1)
    {};
    return 0;
}


int pico(char **cmd[])
{
    int fd[2];
    int close_fd;

    for (int i = 0; cmd[i]; i++)
    {
        if (cmd[i + 1] && pipe(fd) == -1)
            return 1;
        if (fork() == 0)
        {
            dup2(close_fd, 0);
            if (cmd[i + 1]) {
                dup2(fd[1], 1);
                close(fd[0]);      
                close(fd[1]);      
            }
            if (fd[i])
                close(close_fd);
            execvep(cmd[0][i], cmd[i]);
            exit(1);
        }
        if (i)
            close(close_fd);
        if (cmd[i + 1])
            close(fd[1]);
        close_fd = fd[0];
    }
    while (wait(NULL) != -1);
    return 0;
}


int pico(char **cmd[])
{
    int fd[2];
    int save;

    for (int i = 0; cmd[i]; i++)
    {
        if (cmd[i+1] && pipe(fd) == -1)
            return 1;
        if (fork() == 0)
        {
            dup2(save, 0);
            if (cmd[i + 1])
            {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
            }
            if (i)
                close(save);
            execvp(cmd[i][0], cmd[i]); 
            exit(1);
        }
        if (i)
            close(save);
        if (cmd[i + 1])
            close(fd[1]);
        save = fd[0];
    }
    while (wait(NULL) != -1);
    return 0;
}

int main()
{
    return 1;
} 