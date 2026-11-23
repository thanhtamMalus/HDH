#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 4096

int main(int argc, char *argv[]) {
    // 1. Kiem tra tham so dau vao
    if (argc < 2) {
        fprintf(stderr, "Cach dung: %s <so_nguyen_duong>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    // Kiem tra input phai la so nguyen duong
    if (n <= 0) {
        fprintf(stderr, "Loi: Vui long nhap vao mot so nguyen duong (> 0).\n");
        exit(1);
    }

    const char *name = "OS_Collatz_Shm";
    int fd;
    int *shared_array;

    // 2. Tao vung nho chia se POSIX
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open that bai");
        exit(1);
    }

    // 3. Cau hinh kich thuoc vung nho chia se
    if (ftruncate(fd, SIZE) == -1) {
        perror("ftruncate that bai");
        exit(1);
    }

    // 4. Anh xa vung nho chia se vao khong gian dia chi tien trinh
    shared_array = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_array == MAP_FAILED) {
        perror("mmap that bai");
        exit(1);
    }

    // 5. Tao tien trinh con bang fork()
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork that bai");
        exit(1);
    }
    else if (pid == 0) {
        // --- TIEN TRINH CON: Tinh toan day Collatz va ghi vao shared memory ---
        int index = 0;
        int current = n;

        shared_array[index++] = current;

        while (current != 1) {
            if (current % 2 == 0) {
                current = current / 2;
            } else {
                current = 3 * current + 1;
            }
            shared_array[index++] = current;
        }
        // Danh dau ket thuc chuoi bang gia tri -1
        shared_array[index] = -1;

        exit(0);
    }
    else {
        // --- TIEN TRINH CHA: Cho tien trinh con chay xong va in ket qua ---
        wait(NULL);

        printf("Chuoi Collatz cho n = %d:\n", n);
        int i = 0;
        while (shared_array[i] != -1) {
            if (shared_array[i + 1] == -1) {
                printf("%d\n", shared_array[i]);
            } else {
                printf("%d, ", shared_array[i]);
            }
            i++;
        }

        // 6. Thu hoi va xoa tai nguyen shared memory
        munmap(shared_array, SIZE);
        close(fd);
        shm_unlink(name);
    }

    return 0;
}