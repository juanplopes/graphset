#include <iostream>
#include <cstring>
#include <algorithm>
#define MAXX 100
using namespace std;

int n, m;
unsigned int S[MAXX];
bool G2[MAXX][MAXX];
bool G[MAXX][MAXX];

int D[MAXX], O[MAXX];

bool jaccard(bool value, unsigned int x, unsigned int y) {
    unsigned int u = __builtin_popcount(x|y);
    return value ? __builtin_popcount(x&y)*2 >= u : __builtin_popcount(x&y)*3 <= u;
}

bool backtrack(int bits, int v) {
    if (v == n) {
        cout << "{\"G\":[";
    
        for(int i=0; i<n; i++) {
            unsigned int acc = 0;
            for(int j=0; j<n; j++)
                if (G[i][j])
                    acc |= (1<<j);
            cout << (i>0?",":"") << acc;
        }
        cout << "],\"S\":[";
        for(int i=0; i<n; i++) {
            cout << (i>0?",":"") << S[i];
        }
        
        cout << "],\"D\":[";
        for(int i=0; i<n; i++) {
            cout << (i>0?",":"") << D[i];
        }
        cout << "],\"O\":[";
        for(int i=0; i<n; i++) {
            cout << (i>0?",":"") << O[i];
        }
        cout << "],\"n\":" << n << ",\"b\":" << bits << "}," << endl;
    
        return true;
    }

    for(unsigned int x=1; x<(1<<bits); x++) {
//        if (v==0) cout << "  " << x << endl;
        bool valid = true;
        for(int u=0; valid && u<v; u++) 
            valid = jaccard(G[v][u], S[u], x);
        
        if (valid) {
            S[v] = x;
            if (backtrack(bits, v+1)) return true;
        }
    }
    
    return false;
}

bool compare(const int a, const int b) {
    return D[a] >= D[b];
}

int main() {
    int total = 0;
    while(cin >> n >> m) {
        memset(G2, 0, sizeof G);
        memset(D, 0, sizeof D);
        for(int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            cerr << " " << a << " " << b;
            G2[a][b] = G2[b][a] = true;
            D[a]++;
            D[b]++;
        }
        cerr << endl;

        for(int i=0; i<n; i++)
            O[i] = i;
//        sort(O, O+n, compare);
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                G[i][j] = G2[O[i]][O[j]];
//        sort(D, D+n, greater<int>());
        
        cerr << ++total << " ";
        bool found = false;
        for(int i=2; !found && i<32; i++) {
            cerr << "*" << i << " ";
            if (backtrack(i, 0)) {
                cerr << endl;
                found = true;
            }
        }
        if (!found) {
            cerr << "NOT" << endl;
            return 1;
        }
    }
    return 0;
}
