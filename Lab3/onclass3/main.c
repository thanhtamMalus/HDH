#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

//khai bao bien toan cuc de ham xu ly tin hieu Ctrl+C co the truy cap
pid_t child_pid = -1;

//xu ly tin hieu Ctrl+C
void handle_sigint(int sig) {
    if (child_pid > 0) {
        kill(child_pid, SIGKILL);
        write(STDOUT_FILENO, "count.sh has stopped\n", 22);
    }
    exit(0);
}

int main(){
    //1.xuat ra welcome
    fprintf(stdout,"Welcome to IT007, I am 25521638\n");
    
    //tin hieu 
    signal(SIGINT, handle_sigint);
    

    //3.
    child_pid = fork();

    if (child_pid < 0) {
        fprintf(stderr, "fork tao khong thanh cong\n");
        exit(1);
    } 
    else if (child_pid == 0) {
        //tien trinh con

        //2.thuc thi file count.sh
        execlp("./count.sh","./count.sh",NULL);
        perror("Lỗi thực thi lệnh");
        exit(1);
    } 
    else {
        wait(NULL);
        exit(0);
    }

}