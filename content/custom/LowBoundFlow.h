/**
 * Author: Jan Gottweis
 * Date: 2025-01-20
 * License: CC0
 * Source: myself
 * Description: Computes minimal and maximal flow in graph g from s to t. Not optimized running time.
 *  Might want to use PushRelabel if it is slow, take care with maxflow then.
 * Time: $O(1)$ runs of flow 
 * Usage: g is vector<vector<dest, <min, max>>>
 * Status: Tested DMOJ squirrels, cf captain america, need to test least flow calculation
 */
#pragma once

#include "Dinic.h"

pll lowerBoundFlow(vec<vec<pair<ll, pll>>>&g, ll s, ll t){
    ll n = sz(g);
    ll ns = n, nt = n+1;
    Dinic base = Dinic(n + 2);
    vec<ll> O(n), I(n);
    For(i, 0, n){
        for(auto [to, c]:g[i]){
            assert(c.first <= c.second); // no feasible flow
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
    Dinic flow1 = base;
    flow1.addEdge(t, s, inf);    
    assert(flow1.calc(ns, nt) == bound_sum); // no feasible flow
    ll most = flow1.calc(s, t);
    Dinic flow3 = base; ll least = bound_sum - flow3.calc(ns, nt);
    return {least, most};
}
