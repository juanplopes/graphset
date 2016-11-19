//&>/dev/null;x="${0%.*}";[ ! "$x" -ot "$0" ]||(rm -f "$x";g++ "$0")&&./a.out "$@"&&exit $?
#include <iostream>
using namespace std;

int S[1000][1000];

void setInput(int k, int to, int from) {
    S[to][0] = 0;
    for(int i=0; i<k; i++) {
        int start = 1<<i;
        for(int j=0; j<start; j++) {
            if (to&(1<<(k-i-1)))
                S[to][start+j] = 1 - S[to][j];
            else
                S[to][start+j] = S[to][j];
        }
    }
    
    for(int i=from+(1<<k)-1; i>=from; i--) {
        S[to][i] = from+2*(i-from)+S[to][i-from]+1;
    }

    for(int i=0; i<from; i++) {
        S[to][i] = i+1;
    }
}

void setInput(int from, int k) {
    for(int j=0; j<(1<<k); j++) {
        setInput(k, j, from);
        for(int i=0; i<from+(1<<k); i++) {
            cout << " " << S[j][i];
        }
        cout << endl;
    }

    cerr << from+(1<<(k-1)) << "/" << from+3*(1<<(k-1)) << endl;
}

int main() {
    int from, k;
    while(cin >> from >> k) {
        int A = from + (1<<(k+1));
        int B = from + (1<<k);
        cout << (1<<k) << " " << B << " " << A << endl;
        setInput(from, k);
    }
    
}
