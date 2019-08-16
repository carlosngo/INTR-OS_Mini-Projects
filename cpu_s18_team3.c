#include<stdio.h>

#define MAX_NUM_OF_PROCESSES 5

typedef struct {
    char p_id;
    int arrival;
    int remaining;
} process;


void read_file(process list[]);
void print_fcfs(process list[]);
void print_sjf(process list[]);
void print_srtf(process list[]);
void print_rr(process list[], int q);
// void write_to_file();

// void write_to_file(){

// }

int
main() {
    
    process list[MAX_NUM_OF_PROCESSES];
    read_file(list);
    print_fcfs(list);
    print_sjf(list);
    print_srtf(list);
    print_rr(list);
    return 0;
}

