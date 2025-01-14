/**
 * Author: Jan Gottweis
 * Date: 2025-1-14
 * License: CC0
 * Source: n/a
 * Description: UPDATED minimum segment tree with point set update
 * can be modified easily
 * Time: O(\log N)
 * Usage: vec<ll>a; intervalac it = intervalac(a);
 * Status: sevaral simple tasks on cses and ksp/testovac
 */
#pragma once

class intervalac{
    vec<ll>h, z, k;
    ll velkost = 1;
    const ll base = 1e18; //change this
    ll f(ll a, ll b){ return min(a, b); } // change this
public:
    intervalac(vec<ll> a){
        ll n = a.size();
        while(velkost < n)velkost *=2;
        h.resize(2*velkost, base); z.resize(2*velkost); k.resize(2*velkost);
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
        if(l <= z[v] && k[v] <= r) return h[v];
        if(r <= z[v] || k[v] <= l) return base;
        return f(query(l, r, v*2), query(l, r, v*2+ 1)); 
    }
    void update(ll n, ll x){
        n += velkost;
        h[n] = x; // change this
        while(n>1){
            n/=2;
            h[n] = f(h[n*2], h[n*2+1]);
        }
    }
};
