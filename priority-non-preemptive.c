#include <stdio.h>

typedef struct Process
{
    int pId;
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    int waitingTime;
    int priority;
} Process;

void Sort(Process*,int);
void display(Process*,int);
int findhighPriorityJob(Process*,int,int);


int main(void)
{
     int n, i,j;
     int cpuTime = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Array of processes (structures)
    Process process[n];

    printf("\nEnter arrival time,burst time and priority for processes\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d]: ",i+1);
        scanf("%d", &process[i].arrivalTime);
        scanf("%d", &process[i].burstTime);
        scanf("%d",&process[i].priority);
        process[i].pId = i+1;
        process[i].waitingTime = 0;
        process[i].turnaroundTime = 0;
    }

    int highestPriorityProcess;
    int waitingTime = 0;

    for(i=0;i<n+1;i++)
    {
        // find the process with shortest job within the cpu time
        highestPriorityProcess = findhighPriorityJob(process,n,cpuTime);

        if(highestPriorityProcess == -1)
        {
            waitingTime++;
            cpuTime++;
        }
        else 
        {
            cpuTime += process[highestPriorityProcess].burstTime;

            process[highestPriorityProcess].waitingTime = waitingTime - process[highestPriorityProcess].arrivalTime;
            waitingTime += process[highestPriorityProcess].burstTime;

            process[highestPriorityProcess].turnaroundTime = process[highestPriorityProcess].waitingTime + process[highestPriorityProcess].burstTime;
            process[highestPriorityProcess].arrivalTime = -1;

            // printf("\nP[%d]",process[shortestJobProcess].pId);
        }
    }

    display(process,n);
    printf("\n\n");

    return 0;
}


int findhighPriorityJob(Process *process,int n,int cpuTime)
{
    int i,priorityJob,flag=1;
    int highPriorityFound = 0;
    int highPriorityProcess;

    for(i=0;i<n;i++)
    {
        if(process[i].arrivalTime <= cpuTime && process[i].arrivalTime != -1)
        {
            if(flag)
            {
                priorityJob = process[i].priority;
                highPriorityProcess = i;
                flag = 0;
            }
            else
            {
                if(process[i].priority > priorityJob)
                {
                    priorityJob = process[i].priority;
                    highPriorityProcess = i;
                }   
            }
            highPriorityFound = 1;        
        }
    }

    if(highPriorityFound)
        return highPriorityProcess;
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
