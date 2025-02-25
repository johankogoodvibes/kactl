/**
 * Author: Jan Gottweis
 * Date: 2025-1-14
 * License: CC0
 * Source: me
 * Description: min lazy sparse segment tree, substract value range query can be changed easily
 * Time: O(\log N).
 * Usage: Node* it = new Node(n, fill); add export ASAN_OPTIONS=detect_leaks=0 to .bashrc
 * Status: some simple tasks on cses and testovac/ksp
 */
class Node{
    const ll base = 1e18; //change this
    const ll based = 0; //change this
    ll f(ll a, ll b){ return min(a, b); } //change this
    Node* left=0, *right =0;
    ll z, k, h=base, d = based, fill;
    void propagate(){
        if(z+1<k){
            ll mid = (k + z)/2;
            if(!left) left = new Node(z, mid, fill);
            if(!right) right = new Node(mid, k, fill);
        }
        if(d == based) return;
        h += d; //change this
        if(z+1<k){
            left->d += d; //change this
            right->d += d; //change this
        }
        d = based;
    }
    Node(ll lo, ll hi, ll fill):z(lo), k(hi), fill(fill), h(fill) {}
public:
    Node(ll n, ll fill) : fill(fill) { // vytvorim root
        ll velkost = 1;while(velkost<n)velkost*=2;
        z = 0; k = velkost;
        h = fill;
    }
    ll query(ll l, ll r){
        propagate();
        if(l <= z && k <= r) return h;
        if(r <= z || k <= l) return base;
        return f(left->query(l, r), right->query(l, r));
    }
    void update(ll l, ll r, ll x){
        if(l <= z && k <= r){
            d -= x; //change this
            propagate();
            return;
        }
        if(r <= z || k <= l)return;
        propagate();
        left->update(l, r, x); right->update(l, r, x);
        h = f(left->h, right->h);
    }
};