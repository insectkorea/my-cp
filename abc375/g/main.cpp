#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

struct Road {
    int A, B;
    ll C;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<Road> roads(M + 1);
    vector<vector<pair<int, ll>>> adj1(N + 1, vector<pair<int, ll>>());
    vector<vector<pair<int, ll>>> adjN(N + 1, vector<pair<int, ll>>());
    for (int i = 1; i <= M; i++) {
        cin >> roads[i].A >> roads[i].B >> roads[i].C;
        adj1[roads[i].A].emplace_back(roads[i].B, roads[i].C);
        adj1[roads[i].B].emplace_back(roads[i].A, roads[i].C);
        adjN[roads[i].A].emplace_back(roads[i].B, roads[i].C);
        adjN[roads[i].B].emplace_back(roads[i].A, roads[i].C);
    }

    // Dijkstra from 1
    vector<ll> dist1(N + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>,
                   std::greater<pair<ll, int>>>
        pq;
    dist1[1] = 0;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist1[u]) continue;
        for (auto &[v, c] : adj1[u]) {
            if (dist1[v] > dist1[u] + c) {
                dist1[v] = dist1[u] + c;
                pq.emplace(dist1[v], v);
            }
        }
    }

    // Dijkstra from N
    vector<ll> distN(N + 1, INF);
    distN[N] = 0;
    pq.emplace(0, N);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > distN[u]) continue;
        for (auto &[v, c] : adjN[u]) {
            if (distN[v] > distN[u] + c) {
                distN[v] = distN[u] + c;
                pq.emplace(distN[v], v);
            }
        }
    }

    ll D = dist1[N];
    // Build DAG and Reverse DAG
    vector<vector<int>> DAG(N + 1, vector<int>());
    vector<vector<int>> reverse_DAG(N + 1, vector<int>());
    // Flags for each road
    vector<bool> on_dag1(M + 1, false);
    vector<bool> on_dag2(M + 1, false);
    for (int i = 1; i <= M; i++) {
        int u = roads[i].A;
        int v = roads[i].B;
        ll c = roads[i].C;
        if (dist1[u] + c == dist1[v]) {
            on_dag1[i] = true;
            DAG[u].push_back(v);
            reverse_DAG[v].push_back(u);
        }
        if (dist1[v] + c == dist1[u]) {
            on_dag2[i] = true;
            DAG[v].push_back(u);
            reverse_DAG[u].push_back(v);
        }
    }

    // Compute dp1
    vector<ll> dp1(N + 1, 0);
    dp1[1] = 1;
    // Sort nodes by dist1 ascending
    vector<int> order1(N);
    for (int i = 1; i <= N; i++) order1[i - 1] = i;
    sort(order1.begin(), order1.end(),
         [&](const int a, const int b) -> bool { return dist1[a] < dist1[b]; });
    for (auto u : order1) {
        for (auto &[v, c] : adj1[u]) {
            if (dist1[u] + c == dist1[v]) {
                dp1[v] += dp1[u];
            }
        }
    }

    // Compute dp2
    vector<ll> dp2(N + 1, 0);
    dp2[N] = 1;
    // Sort nodes by dist1 descending
    sort(order1.begin(), order1.end(),
         [&](const int a, const int b) -> bool { return dist1[a] > dist1[b]; });
    for (auto u : order1) {
        for (auto &[v, c] : adjN[u]) {
            if (dist1[v] + c == dist1[u]) {
                dp2[v] += dp2[u];
            }
        }
    }

    ll total_paths = dp1[N];
    // Prepare for output
    vector<string> results(M + 1, "No");
    for (int i = 1; i <= M; i++) {
        int A = roads[i].A, B = roads[i].B;
        ll C = roads[i].C;
        if (dist1[A] + C == dist1[B]) {
            if (dp1[A] * dp2[B] == total_paths) {
                results[i] = "Yes";
            }
        }
        if (dist1[B] + C == dist1[A]) {
            if (dp1[B] * dp2[A] == total_paths) {
                results[i] = "Yes";
            }
        }
    }

    for (int i = 1; i <= M; i++) cout << results[i] << "\n";
}
