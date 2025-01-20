/**
 * Author: Jan Gottweis
 * Date: 2025-1-15
 * License: CC0
 * Source: kactl + ksp + me
 * Description: treap with same functionality as set,
 * change commented to get ordered set (idexed from 1 to cnt(treap)).
 * Has traverse implemented see comment.
 * Time: O(\log N).
 * Usage: pnode treap = 0; treap = insert(treap, new Node(val));
 * Status: some simple tasks on cses 
 */
struct Node{
    Node *l = 0, *r = 0;
    ll val, y, c = 1;
    Node(ll val) : val(val), y(rand()) {}
    void recalc();
};

typedef Node* pnode;

ll cnt(pnode n){ return n ? n->c : 0ll; }
void Node::recalc() { c=cnt(l) + cnt(r) + 1;}

template<class F> void each(pnode n, F f){
    if(n) {each(n->l, f); f(n->val) ; each(n->r, f);}
}
// each(t, [](ll val){cerr<<val<<' ';}); cerr<<endl; use [&] for printing all variables 

pair<pnode, pnode> split(pnode n, ll k){
    if(!n)return {};
    if(n->val > k/* cnt(n->l)>=k */){
        auto pa = split(n->l, k);
        n->l = pa.second;
        n->recalc();
        return {pa.first, n};
    }
    else{
        auto pa = split(n->r, k /* - cnt(n->l) - 1 */);
        n->r = pa.first;
        n->recalc();
        return {n, pa.second};
    }
}

pnode merge(pnode l, pnode r){
    if(!l) return r;
    if(!r) return l;
    if(l->y > r->y){
        l->r = merge(l->r, r);
        l->recalc();
        return l;
    }
    else{
        r->l = merge(l, r->l);
        r->recalc();
        return r;
    }
}

pnode insert(pnode n, pnode t/* , ll pos */){
    auto [l, r] = split(n, t->val /* pos */);
    return merge(l, merge(t, r));
}
pnode erase(pnode n, ll pos){
    auto [tl, r] = split(n, pos);
    auto [l, d] = split(tl, pos-1);
    return merge(l, r);
}
ll get(pnode n, ll pos){
    auto [tl, r] = split(n, pos);
    auto [l, d] = split(tl, pos-1);
    if(!d)return -1;
    ll ans = d->val;
    n = merge(merge(l, d), r);
    return ans;
}