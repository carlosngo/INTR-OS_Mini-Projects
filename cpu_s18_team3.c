#include <stdio.h>

#define MAX_NUM_OF_PROCESSES 5

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
// void write_to_file();

// void write_to_file(){

// }

int
main() {
    process list[MAX_NUM_OF_PROCESSES];
    int q;
    int numOfProcesses = 0;
    read_processes(list, &q, &numOfProcesses);
    int i;
    for (i = 0; i < numOfProcesses; i++) {
        fprintf(stdout, "Process %c will arrive at time=%d and has %d time remaining\n", list[i].p_id, list[i].arrival, list[i].remaining);
    }
    fprintf(stdout, "q = %d\n", q);
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

void print_fcfs(process list[], int numOfProcesses) {

}

void print_sjf(process list[], int numOfProcesses) {
    
}

void print_srtf(process list[], int numOfProcesses) {
    
}

void print_rr(process list[], int q, int numOfProcesses) {
    
}