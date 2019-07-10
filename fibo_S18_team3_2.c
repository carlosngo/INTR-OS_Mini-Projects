#include <stdio.h>
#include <unistd.h>
typedef long long ll;

ll read_file (ll* n1, ll* n2);
ll compute_fibo (ll n1, ll n2);
ll write_fibo (ll fibnum, char tmp);
ll fibo (char tmp);

ll read_file (ll* n1, ll* n2) {
    FILE* in = fopen("fibo.txt", "r");
    ll a, b, c;
    char ch;
    while (fscanf(in, "%lld%c", &a, &ch) == 2) {
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

ll write_fibo (ll fibnum, char tmp) {
    FILE* in = fopen("fibo.txt", "a");
    	fprintf(in, "%lld%c\n", fibnum, tmp);
    	fclose(in);
    
}

ll fibo (char tmp) {
    ll a, b;
    read_file(&a, &b);
    write_fibo(compute_fibo(a, b), tmp);
}

ll main (void) {
     ll n;
     fscanf(stdin, "%lld", &n);
     int tmp;
	char who;
	tmp = fork();

     for (ll i = 1; i <= n; i++) {
	if(tmp<0)
	  return -1;
	else if(tmp ==0)
	  who = 'c';
	else
	 who = 'p';
         fibo(who);
     }
     return 0;
}
