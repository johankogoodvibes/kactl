/**
 * Author: Jan Gottweis
 * Date: 2025-1-18
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: good for bipartite matching (has the sqrt complexity), obtain flow with edge.flow()
 * Time: $O(VE\log U)$
 * Usage: flow.addEdge(a, b, c); flow.calc(s, t);
 * Status: Tested on cf captain america, dmoj squirrels
 */
#pragma once

struct Dinic{
    struct edge{
        ll dest, back, c, oc;
        ll flow(){return max(oc-c, 0ll);}
    };
    vec<ll>lvl, ptr, q;
    vec<vec<edge>>g;
    Dinic(ll n) : lvl(n), ptr(n), q(n), g(n){}
    void addEdge(ll s, ll t, ll cap, ll rcap = 0){
        g[s].push_back({t, sz(g[t]), cap, cap});
        g[t].push_back({s, sz(g[s])-1, rcap, rcap});
    }
    ll dfs(ll v, ll t, ll f){
        if(v == t || !f)return f;
        for(ll& i=ptr[v];i<sz(g[v]);i++){
            edge&e = g[v][i];
            if(lvl[e.dest] == lvl[v] + 1){
                if(ll p = dfs(e.dest, t, min(f, e.c))){
                    e.c-=p;g[e.dest][e.back].c += p;
                    return p;
                }
            }
        }
        return 0;
    }
    ll calc(ll s, ll t){
        ll flow = 0; q[0] = s;
        For(L, 0, 31) do{
            lvl = ptr = vec<ll>(sz(q));
            ll qi = 0, qe = lvl[s] = 1;
            while(qi<qe && !lvl[t]){
                ll v = q[qi++];
                for(edge e: g[v]){
                    if(!lvl[e.dest] && e.c >>(30-L)){
                        q[qe++] = e.dest, lvl[e.dest] = lvl[v] + 1;
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
