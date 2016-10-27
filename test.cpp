#include <iostream>
#include <vector>
#include <set>
using namespace std;

int T[100];
vector<set<int> > V;

bool test(int C, set<int> &X, set<int> &Y) {
    int count = 0;
    for(set<int>::iterator it = X.begin(); it != X.end(); it++) {
        if (Y.find(*it) != Y.end()) count++;
    }
    return count == C;
}

int backtrack(int A, int B, int C, int n, int k) {
    if (n==B) {
        set<int> X(T, T+n);
        for(int i=0; i<V.size(); i++) {
            if (!test(C, X, V[i]))
                return 0;
        }
        for(int i=0; i<n; i++) {
            cout << " " << T[i];
        }
        cout << endl;
        V.push_back(X);
        return 1;
    }
    
    int sum = 0;
    for(int i=k; i<A; i++) {
        T[n] = i+1;
        sum += backtrack(A, B, C, n+1, i+1);    
    }
    return sum;
}

int main() {
    
    for(int i=1; i<16; i*=2) {
        V.clear();
        cout << 5*i << " " << backtrack(4*i, 3*i, 2*i, 0, 0) << endl;
    }

}
