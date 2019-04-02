#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
const int MAXSIZE = 1e4+7;
const int INF = 1e9;
vector<int>edge[MAXSIZE];
stack<int> s;
int dfn[MAXSIZE], low[MAXSIZE], indree[MAXSIZE];
int fre[MAXSIZE], scc[MAXSIZE], minf[MAXSIZE];
bool vis[MAXSIZE];
int n, m;
int cs, tot;
void init(){
    cs = tot = 0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(indree,0,sizeof(indree));
    memset(fre,0,sizeof(fre));
    memset(vis,false,sizeof(false));
    memset(scc,0,sizeof(scc));
    memset(minf,0,sizeof(minf));
    while(!s.empty()) s.pop();
    for(int i = 1; i<= n ;i++){
        edge[i].clear();
        minf[i] = INF;
    }
}
void tarjan(int x){
    dfn[x] = low[x] = ++tot;
    vis[x] = true;
    s.push(x);
    for(int i = 0; i< edge[x].size(); i++){
        int v = edge[x][i];
        if(!dfn[v]){
            tarjan(v);
            low[x] = min(low[x], low[v]);
        }
        else if(vis[v]){
            low[x] = min(low[x], dfn[v]);
        }
    }
    if(dfn[x] == low[x]){
        cs++;
        int y;
        do{
            y = s.top();
            s.pop();
            scc[y] = cs;
            vis[y] = false;
            minf[cs] = min(fre[y], minf[cs]);
        }while(x != y);
    }
}
void excute(){
    for(int i = 1; i <= n; i++)
        if(!dfn[i])
            tarjan(i);
}
int main(){
    int a, b;
    while(~scanf("%d %d", &n, &m)){
        init();
        for(int i = 1; i <= n; i++)
            scanf("%d", &fre[i]);
        for(int i = 0; i < m; i++){
            scanf("%d %d", &a, &b);
            edge[a].push_back(b);
        }
        excute();
        for(int i = 1; i<= n; i++){
            for(int j = 0; j < edge[i].size(); j++){
                if(scc[edge[i][j]] != scc[i]){
                    indree[scc[edge[i][j]]]++;
                }
            }
        }
        int cnti = 0;
        int sum = 0;
        for(int i = 1; i <= cs; i++){
            if(!indree[i]){
                cnti++;
                sum += minf[i];
            }
        }
        printf("%d %d\n", cnti, sum);
    }
    return 0;
}
