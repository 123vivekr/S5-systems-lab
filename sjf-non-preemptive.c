#include <stdio.h>

typedef struct Process
{
    int pId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;

void Sort(Process *, int);
void display(Process *, int);
int findShortestJob(Process*,int,int);

int main(void)
{
    int n, i;
    int cpuTime = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Array of processes (structures)
    Process process[n];

    printf("\nEnter arrival time and burst time for processes\n");
    for (i=0;i<n;i++)
    {
        printf("P[%d]: ", i + 1);
        scanf("%d", &process[i].arrivalTime);
        scanf("%d", &process[i].burstTime);
        process[i].pId = i + 1;
        process[i].waitingTime = 0;
        process[i].turnaroundTime = 0;
    }

    int shortestJobProcess;
    int waitingTime = 0;

    for(i=0;i<n+1;i++)
    {
        // find the process with shortest job within the cpu time
        shortestJobProcess = findShortestJob(process,n,cpuTime);

        if(shortestJobProcess == -1)
        {
            waitingTime++;
            cpuTime++;
        }
        else 
        {
            cpuTime += process[shortestJobProcess].burstTime;

            process[shortestJobProcess].waitingTime = waitingTime - process[shortestJobProcess].arrivalTime;
            waitingTime += process[shortestJobProcess].burstTime;

            process[shortestJobProcess].turnaroundTime = process[shortestJobProcess].waitingTime + process[shortestJobProcess].burstTime;
            process[shortestJobProcess].arrivalTime = -1;

            // printf("\nP[%d]",process[shortestJobProcess].pId);
        }
    }

    display(process,n);

   
    printf("\n\n");
    return 0;
}


int findShortestJob(Process *process,int n,int cpuTime)
{
    int i,shortJob,flag=1;
    int shortJobFound = 0;
    int shortestJobProcess;

    for(i=0;i<n;i++)
    {
        if(process[i].arrivalTime <= cpuTime && process[i].arrivalTime != -1)
        {
            if(flag)
            {
                shortJob = process[i].burstTime;
                shortestJobProcess = i;
                flag = 0;
            }
            else
            {
                if(process[i].burstTime < shortJob)
                {
                    shortJob = process[i].burstTime;
                    shortestJobProcess = i;
                }   
            }
            shortJobFound = 1;        
        }
    }

    if(shortJobFound)
        return shortestJobProcess;
    else
        return -1;
}

void display(Process *proc,int n)
{
    int i;
    printf("Process ID\tArrival Time\tBurst Time\tWaiting time\tTurnaround time");
    for(i=0;i<n;i++)
    {
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d\t\t%d",proc[i].pId,proc[i].arrivalTime,proc[i].burstTime,proc[i].waitingTime,proc[i].turnaroundTime);
    }
}
