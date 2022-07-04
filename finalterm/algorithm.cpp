#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<ll,ll>
#define f first
#define s second
int switches, nodecost;
int instime, updtime, simduration;
int srcid, dstid, oldpathlen;
int links;
vector<int> v1[2005], pre[2005], v;
vector<pii> v2[2005];
vector<vector<int>> abo;
long long dis[2005];

void dfs(int x){
    if(x == srcid){
        vector<int> u = v;
        reverse(u.begin(), u.end());
        abo.push_back(u);
        return;
    }
    for(auto i : pre[x]){
        v.push_back(i);
        dfs(i);
        v.pop_back();
    }
}

int main(){
    // cin >> switches >> nodecost;
    // cin >> instime >> updtime >> simduration;
    cin >> srcid >> dstid >> oldpathlen;
    vector<int> ans_vec;
    set<pii> st; // old edge
    ll x = oldpathlen, tmp, a, b, w, ans = 0;
    ans_vec.push_back(srcid);
    while(x--){
        cin >> a >> b;
        ans_vec.push_back(b);
        st.insert({a, b});
        v1[a].push_back(b);
    }
    cin >> links;
    x = links;
    while(x--){
        cin >> a >> b >> w;
        if(st.find({a, b}) != st.end() || st.find({b, a}) != st.end()) ans += w;
        v2[a].push_back({b, w});
        v2[b].push_back({a, w});
    }
    int node_count;
    cin >> node_count;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    memset(dis, 0x3f3f3f3f, sizeof(dis));
    dis[srcid] = 0;
    pq.push({0, srcid});
    // cout << 1 << '\n';
    while(!pq.empty()){ 
        auto now = pq.top();
        pq.pop();
        if(dis[now.s] < now.f) continue;
        for(auto edge: v2[now.s]){
            if(dis[edge.f] == dis[now.s] + edge.s){
                pre[edge.f].push_back(now.s);
            }
            if(dis[edge.f] > dis[now.s] + edge.s){
                dis[edge.f] = dis[now.s] + edge.s;
                pre[edge.f].clear();
                pre[edge.f].push_back(now.s);
                pq.push({dis[edge.f], edge.f});
            }
        } 
    }
    int path_cost = dis[dstid];
    v.push_back(dstid);
    dfs(dstid);
    int cur_sum = 0;
    for(auto vec : abo){
        set<pii> se;
        set<int> yyds;
        for(int i = 0; i < vec.size() - 1; i++){
            se.insert({vec[i], vec[i + 1]});
            if(st.find({vec[i], vec[i + 1]}) == st.end()){
                yyds.insert(vec[i]);
            }
        }
        for(auto i : st){
            if(se.find(i) == se.end()){
                yyds.insert(i.f);
            }
        }
        int size = (yyds.find(dstid) != yyds.end()) ? yyds.size() - 1 : yyds.size();
        if(path_cost + size * node_count < ans){
            ans = path_cost + size * node_count;
            ans_vec.clear();
            for(int i = 0; i < vec.size(); i++){
                ans_vec.push_back(vec[i]);
            }
        }
    }
    cout << "*********\n";
    for(vector<int> i : abo){
        for(auto k: i){
            cout << k << " ";
        }
        cout << '\n';
    }
    cout << "********\n";
    for(auto i : ans_vec){
        cout << i << " ";
    }
    cout << '\n';
    cout << "COST: " << ans << '\n';
}