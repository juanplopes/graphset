#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m;
unsigned int S[10];
bool G[10][10];

int D[10], O[10];


double jaccard(unsigned x, unsigned y) {
    return (double)__builtin_popcount(x&y) / __builtin_popcount(x|y);
}

bool backtrack(double threshold, int bits, int v) {
    if (v == n) {
        cout << "{\"G\":[";
    
        for(int i=0; i<n; i++) {
            unsigned int acc = 0;
            for(int j=0; j<n; j++)
                if (G[O[i]][O[j]])
                    acc |= (1<<j);
            cout << (i>0?",":"") << acc;
        }
        cout << "], \"S\":[";
        for(int i=0; i<n; i++) {
            cout << (i>0?",":"") << S[O[i]];
        }
        
        cout << "], \"D\":[";
        for(int i=0; i<n; i++) {
            cout << (i>0?",":"") << D[O[i]];
        }
        cout << "]}," << endl;
    
        return true;
    }

    for(unsigned int x=0; x<(1<<bits); x++) {
//        if (v==0) cout << "  " << x << endl;
        bool valid = true;
        for(int u=0; valid && u<v; u++) 
            valid = (G[O[v]][O[u]] == (jaccard(S[O[u]], x) > threshold));
        
        if (valid) {
            S[O[v]] = x;
            if (backtrack(threshold, bits, v+1)) return true;
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
        memset(G, 0, sizeof G);
        memset(D, 0, sizeof D);
        for(int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            G[a][b] = G[b][a] = true;
            D[a]++;
            D[b]++;
        }
        for(int i=0; i<n; i++)
            O[i] = i;
        sort(O, O+n, compare);
        
        cerr << ++total << " ";
        bool found = false;
        for(int i=1; !found && i<32; i++) {
            if (backtrack(0.5, i, 0)) {
                cerr << i << endl;
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
