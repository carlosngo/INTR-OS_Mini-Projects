#include <stdio.h>
// #include <unistd.h>

int read_file (int* n1, int* n2);
int compute_fibo (int n1, int n2);
int write_fibo (int n1, int n2);
int fibo (void);

int read_file (int* n1, int* n2) {
    FILE* in = fopen("fibo.txt", "r");
    int a, b, c, d;
    while (fscanf(in, "%d%d", &a, &b) == 2) {
        c = a;
        d = b;
    }
    *n1 = c;
    *n2 = d;
    fclose(in);
}

int compute_fibo (int n1, int n2) {
    // JOHANNA
}

int write_fibo (int n1, int n2) {
    // JANREN
}

int fibo (void) {
    // JOHANNA
}

int main (void) {
     int n;
     fscanf(stdin, "%d", &n);
     fork();
     for (int i = 1; i < n; i++) {
         fibo();
     }
     return 0;
}
