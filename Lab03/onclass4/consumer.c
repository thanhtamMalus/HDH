#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int total_sum;
    int stop_flag;
    sem_t mutex;
    sem_t empty;
    sem_t full;
} SharedData;

int main() {
    const char *name = "OS_Producer_Consumer";
    int fd = shm_open(name, O_RDWR, 0666);
    
    SharedData *shared = mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    while (1) {
        sem_wait(&(shared->full));
        sem_wait(&(shared->mutex));

        if (shared->stop_flag) {
            sem_post(&(shared->mutex));
            break;
        }

        int val = shared->buffer[shared->out];
        shared->out = (shared->out + 1) % BUFFER_SIZE;

        shared->total_sum += val;
        printf("Consumer doc: %d | Tong: %d\n", val, shared->total_sum);

        if (shared->total_sum > 100) {
            printf("Tong > 100. Dung lai!\n");
            shared->stop_flag = 1;
            sem_post(&(shared->full));
            sem_post(&(shared->mutex));
            sem_post(&(shared->empty));
            break;
        }

        sem_post(&(shared->mutex));
        sem_post(&(shared->empty));

        usleep(200000);
    }

    // Don dep vung nho chia se o consumer cuoi cung
    sem_destroy(&(shared->mutex));
    sem_destroy(&(shared->empty));
    sem_destroy(&(shared->full));
    munmap(shared, sizeof(SharedData));
    close(fd);
    shm_unlink(name);

    return 0;
}