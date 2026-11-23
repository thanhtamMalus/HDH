#include <stdio.h>
#include <stdlib.h>

typedef struct process{
    int id;
    int arrival, burst;
    int remain; //burst con lai
    int started; //da chay lan dau chua
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

int main(){
    int n; //so tien trinh
    printf("Nhap so tien trinh: ");
    scanf("%d", &n);
    PCB intput[n];
    printf("Nhap arrival va burst cho tien trinh:\n", n);
    for(int i = 0; i < n; i++){
        scanf("%d %d", &intput[i].arrival, &intput[i].burst);
        intput[i].id = i + 1;
        intput[i].remain = intput[i].burst;
        intput[i].started = 0;
    }
    int quantum; //time quantum
    printf("Nhap quantum: ");
    scanf("%d", &quantum);

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
        //lay tien trinh o dau hang doi
        PCB cur = readyQ[0];
        pop(readyQ, &ready, 0);
        if(cur.started == 0){
            cur.started = 1;
            cur.start = time;
            cur.response = time - cur.arrival;
        }
        //chay toi da 1 quantum
        int run = quantum;
        if (cur.remain < quantum) run = cur.remain;
        time += run;
        cur.remain -= run;
        //tien trinh den trong luc dang chay phai vao hang doi truoc tien trinh bi ngat
        while(remain > 0 && intput[0].arrival <= time){
            push(readyQ, &ready, intput[0]);
            pop(intput, &remain, 0);
        }
        if(cur.remain == 0){
            cur.finish = time;
            cur.tat = cur.finish - cur.arrival;
            cur.waiting = cur.tat - cur.burst;
            push(terminatedQ, &terminated, cur);
        } else {
            push(readyQ, &ready, cur); //quay lai cuoi hang doi
        }
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