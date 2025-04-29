#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

void initRc4(vector<int>& S, const vector<int>& K, int n) {
    int N = pow(2,n);  // 2^n
    S.resize(N);

    for (int i = 0; i < N; ++i) {
        S[i] = i;
    }

    int j = 0;
    for (int i = 0; i < N; ++i) {
        j = (j + S[i] + K[i % K.size()]) % N;
        swap(S[i], S[j]);
    }
}

vector<int> genRc4(const vector<int>& S_init, int n, int num_bytes) {
    int N = pow(2,n);  // 2^n
    vector<int> S = S_init;
    vector<int> output;
    output.reserve(num_bytes);

    int i = 0, j = 0;

    for (int count = 0; count < num_bytes; ++count) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(S[i], S[j]);
        int t = (S[i] + S[j]) % N;
        int K = S[t];
        output.push_back(K);
    }

    return output;
}

int main() {
    int n = 8;
    vector<int> K = {1, 2, 3, 4, 5}; // Пример ключа

    vector<int> S;
    initRc4(S, K, n);

    int num_bytes = 1;
    vector<int> keystream = genRc4(S, n, num_bytes);

    for (int byte : keystream) {
        cout << byte << " ";
    }
    cout << endl;

    return 0;
}
