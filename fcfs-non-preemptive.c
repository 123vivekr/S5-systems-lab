#include<stdio.h>

// function to find wait time for process
// input: array of wait times (empty), burst times of each process and number of processes
// output: populate array  with wait time of each process
void find_wait_time(int*, int*, int);

int main()
{
  // input process burst time
  int burst_time[] = {10, 5, 8};
  int proc_no = sizeof(burst_time) / sizeof(int);

  // find waiting time of all processes
  int wait_time[proc_no];
  find_wait_time(wait_time, burst_time, proc_no);

  // calculate turnaround_time and display info
  int turnaround_time[proc_no];
  printf("Process\tWaiting Time\tTurnaround Time\n");
  for(int i = 0; i < proc_no; ++i) {
    turnaround_time[i] = wait_time[i] + burst_time[i];
    printf("%d\t\t%d\t\t\t\t%d\n", i, wait_time[i], turnaround_time[i]);
  }

  return 0;
}

void find_wait_time(int *wt, int *bt, int n)
{
  // first process does not have to wait
  wt[0] = 0;
  for(int i = 1; i < n; ++i) {
    wt[i] = bt[i-1] + wt[i-1];
  }
}
