/**
 *    author: insectkorea
 *    create-mm-dd hh:mm:ss
 **/

#include <bits/stdc++.h>
using namespace std;

struct Fast
{
    Fast()
    {
        std::cin.tie(0);
        ios::sync_with_stdio(false);
    }
} fast;

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
#define YESNO(bool)            \
    if (bool)                  \
    {                          \
        cout << "YES" << endl; \
    }                          \
    else                       \
    {                          \
        cout << "NO" << endl;  \
    }
#define yesno(bool)            \
    if (bool)                  \
    {                          \
        cout << "yes" << endl; \
    }                          \
    else                       \
    {                          \
        cout << "no" << endl;  \
    }
#define YesNo(bool)            \
    if (bool)                  \
    {                          \
        cout << "Yes" << endl; \
    }                          \
    else                       \
    {                          \
        cout << "No" << endl;  \
    }

/* REP macro */
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); ++i)
#define rep(i, n) reps(i, 0, n)
#define rrep(i, n) reps(i, 1, n + 1)
#define repd(i, n) for (ll i = n - 1; i >= 0; i--)
#define rrepd(i, n) for (ll i = n; i >= 1; i--)

template <typename T>
inline bool vector_finder(std::vector<T> vec, T element, unsigned int search_length)
{
    auto itr = std::find(vec.begin(), vec.end(), element);
    size_t index = std::distance(vec.begin(), itr);
    if (index == vec.size() || index >= search_length)
    {
        return false;
    }
    else
    {
        return true;
    }
}
template <typename T>
inline void print(const vector<T> &v, string s = " ")
{
    rep(i, v.size()) cout << v[i] << (i != (ll)v.size() - 1 ? s : "\n");
}
template <typename T, typename S>
inline void print(const pair<T, S> &p)
{
    cout << p.first << " " << p.second << endl;
}
template <typename T>
inline void print(const T &x) { cout << x << "\n"; }
template <typename T, typename S>
inline void print(const vector<pair<T, S>> &v)
{
    for (auto &&p : v)
        print(p);
}

int main()
{

    int n;
    cin >> n;
    vector<int> dp(n + 1);
    vector<int> before(n + 1);
    before[1] = 1;

    reps(i, 2, n + 1)
    {
        dp[i] = dp[i - 1] + 1;
        before[i] = i - 1;
        if (i % 3 == 0)
        {
            if (dp[i / 3] + 1 < dp[i])
            {
                dp[i] = dp[i / 3] + 1;
                before[i] = i / 3;
            }
        }
        if (i % 2 == 0)
        {
            if (dp[i / 2] + 1 < dp[i])
            {
                dp[i] = dp[i / 2] + 1;
                before[i] = i / 2;
            }
        }
    }
    print(dp[n]);
    if (n != 0)
    {
        cout << n << ' ';
    }
    while (n != 1)
    {
        n = before[n];
        cout << n << ' ';
    }

    // code
    return 0;
}
