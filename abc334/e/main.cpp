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
const int MOD = 998244353;
using mint = modint998244353;

int H, W;
vector<vector<char>> grid;
vector<vector<bool>> visited;
dsu D;

void dfs(int i, int j)
{
    if (i < 0 || i >= H || j < 0 || j >= W || grid[i][j] == '.' || visited[i][j])
        return;
    visited[i][j] = true;

    dfs(i + 1, j);
    dfs(i - 1, j);
    dfs(i, j + 1);
    dfs(i, j - 1);
}

int cellIndex(int i, int j)
{
    return i * W + j;
}

int countGreenComponents()
{
    visited.assign(H, vector<bool>(W, false));
    int count = 0;
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (grid[i][j] == '#' && !visited[i][j])
            {
                dfs(i, j);
                ++count;
            }
        }
    }
    return count;
}

bool isAdjacentGreen(int i, int j)
{
    if (i > 0 && grid[i - 1][j] == '#')
        return true;
    if (j > 0 && grid[i][j - 1] == '#')
        return true;
    if (i < H - 1 && grid[i + 1][j] == '#')
        return true;
    if (j < W - 1 && grid[i][j + 1] == '#')
        return true;
    return false;
}

int main()
{
    cin >> H >> W;
    grid.resize(H, vector<char>(W));
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            cin >> grid[i][j];
        }
    }
    D = dsu(H * W);
    int redCount = 0;

    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            if (grid[i][j] == '#')
            {
                if (i + 1 < H && grid[i + 1][j] == '#')
                    D.merge(cellIndex(i, j), cellIndex(i + 1, j));
                if (j + 1 < W && grid[i][j + 1] == '#')
                    D.merge(cellIndex(i, j), cellIndex(i, j + 1));
                if (i > 0 && grid[i - 1][j] == '#')
                    D.merge(cellIndex(i, j), cellIndex(i - 1, j));
                if (j > 0 && grid[i][j - 1] == '#')
                    D.merge(cellIndex(i, j), cellIndex(i, j - 1));
            }
            else
            {
                redCount++;
            }

    int initialGreenComponents = D.groups().size() - redCount;
    mint total = 0;
    int redCells = 0;

    rep(i, H)
    {
        rep(j, W)
        {
            if (grid[i][j] == '.')
            {
                // debug(initialGreenComponents);
                redCells++;
                set<int> adjComponents;
                if (i > 0 && grid[i - 1][j] == '#')
                    adjComponents.insert(D.leader(cellIndex(i - 1, j)));
                if (j > 0 && grid[i][j - 1] == '#')
                    adjComponents.insert(D.leader(cellIndex(i, j - 1)));
                if (i < H - 1 && grid[i + 1][j] == '#')
                    adjComponents.insert(D.leader(cellIndex(i + 1, j)));
                if (j < W - 1 && grid[i][j + 1] == '#')
                    adjComponents.insert(D.leader(cellIndex(i, j + 1)));
                total += initialGreenComponents - (adjComponents.size() - 1);
            }
        }
    }

    if (redCells > 0)
    {
        total /= (mint)redCells;
    }

    print(total.val());
    return 0;
}