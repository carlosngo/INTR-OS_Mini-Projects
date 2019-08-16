#include <stdio.h>

#define MAX_NUM_OF_PROCESSES 5

typedef struct {
    char p_id;
    int arrival;
    int remaining;
} process;


void read_processes(process list[], int* q);
void print_fcfs(process list[]);
void print_sjf(process list[]);
void print_srtf(process list[]);
void print_rr(process list[], int q);

int
main() {
    process list[MAX_NUM_OF_PROCESSES];
    int q;
    read_processes(list, &q);
    print_fcfs(list);
    print_sjf(list);
    print_srtf(list);
    print_rr(list, q);
    return 0;
}

void read_processes(process list[], int* q) {

}

/*
Programmer: Johanna Lim, 11726008
This function takes in the list of processes and writes the simulated execution order as well as the AWT in a file.
*/
void print_fcfs(process list[]) {
// sort the list
// for each struct get char then concant it duration times
//get new string
//for each char in list, get strchr - arrival time and add them all
// divide the total time by the no of structs
//write string
// write awt
}

void print_sjf(process list[]) {
    
}

void print_srtf(process list[]) {
    
}

void print_rr(process list[], int q) {
    
}