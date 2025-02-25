/**
 * Author: Jan Gottweis
 * Date: 2025-1-13
 * License: CC0
 * Source: N/A
 * Description: g is of size $|A|$, contains neighbors in B (numbers in $0,...,|B|$) 
 * $btoa$ should be a vector full of -1's of size $|B|$. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Usage: vec<ll> btoa(m, -1); hopcroftKarp(g, btoa);
 * Time: O(\sqrt{V}E)
 * Status: testd on codeforces
 */
#pragma once

bool dfs(ll a, ll L, vec<vec<ll>>&g, vec<ll>& btoa, vec<ll>& A, vec<ll>& B){
    if(A[a]!=L)return 0;
    A[a] = -1;
    for(ll b : g[a]) if(B[b] == L + 1){
        B[b] = 0;
        if(btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B)){
            return btoa[b] = a, 1;
        }
    }
    return 0;
}

ll matching(vec<vec<ll>>& g, vec<ll>& btoa){
    ll res = 0;
    vec<ll> A(sz(g)), B(sz(btoa)), cur, next;
    for(;;){
        fill(all(A), 0);
        fill(all(B), 0);
        cur.clear();
        for(ll a : btoa)if(a != -1)A[a] = -1;
        For(a, 0, sz(g)) if(A[a] == 0)cur.push_back(a);
        for(ll lay = 1;; lay++){
            bool islast = 0;
            next.clear();
            for(ll a : cur) for(ll b : g[a]){
                if(btoa[b] == -1){
                    B[b] = lay;
                    islast = 1;
                }
                else if(btoa[b] != a && !B[b]){
                    B[b] = lay;
                    next.push_back(btoa[b]);
                }
            }
            if(islast)break;
            if(next.empty())return res;
            for(ll a : next)A[a] = lay;
            cur.swap(next);
        }
        For(a, 0, sz(g)) res += dfs(a, 0, g, btoa, A, B);
    }
}
