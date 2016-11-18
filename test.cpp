#include <iostream>
#include <vector>
#include <cstring>
#define A1 1
#define A2 3
#define B1 1
#define B2 2
using namespace std;

int N, M, A, R;
int T[100];
int V[10000];
vector<int> V2[100];
int B[100];

bool backtrack(int k) {
    if (k+1==(1<<N)) {
        for(int i=1; i<k; i++){
            for(int j=0; j<N; j++) {
                if (i&(1<<j)) 
                    cout << " " << (j+1);
                else
                    cout << "  ";
            }        
            cout << ": ";
            
            for(int j=0;j<A; j++) {
                if (V2[i][B[i]]&(1<<j)) cout << " " << (j+1);
            }
            cout << endl;
        }
        return true;
    }
    
    for(int i=0; i<V2[k].size(); i++) {
//        if (i>20) continue;
//        if (k<3) cout << " " << B[1] << " " << i << endl;
    
        bool valid = true;
        for(int j=1; j<k && valid; j++) {
            int a = __builtin_popcount(V2[k][i] & V2[j][B[j]]);
            int b = __builtin_popcount(V2[k][i] | V2[j][B[j]]);
            if (a*A2>b*A1) { valid = false; }
        }
        if (!valid) continue;
        B[k] = i;
        if (backtrack(k+1)) return true;
    }
    return false;
}

int main() {
    while(cin >> N >> M >> A) {
        R = 0;
        memset(T, 0, sizeof T);
        memset(V2, 0, sizeof V2);
        
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                int temp; cin >> temp;
                temp--;
                T[i] |= (1<<temp);
            }   
        }

        for(int i=1; i<(1<<A); i++) {
            bool valid = true;
            int count = 0;
            int id = 0;
            for(int j=0; j<N; j++) {
                int a = __builtin_popcount(i&T[j]);
                int b = __builtin_popcount(i|T[j]);
                if (a*A2>b*A1 && a*B2<b*B1) valid = false;
                if (a*B2>=b*B1) { id |= (1<<j); count++; }
            }        
            //cout << " " << i << " " << valid << " " << count << endl;
            
            if (valid && count > 0 && count < N) {
                V2[id].push_back(i);
            }
        }
        backtrack(1);
        
        /*
        for(int k=1; k<(1<<N); k++) {
            for(int j=0; j<N; j++) {
                if (k&(1<<j)) cout << " " << (j+1);
            }        
            cout << ": ";

            for(int i=0; i<V2[k].size(); i++) {
                for(int j=0;j<A; j++) {
                    if (V2[k][i]&(1<<j)) cout << " " << (j+1);
                }
                cout << " / ";
            }
            cout << endl << endl;
        }*/  
        
    }
}
