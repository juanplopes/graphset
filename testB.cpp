//&>/dev/null;x="${0%.*}";[ ! "$x" -ot "$0" ]||(rm -f "$x";g++ "$0")&&./a.out "$@"&&exit $?
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Set{
    int normal, unique;
    
    Set() : normal(0), unique(0) {}
    Set(int normal, int unique) : normal(normal), unique(unique) {}

    int match(Set other) {
        int a = __builtin_popcount(normal&other.normal);
        int b = __builtin_popcount(normal|other.normal) + unique + other.unique;

        return 3*a >= 2*b ?  1 :
               2*a <= 1*b ? -1 : 0;
    }
    
    int print(int uniqueStart) {
        int i=1, temp=normal;
        while(temp) {
            if (temp%2) 
                cout << " " << i;
            i++;
            temp /= 2;
        }
        
        for(int i=0; i<unique; i++) {
            cout << " " << uniqueStart+i;
        }
        return uniqueStart + unique;
    }
};

int N, M, A;

Set S[20];
vector<Set> R[1024];
int B[1024];

bool backtrack(int k) {
    if (k+1 == (1<<N)) {
        int unique = A;

        for(int i=1; i<k; i++) {
            for(int j=0; j<N; j++) {
                if (i&(1<<j))
                    cout << " " << (j+1);
                else
                    cout << "  ";
            }
            cout << ": ";
            unique = R[i][B[i]].print(unique);
            cout << endl;
        }
    
        return true;
    }
    
    for(int i=0; i<R[k].size(); i++) {
        Set s = R[k][i];
        bool valid = true;
        for(int j=1; j<k && valid; j++) {
            if (s.match(R[j][B[j]]) >= 0)
                valid = false;
        }
        if (!valid) continue;
        
        B[k] = i;
        if(backtrack(k+1)) return true;
    }
    return false;
}

int main() {
    while(cin >> N >> M >> A) {
        memset(R, 0, sizeof R);
        memset(S, 0, sizeof S);
        for(int i=0; i<N; i++) {
            S[i] = Set();
            for(int j=0; j<M; j++) {
                int temp; cin >> temp; temp--;
                S[i].normal |= (1<<temp);
            }
        }
        
        for(int x=1; x<(1<<A); x++) {
            for(int y=0; y<M; y++) {
                Set s(x, y);
                int count=0, id=0;
                bool valid = true;
                for(int i=0; i<N && valid; i++) {
                    int mat = S[i].match(s);
                    if (mat == 0) valid = false;
                    if (mat > 0) { count++; id |= (1<<i); }
                }
                
                if (valid && count > 0 && count < N)
                    R[id].push_back(s);
            }
        }
        
        /*for(int i=1; i+1<(1<<N); i++) {
            for(int j=0; j<N; j++) {
                if (i&(1<<j))
                    cout << " " << (j+1);
                else
                    cout << "  ";
            }
            cout << ": ";

            for(int k=0; k<R[i].size(); k++) {
                R[i][k].print(1000);
                cout << " / ";
            }
            cout << endl << endl;            
        }*/
        
        
        for(int i=0; i<N; i++) {
            S[i].print(A);
            cout << endl;
        }
        
        cout << endl;
        
        backtrack(1);
        
        cout << endl;

    }
    
}
