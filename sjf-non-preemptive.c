#include <stdio.h>

/*
 *  function to find wait times
 *  input: wait time array (empty), burst time array, number of processes
 */
void find_wait_time(int*, int**, int);
// sort burst time array in increasing order of burst time
void sort(int*, int);

int main(void) {
    // input burst times
    int burst_time[][2] = {{1, 3}, {2, 6}, {3, 7}, {4, 8}};
    int n = sizeof(burst_time) / (sizeof(int) * 2);

    // sort burst_time
    /* sort(burst_time, n); */

    // calculate wait time and turnaround time
    int wait_time[n];
    find_wait_time(wait_time, burst_time, n);
    int turnaround_time[n];
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; ++i) {
        turnaround_time[i] = wait_time[i] + burst_time[i];
        printf("%d\t\t%d\t\t\t\t%d\n", burst_time[i][0], wait_time[i], turnaround_time[i]);
    }
}

void find_wait_time(int *wt, int **bt, int n)
{
    // first process does not have to wait
    wt[0] = 0;
    for(int i = 1; i < n; ++i) {
        wt[i] = bt[i-1][1] + wt[i-1];
    }
}

/* void sort(int *arr, int n) */
/* { */
/*     for(int i = 0; i < n; ++i) { */

/*     } */
/* } */
