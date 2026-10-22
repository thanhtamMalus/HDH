#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <time.h>

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
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(SharedData));
    
    SharedData *shared = mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Chi khoi tao semaphore va bien neu chay producer dau tien
    shared->in = 0;
    shared->out = 0;
    shared->total_sum = 0;
    shared->stop_flag = 0;
    sem_init(&(shared->mutex), 1, 1);
    sem_init(&(shared->empty), 1, BUFFER_SIZE);
    sem_init(&(shared->full), 1, 0);

    srand(time(NULL));
    while (1) {
        int item = (rand() % 11) + 10;

        sem_wait(&(shared->empty));
        sem_wait(&(shared->mutex));

        if (shared->stop_flag) {
            sem_post(&(shared->mutex));
            break;
        }

        shared->buffer[shared->in] = item;
        shared->in = (shared->in + 1) % BUFFER_SIZE;
        printf("Producer ghi: %d\n", item);

        sem_post(&(shared->mutex));
        sem_post(&(shared->full));

        usleep(150000);
    }

    munmap(shared, sizeof(SharedData));
    close(fd);
    return 0;
}