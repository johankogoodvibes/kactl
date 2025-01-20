/**
 * Author: Jan Gottweis
 * Date: 2025-01-20
 * Source: Stanford Notebook, kactl
 * Description: Min-cost max-flow.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  Note that setpi works for general graphs, for more concrete restrictions you might want to implement faster approach.
 *  To obtain the actual flow, look at positive values of .flow only. pi - least cost to get to vertex
 * Status: copied from kactl, tested on cf Four Melodies
 * Time: $O(F E \log(V))$ where F is max flow. $O(VE)$ for setpi - this might be too slow!
 */
#pragma once

// #include <bits/extc++.h> /// include-line, keep-include

#define inf (ll)1e18

struct MCMF{
    struct edge{
        ll from, to, rev, cap, cost, flow;
    };
    ll n;
    vec<vec<edge>> g;
    vec<ll> seen;
    vec<ll> dist, pi;
    vec<edge*>par;

    MCMF(ll n): n(n), g(n), seen(n), dist(n), pi(n), par(n) {}
    void addEdge(ll from, ll to, ll cap, ll cost){
        if(from == to)return;
        // dbg(from, to, cap, cost);
        g[from].push_back({from, to, sz(g[to]), cap, cost, 0});
        g[to].push_back({to, from, sz(g[from]) - 1, 0, - cost, 0});
    }
    void path(ll s){
        fill(all(seen), 0);
        fill(all(dist), inf);
        dist[s] = 0;ll di;

        __gnu_pbds::priority_queue<pll> q;
        vec<decltype(q)::point_iterator> its(n);
        q.push({0, s});

        while(!q.empty()){
            s= q.top().second;q.pop();
            seen[s] = 1; di = dist[s] + pi[s];
            for(edge& e : g[s]) if(!seen[e.to]){
                ll val = di - pi[e.to] + e.cost;
                if(e.cap - e.flow > 0 && val < dist[e.to]){
                    dist[e.to] = val;
                    par[e.to] = &e;
                    if(its[e.to] == q.end())
                        its[e.to] = q.push({-dist[e.to], e.to});
                    else 
                        q.modify(its[e.to], {-dist[e.to], e.to});
                }
            }
        }
        For(i, 0, n)pi[i] = min(pi[i] + dist[i], inf);
    }
    pll calc(ll s, ll t){
        ll totflow = 0, totcost = 0;
        while(path(s), seen[t]){
            ll fl = inf;
            for(edge* x = par[t];x;x=par[x->from]){
                fl = min(fl, x->cap - x->flow);
            }

            totflow += fl;
            for(edge*x=par[t];x;x=par[x->from]){
                x->flow += fl;
                g[x->to][x->rev].flow -= fl;
            }
        }
        For(i, 0, n) for(edge& e: g[i]) totcost += e.cost * e.flow;
        return {totflow, totcost / 2};
    }
    // If some costs can be negative , call this before maxflow:
    void setpi(ll s) { // (otherwise, leave this out)
        fill(all(pi), inf); pi[s] = 0;
        ll it = n, ch = 1, v;
        while(ch--&&it--){
            For(i, 0, n) if(pi[i]!=inf){
                for(edge& e : g[i]) if(e.cap){
                    if((v=pi[i] + e.cost) < pi[e.to]) pi[e.to] = v, ch = 1;
                }
            }
        }
        assert(it>=0); // negative cost cycle;
    }
};
