#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) x.begin(),x.end()
#define ar array
#define sz(x) ((int)x.size())
template <class T,class S> inline bool chmin(T &a,const S &b) {return (a> b? a= b, 1: 0);}
template <class T,class S> inline bool chmax(T &a,const S &b) {return (a< b? a= b, 1: 0);}
int main(){
    ios_base::sync_with_stdio(false),cin.tie(0);
    vector <map<int, int>> arr(5);
    arr[1].insert({1 , 1});

    vector <vector <ar<int, 3>>> brr(5);
    
    brr[0].push_back({1, 3, 5});

    // cout << brr[0][0][1] << "\n";
    map <unsigned int, ar<int, 3>> mp;
    mp[0] = {1, 3, 5};
    for(int i = 0,a, b, c, d;i < 5;i++){
        cin >> a >> b >> c >> d;
        mp[a] = {b, c, d};
    }

    return 0;
}