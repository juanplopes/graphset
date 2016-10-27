#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> G[1000];
int T[1000][1000];

int XX = 1;
bool V[1000];

void setNext(int k, int from, int to) {
    T[to][0] = 0;
    for(int i=0; i<k; i++) {
        int start = 1<<i;
        for(int j=0; j<start; j++) {
            if (to&(1<<(k-i-1)))
                T[to][start+j] = 1 - T[to][j];
            else
                T[to][start+j] = T[to][j];
        }
    }
    for(int i=1<<((k+1)-1); i>=0; i--) {
        int value = T[to][i];
        T[to][i*2 + value] = T[from][i*2 + value];
        T[to][i*2 + (1-value)] = 0;
    }
}

void dfs(int k, int level, int u, int v) {
    if (level == 0) {
        XX = 1;
        for(int i=0; i<(1<<(k+1)); i++)
            T[v][i] = XX++;
    } else if (level % 2 == 1) {
        setNext(k, u, v);
    } else {
        for(int i=0; i<(1<<(k+1)); i++)
            T[v][i] = T[u][i] != 0 ? T[u][i] : XX++;
    }
    
    for(int i=0; i<G[v].size(); i++) {
        if (G[v][i] != u)
            dfs(k, level+1, v, G[v][i]);
    }
}

int main() {
    int N, M;
    while(cin >> N >> M) {
        for(int i=0; i<M; i++) {
            int a, b; cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);        
        }
        
        int k = ceil(log(N)/log(2))-1;
        dfs(k, 0, -1, 0);
        
        for(int i=0; i<N; i++) {
            cout << i << ":";

            for(int j=0; j<(1<<(k+1)); j++) {
                if (T[i][j])
                    cout << " " << T[i][j];
            }
            
            cout << endl;
        }
    }
}
