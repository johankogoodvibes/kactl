/**
 * Author: Jan Gottweis
 * Date: 2025-1-18
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: good for bipartite matching (has the sqrt complexity), obtain flow with edge.flow()
 * Time: $O(VE\log U)$
 * Usage: flow.addEdge(a, b, c); flow.calc(s, t);
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING
 */
#pragma once

struct Dinic{
    struct edge{
        ll to, rev, c, oc;
        ll flow(){ return max(oc - c, 0LL); }
    };
    vec<ll> lvl, ptr, q;
    vec<vec<edge>>adj;
    Dinic(ll n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(ll a, ll b, ll c, ll rcap = 0){
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
    }
    ll dfs(ll v, ll t, ll f){
        if(v == t || !f) return f;
        for(ll& i= ptr[v]; i<sz(adj[v]);i++){
            edge& e = adj[v][i];
            if(lvl[e.to] == lvl[v] + 1){
                if(ll p = dfs(e.to, t, min(f, e.c))){
                    e.c-=p, adj[e.to][e.rev].c += p;
                    return p;
                }
            }
        }
        return 0;
    }
    ll calc(ll s, ll t){
        ll flow = 0;q[0] = s;
        For(L, 0, 31) do{
            lvl = ptr = vec<ll>(sz(q));
            ll qi = 0, qe = lvl[s] = 1;
            while(qi < qe && !lvl[t]){
                ll v = q[qi++];
                for(edge e : adj[v]){
                    if(!lvl[e.to] && e.c >> (30 - L)){
                        q[qe++] = e.to, lvl[e.to]= lvl[v] + 1;
                    }
                }
            }
            while(ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while(lvl[t]);
        return flow;
    }
    bool leftOfMinCut(ll a){
        return lvl[a]!=0;
    }
};
