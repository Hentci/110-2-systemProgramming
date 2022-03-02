#include <iostream>
#include <vector>
#include <map>
#include <array>
using namespace std;
using ui = unsigned int;
#define ar array
const int mxn = 2e3;
class node{
    public:

    ui id;

};
int G[mxn][mxn];
int main(){
    // freopen("input.txt", "r", stdin);
    int n, dst, m; // n -> the number of nodes, m -> the number of links
    cin >> n >> dst >> m;
    vector <node> dsts(dst); 
    // vector <vector <ar<ui, 3>>> adj(n); // to store the neighbor's IDs <b, oldw, neww>
    // vector <map<node, node>> table(n); // to store each entry <destination ID, next node ID>
    map<ui, map<ui, ui>> table;
    

    for(int i = 0, nd;i < dst;i++){
        cin >> nd;
        dsts[i].id = nd;
    }

    // ui a, b, ow, nw;
    // for(int i = 0, linkid;i < m;i++){
    //     cin >> linkid >> a >> b >> ow >> nw;
    //     adj[a].push_back({b, ow, nw});
    //     adj[b].push_back({a, ow, nw});
    // }

    map <int, ar<int, 3>> links;
    int a, b, linkid;
    for(int i = 0, ow, nw;i < m;i++){
        cin >> linkid >> a >> b >> ow >> nw;
        G[a][b] = ow;
        G[b][a] = ow;
        links[linkid] = {a, b, nw};
    }

    // for(int i = 0;i < n;i++){
    //     for(int j = 0;j < n;j++)
    //         cout << G[i][j] << " ";
    //     cout << "\n";
    // }

    vector <int> d(n);
    vector <bool> inPath(n);
    vector <ui> par(n);
    auto dijk = [&](ui st) -> void{
        fill(d.begin(), d.end(), INT32_MAX);
        fill(inPath.begin(), inPath.end(), false);
        par[0] = -1;
        d[st] = 0;
        for(int i = 0;i < n - 1;i++){
            int mn = INT32_MAX, mnIdx;
            for(int j = 0;j < n;j++)
                if(!inPath[j] && d[j] <= mn)
                    mn = d[j], mnIdx = j;

            inPath[mnIdx] = true;
            for(int v = 0;v < n;v++){
                if(!inPath[v] && G[mnIdx][v] && d[mnIdx] + G[mnIdx][v] <= d[v]){
                    par[v] = mnIdx;
                    d[v] = d[mnIdx] + G[mnIdx][v];
                }
            }
        }
    };

    // dijk(4);
    // for(auto ele: par)
    //     cout << ele << " ";
    // cout << "\n";
    for(auto ele: dsts){
        dijk(ele.id);
        for(ui v = 0;v < n;v++){
            if(v == ele.id) continue;
            table[v][ele.id] = par[v];
        }
    }
    for(int i = 0;i < n;i++){
        if(table[i].empty()) continue;
        cout << i << "\n";
        for(auto ele: table[i]){
            cout << ele.first << " " << ele.second << "\n";
        }
    }

    for(auto ele: links){
        G[ele.second[0]][ele.second[1]] = ele.second[2];
        G[ele.second[1]][ele.second[0]] = ele.second[2];
    }
    // bool skip[n][n] = {};
    for(auto ele: dsts){
        dijk(ele.id);
        for(ui v = 0;v < n;v++){
            if(v == ele.id) continue;
            if(par[v] == table[v][ele.id]){
                table[v].erase(ele.id);
                continue;
            }
            table[v][ele.id] = par[v];
        }
    }
    for(int i = 0;i < n;i++){
        if(table[i].empty()) continue;
        cout << i << "\n";
        for(auto ele: table[i]){
            cout << ele.first << " " << ele.second << "\n";
        }
    }

    return 0;
}