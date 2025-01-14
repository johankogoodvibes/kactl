#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

#define For(i, a, n) for (ll i = a; i < (ll) n; i++)
#define vec vector
#define all(x) begin(x), end(x)
#define endl "\n"

template<class A, class B>
pair<A, B> operator+(const pair<A, B>& a, const pair<A, B>& b){
    return {a.first + b.first, a.second + b.second};
}

template<class A, class B>
ostream& operator<<(ostream& os, const pair<A, B>& a){
    return os << "(" << a.first << ", " << a.second << ")";
}

template<class A, class B, class C>
basic_ostream<A, B>& operator<<(basic_ostream<A, B>& os, const C& c){
    for(auto it = begin(c); it != end(c); ++it){
        os << (it == begin(c) ? "" : " ") << *it;
    }
    return os;
}

template<typename... Args>
void dbg(Args&&... args){
    ((cerr << args << " |"),...);
    cerr << endl;
}

void solve(){
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll t = 1;//cin>>t ;
    while(t--){
        solve();
    }
}