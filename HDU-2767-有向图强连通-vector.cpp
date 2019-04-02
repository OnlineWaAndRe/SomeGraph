#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
const int MAXSIZE = 1e4+7;
vector<int> edge[MAXSIZE];
stack<int> sta;
int dfn[MAXSIZE], low[MAXSIZE], scc[MAXSIZE];
int indree[MAXSIZE], outdree[MAXSIZE];
bool vis[MAXSIZE];
int cs, tot;
int n, m;
void init(){
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(scc,0,sizeof(scc));
    memset(outdree,0,sizeof(outdree));
    memset(indree,0,sizeof(indree));
    memset(vis,false, sizeof(vis));
    for(int i = 1; i <= n; i++)
        edge[i].clear();
    cs = tot = 0;
}
void tarjan(int x){
    low[x] = dfn[x] = ++tot;
    sta.push(x);
    vis[x] = true;
    for(int i = 0; i < edge[x].size(); i++){
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
            y = sta.top();
            sta.pop();
            scc[y] = cs;
            vis[y] = false;
        }while(x != y);
    }
}
void excute(){
    for(int i = 1; i <= n; i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
}
int main(){
    int t;
    int a, b;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &m);
        init();
        for(int i = 0; i< m ; i++){
            scanf("%d %d", &a, &b);
            edge[a].push_back(b);
        }
        excute();
        for(int i = 1; i<= n; i++){
            for(int j = 0; j < edge[i].size(); j++){
                if(scc[edge[i][j]] != scc[i]){
                    indree[scc[edge[i][j]]]++;
                    outdree[scc[i]]++;
                }
            }
        }
        int cni, cno;
        cni = cno = 0;
        for(int i = 1; i <= cs; i++){
            if(!indree[i])
                cni++;
            if(!outdree[i])
                cno++;
        }
        if(cs == 1) printf("0\n");
        else printf("%d\n", max(cni,cno));
    }
    return 0;
}
