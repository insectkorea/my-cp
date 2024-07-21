/**
 *    author: insectkorea
 *    create-mm-dd hh:mm:ss
 **/

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

// clang-format off
/* accelration */
// 高速バイナリ生成
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
// cin cout の結びつけ解除, stdioと同期しない(入出力非同期化)
// cとstdの入出力を混在させるとバグるので注意
struct Fast {Fast() {std::cin.tie(0); ios::sync_with_stdio(false);}} fast;

/* alias */
using ull = unsigned long long;
using ll = long long;
using vi = vector<int>;
using vl = vector<long>;
using vll = vector<long long>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vvll = vector<vll>;
using vs = vector<string>;
using pii = pair<int, int>;

/* define short */
#define pb push_back
#define mp make_pair
#define all(obj) (obj).begin(), (obj).end()
#define YESNO(bool) if(bool){cout<<"YES"<<endl;}else{cout<<"NO"<<endl;}
#define yesno(bool) if(bool){cout<<"yes"<<endl;}else{cout<<"no"<<endl;}
#define YesNo(bool) if(bool){cout<<"Yes"<<endl;}else{cout<<"No"<<endl;}

/* REP macro */
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); ++i)
#define rep(i, n) reps(i, 0, n)
#define rrep(i, n) reps(i, 1, n + 1)
#define repd(i,n) for(ll i=n-1;i>=0;i--)
#define rrepd(i,n) for(ll i=n;i>=1;i--)

/* debug */
// 標準エラー出力を含む提出はrejectされる場合もあるので注意
#define debug(x) cerr << "\033[33m(line:" << __LINE__ << ") " << #x << ": " << x << "\033[m" << endl;

/* func */
inline int in_int() {int x; cin >> x; return x;}
inline ll in_ll() {ll x; cin >> x; return x;}
inline string in_str() {string x; cin >> x; return x;}
// search_length: 走査するベクトル長の上限(先頭から何要素目までを検索対象とするか、1始まりで)
template <typename T> inline bool vector_finder(std::vector<T> vec, T element, unsigned int search_length) {
    auto itr = std::find(vec.begin(), vec.end(), element);
    size_t index = std::distance( vec.begin(), itr );
    if (index == vec.size() || index >= search_length) {return false;} else {return true;}
}
template <typename T> inline void print(const vector<T>& v, string s = " ")
    {rep(i, v.size()) cout << v[i] << (i != (ll)v.size() - 1 ? s : "\n");}
template <typename T, typename S> inline void print(const pair<T, S>& p)
    {cout << p.first << " " << p.second << endl;}
template <typename T> inline void print(const T& x) {cout << x << "\n";}
template <typename T, typename S> inline void print(const vector<pair<T, S>>& v)
    {for (auto&& p : v) print(p);}
// 第一引数と第二引数を比較し、第一引数(a)をより大きい/小さい値に上書き
template <typename T> inline bool chmin(T& a, const T& b) {bool compare = a > b; if (a > b) a = b; return compare;}
template <typename T> inline bool chmax(T& a, const T& b) {bool compare = a < b; if (a < b) a = b; return compare;}
// gcd lcm
// C++17からは標準実装
// template <typename T> T gcd(T a, T b) {if (b == 0)return a; else return gcd(b, a % b);}
// template <typename T> inline T lcm(T a, T b) {return (a * b) / gcd(a, b);}
// clang-format on

vi dx = {1, 0, -1, 0};
vi dy = {0, 1, 0, -1};
int main()
{
    // code
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    rep(i, n) cin >> grid[i];
    // n + m + s + t
    mf_graph<int> graph(n * m + 2);
    int s = n * m, t = n * m + 1;

    auto index = [&](int i, int j) -> int
    { return i * m + j; };

    rep(i, n)
    {
        rep(j, m)
        {
            if ((i + j) % 2 == 0)
            {
                rep(dir, 4)
                {
                    // black to white
                    int i2 = i + dx[dir], j2 = j + dy[dir];
                    if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= m)
                        continue;
                    if (grid[i][j] == '.' && grid[i2][j2] == '.')
                        graph.add_edge(index(i, j), index(i2, j2), 1);
                }
            }
            // s to black
            if ((i + j) % 2 == 0 && grid[i][j] == '.')
                graph.add_edge(s, index(i, j), 1);
            // white to t
            if ((i + j) % 2 == 1 && grid[i][j] == '.')
                graph.add_edge(index(i, j), t, 1);
        }
    }

    int max_flow = graph.flow(s, t);

    const auto &edges = graph.edges();
    for (const auto &edge : edges)
    {
        if (edge.from == s || edge.to == t || edge.flow == 0)
            continue;
        int ifrom = edge.from / m, jfrom = edge.from % m;
        int ito = edge.to / m, jto = edge.to % m;

        if (ifrom == ito)
        {
            if (jfrom > jto)
                swap(jfrom, jto);
            grid[ifrom][jfrom] = '>';
            grid[ito][jto] = '<';
        }
        else
        {
            if (ifrom > ito)
                swap(ifrom, ito);
            grid[ifrom][jfrom] = 'v';
            grid[ito][jto] = '^';
        }
    }
    print(max_flow);
    for (int i = 0; i < n; i++)
    {
        print(grid[i]);
    }
    return 0;
}
