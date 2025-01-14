/**
 * Author: Jan Gottweis
 * Date: 2025-1-14
 * License: CC0
 * Source: me
 * Description: UPDATED min segment tree, substract value query can be changed easily
 * Time: O(\log N).
 * Usage: vec<ll>a; intervalac it = intervalac(a);
 * Status: some simple tasks on cses and testovac/ksp
 */
#pragma once

class intervalac{
    vec<ll> h, z, k;
    vec<ll> d;
    ll velkost = 1;
    const ll base = 1e18; //change this
    const ll based = 0; //change this
    ll f(ll a, ll b){ return min(a, b); } // change this

    void propagate(ll v){
        if(d[v] == based)return;
        h[v] += d[v]; //change this
        if(v < velkost){
            d[v*2] += d[v]; // change this
            d[v*2 + 1] += d[v]; // change this
        }
        d[v] = based;
    }
public:
    intervalac(vec<ll> a){
        ll n = a.size();
        while(velkost < n)velkost *=2;
        h.resize(2*velkost, base); z.resize(2*velkost); k.resize(2*velkost);
        d.resize(2*velkost, based);
        For(i, 0, velkost){
            if(i<n) h[i + velkost] = a[i];
            z[i + velkost] = i;
            k[i + velkost] = i + 1;
        }
        for(ll i = velkost - 1; i > 0; i--){
            h[i] = f(h[i*2], h[i*2+1]);
            z[i] = z[i*2];
            k[i] = k[i*2+1];
        }
    }
 
    ll query(ll l, ll r, ll v = 1){
        propagate(v);
        if(l <= z[v] && k[v] <= r) return h[v];
        if(r <= z[v] || k[v] <= l) return base;
        return f(query(l, r, v*2), query(l, r, v*2+ 1)); 
    }
    void update(ll l, ll r, ll x, ll v = 1){
        if(l <= z[v] && k[v] <= r) {
            d[v] -= x; //change this
            propagate(v); //needs to be here!!!
            return;
        }
        if(r <= z[v] || k[v] <= l) return;
        propagate(v);
        update(l, r, x, v*2); update(l, r, x, v*2+1);
        h[v] = f(h[v*2], h[v*2+1]);
    }
};
