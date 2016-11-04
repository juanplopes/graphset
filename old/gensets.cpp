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
    /*for(int i=1; i<15; i++) {
        for(int j=1; j<i; j++) {
            for(int k=1; k<j; k++) {
                V.clear();
                int a = backtrack(i, j, k, 0, 0);
                V.clear();
                int b = backtrack(2*i, 2*j, 2*k, 0, 0);
//                V.clear();
//                int c = backtrack(4*i, 4*j, 4*k, 0, 0);
                if (b>a)
                    cout << i << " " << j << " " << k << ": " << a << "->" << b << "->" << endl;
            }
        }
    }*/
    
    for(int i=1; i<10; i*=2) {
        cout << i << " " << backtrack(12*i, 7*i, 3*i, 0, 0) << endl;
    }
    
}
