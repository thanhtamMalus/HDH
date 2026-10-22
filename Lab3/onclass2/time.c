#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Thieu tham so\n");
        exit(1);
    }

    struct timeval start, end;

    // lay moc tgian truoc thuc thi
    gettimeofday(&start, NULL);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork tao khong thanh cong\n");
        exit(1);
    } 
    else if (pid == 0) {
        //tien trinh con
        execlp(argv[1],argv[1],NULL);
        perror("Lỗi thực thi lệnh");
        exit(1);
    } 
    else {
        wait(NULL);
        // lay moc tgian sau thuc thi
        gettimeofday(&end, NULL);

        //tinh thoi gian
        double time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        fprintf(stderr, "thoi gian: %f giay\n", time);

        exit(1);
    }


    return 0;
}