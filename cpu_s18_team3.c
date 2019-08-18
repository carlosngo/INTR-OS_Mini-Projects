#include <stdio.h>
#include <stdbool.h>
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
    FILE *in = fopen("jobs_s18_team3.txt", "r");
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
    FILE *out = fopen("jobs_s18_team3.txt", "a");
    int i, j, indexCtr;
    int timeFinished[MAX_NUM_OF_PROCESSES];
    int waiting[MAX_NUM_OF_PROCESSES];
    process temp;
    // Copy contents of list to processes
    process processes[MAX_NUM_OF_PROCESSES];
    for (i = 0; i < numOfProcesses; i++) {
        processes[i] = list[i];
    }
    fprintf(out, "\n*FCFS*\n");
    // Sort the processes according to time of arrival
    for (i = 0; i < numOfProcesses-1; i++){
        for (j = 0; j < numOfProcesses-i-1; j++){
            if (processes[j].arrival > processes[j + 1].arrival){
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            } 
        }
    }
    // Write the simulated execution order to the file
    for (i = 0; i < numOfProcesses; i++){
        for (j = 0; j < processes[i].remaining ; j++){
             fprintf(out, "%c", processes[i].p_id);
        }
    }
    // Compute for the AWT
    timeFinished[0] = processes[0].arrival + processes[0].remaining;
    waiting[0] = 0;
    for (i = 1; i < numOfProcesses; i++){
        timeFinished[i] = timeFinished[i-1] + processes[i].remaining;
        waiting[i] = timeFinished[i-1] - processes[i].arrival;
    }
    fprintf(out, "\nAWT = %.2f\n\n", compute_avg(waiting, numOfProcesses));
    fclose(out);
}

void print_sjf(process list[], int numOfProcesses) {
    FILE *out = fopen("jobs_s18_team3.txt", "a");
    int time = 0;
    int i, j;
    int waiting[MAX_NUM_OF_PROCESSES] = {0};
    // Copy contents of list to processes
    process processes[MAX_NUM_OF_PROCESSES];
    for (i = 0; i < numOfProcesses; i++) {
        processes[i] = list[i];
    }
    fprintf(out, "*SJF*\n");
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
            fprintf(out, "%c", processes[nextIndex].p_id);
        }
        waiting[nextIndex] += time - processes[nextIndex].arrival;
        time += shortest;
    }
    fprintf(out, "\nAWT = %.2f\n\n", compute_avg(waiting, numOfProcesses));
    fclose(out);
}

void print_srtf(process list[], int numOfProcesses) {
    FILE *out = fopen("jobs_s18_team3.txt", "a");
    int time = 0;
    int i, j;
    process processes[MAX_NUM_OF_PROCESSES];
    for (i = 0; i < numOfProcesses; i++) {
        processes[i] = list[i];
    }
    int waiting[MAX_NUM_OF_PROCESSES] = {0};
    fprintf(out, "*SRTF*\n");
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
        fprintf(out, "%c", processes[nextIndex].p_id);
        processes[nextIndex].remaining--;
        waiting[nextIndex] += time - processes[nextIndex].arrival;
        time++;
        processes[nextIndex].arrival = time;
    }
    fprintf(out, "\nAWT = %.2f\n\n", compute_avg(waiting, numOfProcesses));
    fclose(out);
}

void print_rr(process list[], int q, int numOfProcesses) {
	bool first_go = true;
	int holder;
	bool retain = false;
	bool finished = false;
	bool checker = true;
	bool dispatched;
    int time = 0;
    int counter;
    int i = 0, j,k,l,m;
    int waiting[MAX_NUM_OF_PROCESSES] = {0};
    process temp;
    // Copy contents of list to processes
    process processes[MAX_NUM_OF_PROCESSES];
    for (i = 0; i < numOfProcesses; i++) {
        processes[i] = list[i];
    }
    // Sort the processes according to time of arrival
    for (m = 0; m < numOfProcesses-1; m++){
        for (j = 0; j < (numOfProcesses)-m-1; j++){
            if (processes[j].arrival > processes[j + 1].arrival){
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            } 
        }
    }
    fprintf(out, "*RR*\n");
    i=0;
    holder = i;
    counter = q;
    dispatched = false;
    while(!finished){
    	//assures that the first in queue is dispatched on time
    	if(first_go){
    		if(processes[0].arrival == time){
    			first_go =false;
    			dispatched = true;
			}
		}
    	
    	if(dispatched){
    		if(retain == false){
    			//fprintf(out, "%d-%d, ", time, processes[i].arrival); // prints the avg waiting calculations
    			waiting[i] += time - processes[i].arrival;
			}
		}
		retain = true;
		dispatched = false;
    	processes[i].remaining--;
		time++;
		counter--;
		fprintf(out, "%c", processes[i].p_id); // prints the dispatched process
		//the process has ended or q is finished
		if(counter == 0 || processes[i].remaining == 0){
			holder = i;//keeps track of previous process
			finished = true;
			checker = true;
			counter = q;
			// go on to next process
			if(i+1 == numOfProcesses){
				i = 0;
			}else if(processes[i+1].arrival <= time){
				i++;
			}
			
			//check if next process still has remaining find if not
			do{
				if(processes[i].remaining > 0){
					checker = false;
					finished = false;
				}else if(i+1 == numOfProcesses){
					i = 0;
				}else{
					i++;
				} 
				
				if(holder == i && processes[i].remaining <= 0){ //checks if it did not see any remaining process
					i = -1;
				}
			}while(checker && (i != -1));
			//dispatch the next process
			if(finished == false){
				dispatched = true;
				if(holder != i){ //previous process maintains its past dispatch time if it did not get out of the process
					retain = false;
					processes[holder].arrival = time;
				}
			}
		}
		
	}
    fprintf(out, "\nAWT = %.2f\n\n", compute_avg(waiting, numOfProcesses));
    fclose(out);
}

double compute_avg(int arr[], int n) {
    double avg = 0;
    int i;
    for (i = 0; i < n; i++) {
        avg += arr[i];
    }
    return avg / n;
}
