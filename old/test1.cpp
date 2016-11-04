#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#define MAXX 100
using namespace std;

int n, m;
set<int> S[MAXX];
set<int> E[MAXX];
bool G[MAXX][MAXX];

int D[MAXX], O[MAXX];

bool jaccard(set<int> &x, set<int> &y) {
    set<int> I, U;
    set_intersection(x.begin(),x.end(),y.begin(),y.end(), std::inserter(I, I.begin()));
    set_union(x.begin(),x.end(),y.begin(),y.end(), std::inserter(U, U.begin()));
    //cout << "(" << I.size() << " " << U.size() << ") ";
    return I.size() > (U.size()>>1);
}


int main() {
    int total = 0;
    while(cin >> n >> m) {
        memset(G, 0, sizeof G);
        memset(D, 0, sizeof D);

        for(int i=0; i<n; i++) {
            E[i].clear();
            S[i].clear();
        }
        
        for(int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            G[a][b] = G[b][a] = true;
            E[a].insert(i);
            E[b].insert(i);
            D[a]++;
            D[b]++;
        }

        for(int i=0; i<n; i++) {
            for(int j=0; j<2*m; j++) {
                S[i].insert(m+j);
            }
        }


        int next = 3*m;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if (E[i].find(j) != E[i].end())
                    S[i].insert(j);
                else
                    S[i].insert(next++);
            }            
        }
        cerr << ++total << " ";
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if (i!=j && G[i][j] != jaccard(S[i], S[j])) {
                    cerr << "ERROR ";
                    return 1;
                }
            }
        }
        cerr << endl;

    }
    return 0;
}
