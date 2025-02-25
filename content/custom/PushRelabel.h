/**
 * Author: Jan Gottweis
 * Date: 2025-01-17
 * License: CC0
 * Source: rewritten kactl
 * Description: Push-relabel using the highest label selection rule and the gap heuristic. Quite fast in practice.
 *  To obtain the actual flow, look at positive values only in g (.f). Edges are directed add both for undirected
 * Time: $O(V^2\sqrt E)$
 * Usage: flow.addEdge(a, b, c); flow.calc(s, t);
 * Status: Tested SPOJ, dmoj
 */
#pragma once

struct PushRelabel{
    struct edge {
        ll dest, back;
        ll f, c;
    };
    vec<vec<edge>> g;
    vec<ll>ec;
    vec<edge*>cur;
    vec<vec<ll>> hs; vec<ll> H;
    PushRelabel(ll n) : g(n), ec(n), cur(n), hs(2*n), H(n){}
    
    void addEdge(ll s, ll t, ll cap, ll rcap=0){
        if(s == t)return;
        g[s].push_back({t, sz(g[t]), 0, cap});
        g[t].push_back({s, sz(g[s])-1, 0, rcap});
    }
    void addFlow(edge&e, ll f){
        edge &back = g[e.dest][e.back];
        if(!ec[e.dest] && f)hs[H[e.dest]].push_back(e.dest);
        e.f+=f; e.c-=f;ec[e.dest]+=f;
        back.f -= f; back.c += f; ec[back.dest]-=f;
    }
    ll calc(ll s, ll t){
        ll v = sz(g); H[s] = v; ec[t] = 1;
        vec<ll> co(2*v);co[0]=  v-1;
        For(i, 0, v)cur[i] = g[i].data();
        for(auto& e: g[s])addFlow(e, e.c);

        for(ll hi = 0;;){
            while(hs[hi].empty())if(!hi--)return -ec[s];
            ll u = hs[hi].back(); hs[hi].pop_back();
            while(ec[u]>0){
                if(cur[u] == g[u].data()+sz(g[u])){
                    H[u] = 1e9;
                    for(auto& e:g[u])if(e.c && H[u] > H[e.dest] + 1){
                        H[u] = H[e.dest] + 1, cur[u] = &e;
                    }
                    if(++co[H[u]], !--co[hi] && hi<v){
                        For(i, 0, v) if(hi<H[i] && H[i] < v){
                            --co[H[i]], H[i] = v + 1;
                        }
                    }
                    hi = H[u];
                } else if( cur[u]->c && H[u] == H[cur[u]->dest] + 1){
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                } else ++cur[u];
            }
        }
    }
    bool leftOfMinCut(ll a){
        return H[a]>=sz(g);
    }
};