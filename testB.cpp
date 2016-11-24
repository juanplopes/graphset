//&>/dev/null;x="${0%.*}";[ ! "$x" -ot "$0" ]||(rm -f "$x";g++ "$0")&&./a.out "$@"&&exit $?
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <sstream>
using namespace std;

struct Set{
    unsigned long long normal;
    int unique, sz;
    
    Set() : normal(0), unique(0), sz(0) {}
    Set(unsigned long long normal, int unique) : normal(normal), unique(unique), sz(__builtin_popcount(normal)+unique) {}

    int match(Set other) {
        int a = __builtin_popcount(normal&other.normal);
        int b = __builtin_popcount(normal|other.normal) + unique + other.unique;

        return 2*a >= 1*b ?  1 :
               3*a <= 1*b ? -1 : 0;
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
    
    int size() {
        return sz;
    }
};

int N, M, A;

Set S[100];
vector<Set> R[1024];
int B[1024];
int O[1024];

bool backtrack(int k) {
    if (k+1 == (1<<N)) {
        int unique = A+1;

        for(int co=1; co<N; co++) {
            for(int i=1; i<k; i++) {
                if (__builtin_popcount(i) != co) continue;
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
        }
    
        return true;
    }
    
    for(int i=0; i<R[O[k]].size(); i++) {
        /* //if (k==1) cout << " %" << i << endl;
        Set s = R[k][i];
        //if (s.unique == 0) continue;
/*        bool valid = true;
        for(int j=1; j<k && valid; j++) {
            if (s.match(R[j][B[j]]) >= 0)
                valid = false;
        }
        if (!valid) continue;*/
        
        B[O[k]] = i;
        if(backtrack(k+1)) return true;
    }
    return false;
}

bool compare(int a, int b) {
    return R[a].size() < R[b].size();
}

int main() {
    string line;
    while(cin >> N) {
        memset(R, 0, sizeof R);
        memset(S, 0, sizeof S);
        getline(cin, line);
        M = A = 0;


        M = A = 0;
        for(int i=0; i<N; i++) {
            getline(cin, line);
            stringstream sin(line);
        
            S[i] = Set();
            int temp, count = 0;
            while(sin >> temp) {
                A = max(A, temp);
                temp--;
                S[i].normal |= (1<<temp);
                count++;
            }
            M = max(M, count);
        }

        int found = 0;
        for(unsigned long long x=1; x<(1ull<<A); x++) {
            for(int y=0; y<=M; y++) {
                Set s(x, y);
                int count=0, id=0;
                bool valid = true;
                for(int i=0; i<N && valid; i++) {
                    int mat = S[i].match(s);
                    if (mat == 0) valid = false;
                    if (mat > 0) { count++; id |= (1<<i); }
                }
                
                if (valid && count > 0 && count < N) {
                    //if (s.size() == M)
                    R[id].push_back(s);
                    found++;
                }
                
/*                if (found+2 == (1<<N))
                    break;*/
            }
        }

        for(int i=1; i+1<(1<<N); i++)
            O[i] = i;
            
        sort(O+1, O+(1<<N)-1, compare);

        
        for(int i=1; i+1<(1<<N); i++) {
        /*    for(int j=0; j<N; j++) {
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
            cout << endl << endl;*/
            cout << " " << __builtin_popcount(O[i]) << ":" << R[O[i]].size();
            //cout << " " << __builtin_popcount(i) << ":" << R[i].size();
        }
        cout << endl;
        
        int startA = A+1;
        for(int i=0; i<N; i++) {
            startA = S[i].print(startA);
            cout << endl;
        }
        
        cout << endl;
        
        backtrack(1);
        
        cout << endl;
    }
    
}
