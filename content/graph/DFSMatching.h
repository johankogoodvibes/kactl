/**
 * Author: Jan Gottweis
 * Date: 2025-1-3
 * License: CC0
 * Source:
 * Description: UPDATED g is of size $|A|$, contains neighbors in B (numbers in $0,...,|B|$) 
 * $btoa$ should be a vector full of -1's of size $|B|$. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Time: O(VE)
 * Usage: vec<ll> btoa(m, -1); dfsMatching(g, btoa);
 * Status: works
 */
#pragma once

bool find(ll j, vec<vec<ll>>&g, vec<ll>&btoa, vec<ll>&vis){
    if(btoa[j] == -1)return 1;
    vis[j] = 1; ll di = btoa[j];
    for(ll e : g[di]){
        if(!vis[e] && find(e, g, btoa, vis)){
            btoa[e] = di;
            return 1;
        }
    }
    return 0;
}

ll dfsMatching(vec<vec<ll>>&g, vec<ll>&btoa){
    vec<ll> vis;
    For(i, 0, sz(g)){
        vis.assign(sz(btoa), 0);
        for(ll j : g[i]){
            if(find(j, g, btoa, vis)){
                btoa[j] = i;
                break;
            }
        }
    }
    return sz(btoa)- (ll)count(all(btoa), -1);
}
