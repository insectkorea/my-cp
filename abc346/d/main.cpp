#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    string S;
    cin >> S;
    // Read C[1..N]
    vector<ll> C(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> C[i];
    }

    // Precompute prefix0 and prefix1
    // prefix0[j]: cost to make S[1..j] alternate starting with '0'
    // prefix1[j]: cost to make S[1..j] alternate starting with '1'
    vector<ll> prefix0(N + 1, 0);
    vector<ll> prefix1(N + 1, 0);
    for (int j = 1; j <= N; ++j) {
        char expected0 = (j % 2 == 1) ? '0' : '1';
        char expected1 = (j % 2 == 1) ? '1' : '0';
        prefix0[j] = prefix0[j - 1] + (S[j - 1] != expected0 ? C[j] : 0);
        prefix1[j] = prefix1[j - 1] + (S[j - 1] != expected1 ? C[j] : 0);
    }

    // Precompute suffix0 and suffix1
    // suffix0[j]: cost to make S[j..N] alternate starting with '0'
    // suffix1[j]: cost to make S[j..N] alternate starting with '1'
    vector<ll> suffix0(N + 2, 0);  // suffix0[N+1] =0
    vector<ll> suffix1(N + 2, 0);  // suffix1[N+1] =0
    for (int j = N; j >= 1; --j) {
        // Starting with '0'
        char expected0 = ((j % 2) == 1) ? '0' : '1';
        char expected1 = ((j % 2) == 1) ? '1' : '0';
        suffix0[j] = (S[j - 1] != '0' ? C[j] : 0) + suffix1[j + 1];
        suffix1[j] = (S[j - 1] != '1' ? C[j] : 0) + suffix0[j + 1];
    }

    ll min_cost = INF;
    for (int i = 1; i <= N - 1; ++i) {
        // For c = '0' and '1'
        for (char c : {'0', '1'}) {
            ll cost_prefix = INF;
            if (c == '0') {
                if ((i - 1) % 2 == 0) {
                    // (i-1) even: use prefix0[i-1]
                    cost_prefix = prefix0[i - 1];
                } else {
                    // (i-1) odd: use prefix1[i-1]
                    cost_prefix = prefix1[i - 1];
                }
            } else {  // c == '1'
                if ((i - 1) % 2 == 1) {
                    // (i-1) odd: use prefix0[i-1]
                    cost_prefix = prefix0[i - 1];
                } else {
                    // (i-1) even: use prefix1[i-1]
                    cost_prefix = prefix1[i - 1];
                }
            }
            // Cost_suffix
            ll cost_suffix = 0;
            if (i + 2 <= N) {
                if (c == '0') {
                    // Suffix must start with '1'
                    cost_suffix = suffix1[i + 2];
                } else {
                    // c == '1', suffix starts with '0'
                    cost_suffix = suffix0[i + 2];
                }
            }
            // Cost to set T[i] and T[i+1] to c
            ll cost_flip = 0;
            if (S[i - 1] != c) {
                cost_flip += C[i];
            }
            if (S[i] != c) {
                cost_flip += C[i + 1];
            }
            // Total cost
            ll total_cost = cost_prefix + cost_flip + cost_suffix;
            min_cost = min(min_cost, total_cost);
        }
    }
    cout << min_cost << endl;
}
