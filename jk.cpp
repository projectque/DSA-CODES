#include <bits/stdc++.h>
using namespace std;
#define ll long long


vector<vector<ll>> adj(1001);

ll N,M,T,C;
void dijkstra(vector<ll> & d, vector<ll> & p) {
    ll n = N+1;
    d.assign(n, __LONG_LONG_MAX__);
    p.assign(n, -1);

    d[1] = 0;
    using pii = pair<ll, ll>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, 1});
    while (!q.empty()) {
        
        ll v = q.top().second;
        ll d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;
        bool ifred=((d[v]/T)&1);
        for (auto to : adj[v]) {
            ll len;
            if(ifred)
                len = ((d[v]/T)*T + T + C)-d[v];
            else
                len = C;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}


int32_t main()
{
    
    cin>>N>>M>>T>>C;
    ll u,v;
    while(M--){
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    

    vector<ll> dist, par;

    dijkstra(dist, par);
    int to=N;
    ll NextBestPath = __LONG_LONG_MAX__;
    while (par[to]!=-1) {
        u=par[to];
        v=to;
        for(auto it=adj[u].begin();it!=adj[u].end();++it)
            if(*it==v){
                adj[u].erase(it);
                break;
            }
        swap(u, v);
        for(auto it=adj[u].begin();it!=adj[u].end();++it)
            if(*it==v){
                adj[u].erase(it);
                break;
            }
        vector<ll> p;
        dijkstra(dist, p);
        NextBestPath = min(NextBestPath, dist[N]);
        adj[u].push_back(v);
        adj[v].push_back(u);
        to=par[to];
    }
    
    cout<<NextBestPath;
    return 0;
}