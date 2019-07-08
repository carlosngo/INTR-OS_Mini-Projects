#include <stdio.h>
#include <unistd.h>
typedef long long ll;

ll read_file (ll* n1, ll* n2);
ll compute_fibo (ll n1, ll n2);
ll write_fibo (ll fibnum);
ll fibo (void);

ll read_file (ll* n1, ll* n2) {
    FILE* in = fopen("fibo.txt", "r");
    ll a, b, c;
    while (fscanf(in, "%lld", &a) == 1) {
        c = b;
        b = a;
    }
    *n1 = b;
    *n2 = c;
    fclose(in);
}

ll compute_fibo (ll n1, ll n2) {
    return n1 + n2;
}

ll write_fibo (ll fibnum) {
    FILE* in = fopen("fibo.txt", "a");
    fprintf(in, "%lld\n", fibnum);
    fclose(in);
}

ll fibo (void) {
    ll a, b;
    read_file(&a, &b);
    write_fibo(compute_fibo(a, b));
}

ll main (void) {
     ll n;
     fscanf(stdin, "%lld", &n);
     fork();
     for (ll i = 1; i <= n; i++) {
         fibo();
     }
     return 0;
}
