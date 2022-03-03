#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <queue>
#include <functional>
using namespace std;
using ui = unsigned int;
#define ll long long
#define ar array
const int mxn = 2e3;
class node{
    public:
    ui id;
};
class edge{
    public:
    bool isold; // determine whether the node is old or not
    ui neighbor;
    ll w; // weight
    edge(){}
    edge(bool a, int b, ll c): isold(a), neighbor(b), w(c){}
};
int main(){
    // freopen("input.txt", "r", stdin);
    int n, dst, m; // n -> the number of nodes, m -> the number of links
    cin >> n >> dst >> m;
    vector <vector <edge>> G(mxn); // Graph
    vector <node> dsts(dst);  // all destinations
    map<ui, map<ui, ui>> table; // output table <node id, destination id, ans>
    

    for(int i = 0, nd;i < dst;i++){
        cin >> nd;
        dsts[i].id = nd;
    }

    // linkid -> useless
    int a, b, linkid;
    ll ow, nw;
    for(int i = 0;i < m;i++){
        cin >> linkid >> a >> b >> ow >> nw;
        G[a].push_back(edge(true, b, ow));
        G[b].push_back(edge(true, a, ow));
        G[a].push_back(edge(false, b, nw));
        G[b].push_back(edge(false, a, nw));
    }

    vector <ll> d(n);
    vector <ui> par(n); // record the shortest path 
    auto dijk = [&](bool ok, ui st) -> void{
        fill(d.begin(), d.end(), 0x3f3f3f3f3f);
        d[st] = 0;
        par[st] = st;
        /* init */

        /* dijkstra */
        priority_queue <ar<ll, 2>, vector <ar<ll, 2>>, greater<ar<ll, 2>>> pq;
        pq.push({0, st});
        while(!pq.empty()){
            auto [wei, v] = pq.top(); pq.pop();
            if(wei > d[v]) continue;
            for(auto ele: G[v]){
                // to determine use which weight
                if(ele.isold == ok) continue;
                // upd smaller node if they are same d
                if(d[ele.neighbor] == d[v] + ele.w && v < par[ele.neighbor])
                    par[ele.neighbor] = v;
                // dijkstra -> greedy
                if(d[ele.neighbor] > d[v] + ele.w){
                    par[ele.neighbor] = v;
                    d[ele.neighbor] = d[v] + ele.w;
                    pq.push({d[ele.neighbor], ele.neighbor});
                }
            }
        }
    };
    /* process the old table */
    for(auto ele: dsts){
        dijk(0, ele.id);
        for(int i = 0;i < n;i++){
            if(i == (int)ele.id) continue;
            table[i][ele.id] = par[i];
        }
    }
    for(int i = 0;i < n;i++){
        cout << i << "\n";
        for(auto ele: table[i])
            cout << ele.first << " " << ele.second << "\n";
    }
    /* process the new table */
    for(auto ele: dsts){
        dijk(1, ele.id);
        for(int i = 0;i < n;i++){
            if(i == (int)ele.id) continue;
            if(par[i] == table[i][ele.id]){
                table[i].erase(ele.id);
                continue;
            }
            table[i][ele.id] = par[i];
        }
    }
    for(int i = 0;i < n;i++){
        if(table[i].empty()) continue;
        cout << i << "\n";
        for(auto ele: table[i])
            cout << ele.first << " " << ele.second << "\n";
    }

    return 0;
}