#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    vector<vector<int>> pos(n + 1);
    for (int i = 0; i < n; i++) pos[a[i]].push_back(i + 1);
    ll total = (n * (n + 1)) / 2;
    ll ans = 0;
    for (int x = 1; x <= n; x++) {
        if (pos[x].empty()) continue;
        ll cnt = 0;
        int prev = 0;
        for (auto p : pos[x]) {
            ll l = p - prev - 1;
            cnt += (l * (l + 1)) / 2;
            prev = p;
        }
        ll l = n - prev;
        cnt += (l * (l + 1)) / 2;
        ans += total - cnt;
    }
    cout << ans << endl;
}
