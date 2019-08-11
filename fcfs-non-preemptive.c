#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int wait_time;
    int turnaround_time;
} proc;

proc * input(int n)
{
    proc *p_arr = (proc *) malloc(sizeof(proc) * n);

    printf("--------------------------\n");

    for(int i = 0; i < n; ++i) {
        p_arr[i].id = i;
        printf("Enter process %d arrival time: ", i+1);
        scanf("%d", &p_arr[i].arrival_time);
        printf("Enter process %d burst time: ", i+1);
        scanf("%d", &p_arr[i].burst_time);
        printf("--------------------------\n");
    }
    return p_arr;
}

void find_wait_time(proc *p_arr, int n)
{
    // wait time for first process is 0
    p_arr[0].wait_time = 0;
    int cum_burst_time = 0;
    for(int i = 1; i < n; ++i) {
        cum_burst_time += p_arr[i-1].burst_time;
        p_arr[i].wait_time = cum_burst_time - p_arr[i].arrival_time;
    }
}

void sort(proc *p_arr, int n)
{
    for(int i = 0; i < n - 1; ++i) {
        for(int j = 0; j < n - i - 1; ++j) {
            if(p_arr[i].arrival_time > p_arr[i+1].arrival_time) {
                // swap
                proc temp;
                temp.id = p_arr[i].id;
                temp.arrival_time = p_arr[i].arrival_time;
                temp.burst_time= p_arr[i].burst_time;

                p_arr[i].id = p_arr[i+1].id;
                p_arr[i].arrival_time = p_arr[i+1].arrival_time;
                p_arr[i].burst_time= p_arr[i+1].burst_time;

                p_arr[i+1].id = temp.id;
                p_arr[i+1].arrival_time = temp.arrival_time;
                p_arr[i+1].burst_time = temp.burst_time;
            }
        }
    }
}

void find_turnaround_time(proc *p_arr, int n)
{
    for(int i = 0; i < n; ++i)
        p_arr[i].turnaround_time = p_arr[i].burst_time + p_arr[i].wait_time;
}

void display(proc *p_arr, int n)
{
    printf("Process#\tArrival Time\tBurst Time\tWait Time\tTurnaround Time\n");
    for(int i = 0; i < n; ++i) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p_arr[i].id+1, p_arr[i].arrival_time, p_arr[i].burst_time, p_arr[i].wait_time, p_arr[i].turnaround_time);
    }
}

int main(void)
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // input process arrival_time and burst_time
    proc *p_arr = input(n);

    // sort process on arrival time
    sort(p_arr, n);

    // find waiting time of all processes
    find_wait_time(p_arr, n);

    // find turnaround time of all processes
    find_turnaround_time(p_arr, n);

    // display results
    display(p_arr, n);
    return 0;
}
