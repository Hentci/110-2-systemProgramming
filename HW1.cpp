#include <iostream>
#include <vector>
#include <map>
#include <array>
using namespace std;
using ui = unsigned int;
#define ar array
// const int mxn = 2e5;
class node{
    public:

    ui id;

};
int main(){
    freopen("input.txt", "r", stdin);
    int n, dst, m; // n -> the number of nodes, m -> the number of links
    cin >> n >> dst >> m;
    vector <node> dsts(dst); 
    vector <vector <ar<ui, 3>>> adj(n); // to store the neighbor's IDs <b, oldw, neww>
    vector <map<node, node>> table(n); // to store each entry <destination ID, next node ID>

    for(int i = 0, nd;i < dst;i++){
        cin >> nd;
        dsts[i].id = nd;
    }

    ui a, b, ow, nw;
    for(int i = 0, linkid;i < m;i++){
        cin >> linkid >> a >> b >> ow >> nw;
        adj[a].push_back({b, ow, nw});
        adj[b].push_back({a, ow, nw});
    }

    

    return 0;
}