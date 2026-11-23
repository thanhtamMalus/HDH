#include <stdio.h>
#include <stdlib.h>

typedef struct process{
    int id;
    int arrival, burst;
    int start;
    int finish;
    int response, waiting;
    int tat; //turn around time
} PCB;

void push(PCB *arr, int *n, PCB p){
    arr[*n] = p;
    (*n)++;
}
void pop(PCB *arr, int *n, int index){
    for(int i = index; i < *n - 1; i++){
        arr[i] = arr[i + 1];
    }
    (*n)--;
}

void sort_arrival(PCB *arr, int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j].arrival > arr[j + 1].arrival){
                PCB temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void sort_brust(PCB *arr, int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j].burst > arr[j + 1].burst){
                PCB temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(){
    int n; //so tien trinh
    scanf("%d", &n);
    PCB intput[n];  
    for(int i = 0; i < n; i++){
        scanf("%d %d", &intput[i].arrival, &intput[i].burst);
        intput[i].id = i + 1;
    }
    int remain = n; //so tien trinh con lai
    PCB readyQ[n]; //hang doi san sang
    int ready = 0;
    PCB terminatedQ[n]; //hang ket thuc
    int terminated = 0;

    sort_arrival(intput, n);
    int time = intput[0].arrival; //thoi gian hien tai

    while(terminated < n){
        //dua tat ca tien trinh da den vao hang doi san sang
        while(remain > 0 && intput[0].arrival <= time){
            push(readyQ, &ready, intput[0]);
            pop(intput, &remain, 0);
        }
        //CPU ranh: nhay toi tien trinh den tiep theo
        if(ready == 0){
            time = intput[0].arrival;
            continue;
        }
        //chon tien trinh co burst ngan nhat
        sort_brust(readyQ, ready);
        readyQ[0].start = time;
        readyQ[0].finish = time + readyQ[0].burst;
        readyQ[0].tat = readyQ[0].finish - readyQ[0].arrival;
        readyQ[0].waiting = readyQ[0].start - readyQ[0].arrival;
        readyQ[0].response = readyQ[0].waiting;
        push(terminatedQ, &terminated, readyQ[0]);
        pop(readyQ, &ready, 0);
        time = terminatedQ[terminated - 1].finish;
    }

    //tinh tong de lay trung binh
    double sum_response = 0, sum_waiting = 0, sum_tat = 0, sum_finish = 0;
    for(int i = 0; i < terminated; i++){
        sum_response += terminatedQ[i].response;
        sum_waiting += terminatedQ[i].waiting;
        sum_tat += terminatedQ[i].tat;
        sum_finish += terminatedQ[i].finish;
    }

    printf("Ket qua\n");

    printf("ID Arrival Burst Start Finish TAT Waiting Response\n");
    for (int i = 0; i < terminated; i++){
        printf("%d %d %d %d %d %d %d %d\n", terminatedQ[i].id, terminatedQ[i].arrival, terminatedQ[i].burst, terminatedQ[i].start, terminatedQ[i].finish, terminatedQ[i].tat, terminatedQ[i].waiting, terminatedQ[i].response);
    }

    printf("Trung binh response: %.2f\n", sum_response / n);
    printf("Trung binh waiting: %.2f\n", sum_waiting / n);
    printf("Trung binh TAT: %.2f\n", sum_tat / n);
    printf("Trung binh finish: %.2f\n", sum_finish / n);

    return 0;
}