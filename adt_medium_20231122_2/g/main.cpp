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

ll parent[3001];

// int find(int i)
// {
//     int cur = i;
//     while (parent[i] != cur)
//     {
//         cur = parent[i];
//     }
//     parent[i] = cur;
//     return cur;
// }

// void merge(int i, int j)
// {
//     int pi = find(i);
//     int pj = find(j);
//     if (pi < pj)
//     {
//         parent[pi] = pj;
//     }
//     else
//     {
//         parent[pj] = pi;
//     }
// }

bool is_connected(vll i, vll j)
{
    ll dist = (i[0] - j[0]) * (i[0] - j[0]) + (i[1] - j[1]) * (i[1] - j[1]);

    return dist >= (i[2] - j[2]) * (i[2] - j[2]) && dist <= (i[2] + j[2]) * (i[2] + j[2]);
}

int main()
{
    int n;
    cin >> n;
    pii s, t;
    cin >> s.first >> s.second >> t.first >> t.second;
    vector<vll> circles(n);
    dsu d(n);

    rep(i, n)
    {
        int x, y, r;
        cin >> x >> y >> r;
        circles[i] = {x, y, r};
    }
    int ps = INT_MAX;
    int pt = INT_MAX;
    rep(i, n)
    {
        parent[i] = i;
        if ((s.first - circles[i][0]) * (s.first - circles[i][0]) + (s.second - circles[i][1]) * (s.second - circles[i][1]) == circles[i][2] * circles[i][2])
        {
            ps = i;
        }
        if ((t.first - circles[i][0]) * (t.first - circles[i][0]) + (t.second - circles[i][1]) * (t.second - circles[i][1]) == circles[i][2] * circles[i][2])
        {
            pt = i;
        }
    }

    rep(i, n)
    {
        reps(j, i + 1, n)
        {
            if (is_connected(circles[i], circles[j]))
            {
                // printf("%d and %d are connected\n", i, j);
                d.merge(i, j);
            }
        }
    }
    // printf("ps %d, pt %d\n", ps, pt);
    // printf("pps %d, ppt %d\n", find(ps), find(pt));
    if (ps == INT_MAX || pt == INT_MAX)
    {
        print("No");
    }

    else if (d.same(ps, pt))
    {
        print("Yes");
    }
    else
    {
        print("No");
    }

    // code
    return 0;
}
