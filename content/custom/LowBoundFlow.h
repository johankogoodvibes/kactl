/**
 * Author: Jan Gottweis
 * Date: 2025-01-20
 * License: CC0
 * Source: myself
 * Description: Computes minimal and maximal flow in graph g from s to t.
 *  Minimal flow is more time consuming. Not optimized for running time
 * Time: maxflow $O(1)$ minflow $O(log F)$ times flow 
 * Usage: g is vector<vector<dest, <min, max>>>
 * Status: Tested DMOJ squirrels
 */
#pragma once

#include "PushRelabel.h"

pll lowerBoundFlow(vec<vec<pair<ll, pll>>>&g, ll s, ll t){
    ll n = sz(g);
    ll ns = n, nt = n+1;
    PushRelabel base = PushRelabel(n + 2);
    vec<ll> O(n), I(n);
    For(i, 0, n){
        for(auto [to, c]:g[i]){
            O[i] += c.first;
            I[to] += c.first;
            base.addEdge(i, to, c.second - c.first);
        }
    }
    ll bound_sum = 0;
    For(i, 0, n){
        bound_sum += I[i];
        base.addEdge(ns, i, I[i]);
        base.addEdge(i, nt, O[i]);
    }
    PushRelabel flow1 = base;
    flow1.addEdge(t, s, inf);
    
    assert(flow1.calc(ns, nt) == bound_sum); // no feasible flow
    
    // this is for max possible flow
    map<pll, ll> flows;
    For(i, 0, sz(flow1.g)){
        for(auto e:flow1.g[i]){
            flows[{i, e.dest}] = e.f;            
        }
    }
    PushRelabel flow2 = PushRelabel(n);
    For(i, 0, n){
        for(auto [to, c]:g[i]){
            flow2.addEdge(i, to, c.second - c.first - flows[{i, to}], flows[{i, to}]);
        }
    }
    ll most = flow2.calc(s, t) + flows[{t, s}];

    // this is for min possible flow
    ll lo = -1, hi = inf;
    while(hi-lo>1){
        ll mid = (lo + hi)/2;
        PushRelabel flow3 = base;
        flow3.addEdge(t, s, mid);
        if(flow3.calc(ns, nt)<bound_sum)lo = mid;
        else hi = mid;
    }
    ll least = lo + 1;
    return {least, most};
}