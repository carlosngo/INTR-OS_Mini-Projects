#include <stdio.h>

#define MAX_NUM_OF_PROCESSES 5
#define FALSE 0
#define TRUE 1

typedef struct {
    char p_id;
    int arrival;
    int remaining;
} process;

void read_processes(process list[], int* q, int* numOfProcesses);
void print_fcfs(process list[], int numOfProcesses);
void print_sjf(process list[], int numOfProcesses);
void print_srtf(process list[], int numOfProcesses);
void print_rr(process list[], int q, int numOfProcesses);
double compute_avg(int arr[], int n);

int
main() {
    process list[MAX_NUM_OF_PROCESSES];
    int q;
    int numOfProcesses = 0;
    read_processes(list, &q, &numOfProcesses);
    print_fcfs(list, numOfProcesses);
    print_sjf(list, numOfProcesses);
    print_srtf(list, numOfProcesses);
    print_rr(list, q, numOfProcesses);
    return 0;
}

void read_processes(process list[], int* q, int* numOfProcesses) {
    FILE *in = fopen("jobs.txt", "r");
    char ch;
    
    while(fscanf(in, "%c", &ch)) {
        if (ch == 'q') {
            fscanf(in, "=%d", q);
            break;
        } else {
            list[*numOfProcesses].p_id = ch;
            fscanf(in, ", %d, %d ", &list[*numOfProcesses].arrival, &list[*numOfProcesses].remaining);
            *numOfProcesses = *numOfProcesses + 1;
        }
    }
    fclose(in);
}

/*
Programmer: Johanna Lim, 11726008
This function takes in the list of processes and writes the simulated execution order as well as the AWT in a file.
*/
void print_fcfs(process list[], int numOfProcesses) {
// sort the list
// for each struct get char then concant it duration times
//get new string
//for each char in list, get strchr - arrival time and add them all
// divide the total time by the no of structs
//write string
// write awt
}

void print_sjf(process list[], int numOfProcesses) {
    int time = 0;
    int i, j;
    int waiting[MAX_NUM_OF_PROCESSES] = {0};
    // Copy contents of list to processes
    process processes[MAX_NUM_OF_PROCESSES];
    for (i = 0; i < numOfProcesses; i++) {
        processes[i] = list[i];
    }
    fprintf(stdout, "*SJF*\n");
    while (1) {
        char nextIndex = -1;
        int shortest = 1e9;
        int finished = TRUE;
        for (i = 0; i < numOfProcesses; i++) { // classic find min
            if (processes[i].remaining > 0) {
                finished = FALSE; // found a process that's in the queue
                if (processes[i].arrival <= time && processes[i].remaining < shortest) {
                    nextIndex = i;
                    shortest = processes[i].remaining;
                }
            }
        }
        if (finished) break;
        processes[nextIndex].remaining = 0;
        for (i = 0; i < shortest; i++) {
            fprintf(stdout, "%c", processes[nextIndex].p_id);
        }
        waiting[nextIndex] += time - processes[nextIndex].arrival;
        time += shortest;
    }
    fprintf(stdout, "\nAWT = %llf\n\n", compute_avg(waiting, numOfProcesses));
    
}

void print_srtf(process list[], int numOfProcesses) {
    int time = 0;
    int i, j;
    process processes[MAX_NUM_OF_PROCESSES];
    for (i = 0; i < numOfProcesses; i++) {
        processes[i] = list[i];
    }
    int waiting[MAX_NUM_OF_PROCESSES] = {0};
    fprintf(stdout, "*SRTF*\n");
    while (1) {
        int nextIndex = -1;
        int shortest = 1e9;
        int finished = TRUE;
        for (i = 0; i < numOfProcesses; i++) { // classic find min
            if (processes[i].remaining > 0) {
                finished = FALSE;
                if (processes[i].arrival <= time && processes[i].remaining < shortest) {
                    nextIndex = i;
                    shortest = processes[i].remaining;
                }
            }
        }

        if (finished) break;
        fprintf(stdout, "%c", processes[nextIndex].p_id);
        processes[nextIndex].remaining--;
        waiting[nextIndex] += time - processes[nextIndex].arrival;
        time++;
        processes[nextIndex].arrival = time;
    }
    fprintf(stdout, "\nAWT = %llf\n\n", compute_avg(waiting, numOfProcesses));
}

void print_rr(process list[], int q, int numOfProcesses) {
    
}

double compute_avg(int arr[], int n) {
    double avg = 0;
    int i;
    for (i = 0; i < n; i++) {
        avg += arr[i];
    }
    return avg / n;
}