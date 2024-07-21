#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<vector<bool>> edge(n, vector<bool>(n, false));
    while (true) {
        int a, b;
        cin >> a >> b;
        if (a == -1 && b == -1) break;
        a--, b--;
        edge[a][b] = true;
        edge[b][a] = true;
    }
    // 자기 자신과의 간선은 항상 true로 설정
    for (int i = 0; i < n; i++) {
        edge[i][i] = true;
    }

    // 색칠을 위한 배열 초기화
    vector<int> color(n, -1);

    // 이분 그래프 만들기
    function<void(int, int)> makeBipartite = [&](int now, int toColor) {
        color[now] = toColor;

        for (int nxt = 0; nxt < n; nxt++) {
            // 서로 아는 사이이면 넘어감
            if (edge[now][nxt]) continue;

            // 모르는 사이이고 색칠되지 않았다면 다른 팀에 배정
            if (color[nxt] == -1) makeBipartite(nxt, 1 - toColor);
            // 모르는 사이이고 이미 다른 팀에 배정되었다면 무시
            else if (color[nxt] != toColor)
                continue;
            // 모르는 사이인데 같은 팀이면 에러
            else if (color[nxt] == toColor) {
                cout << -1;
                exit(0);
            }
        }
    };

    // 모든 노드에 대해 색칠 시도
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            makeBipartite(i, 0);
        }
    }

    // 출력
    cout << 1 << '\n';
    vector<vector<int>> ans(2);
    for (int i = 0; i < n; i++) {
        ans[color[i]].push_back(i + 1);
    }
    for (auto v : ans) {
        for (auto i : v) cout << i << ' ';
        cout << -1 << '\n';
    }

    return 0;
}