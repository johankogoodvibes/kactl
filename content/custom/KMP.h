/**
 * Author: Jan Gottweis
 * Date: 2025-2-25
 * License: CC0
 * Source: misqo + me
 * Description: basic kmp
 * Time: O(N + M).
 * Usage: kmp(pattern, string)
 * Status: tested on icpc wf 2020 - o
 */
vec<ll> kmp(string& a, string& b){
    vec<ll> positions;
    string s = a + "#" + b;
    vec<ll> jumps(sz(s));
    ll prev = 0;
    For(i, 1, sz(s)) {
        while (prev > 0 && s[i] != s[prev]) prev = jumps[prev - 1];
        if (s[i] == s[prev]) prev++;
        jumps[i] = prev;
        if (prev == sz(a)) {
            positions.push_back(i - sz(a) - 1);
        }
    }
    return positions;
}