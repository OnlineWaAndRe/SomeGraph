#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
const int MAXSIZE = 1e4+7;
struct node{
    int st;
    int to, next;
}edge[MAXSIZE];
stack<int> s;
int head[MAXSIZE], vis[MAXSIZE], scc[MAXSIZE];
int dfn[MAXSIZE], low[MAXSIZE];
int indree[MAXSIZE], outdree[MAXSIZE];
int n, m;
int cs, tot, cnt;
void init(){
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(scc,0,sizeof(scc));
    memset(dfn, 0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(indree,0,sizeof(indree));
    memset(outdree,0,sizeof(outdree));
    memset(edge,0,sizeof(edge));
    cs = tot = cnt = 0;
    while(!s.empty())
        s.pop();
}
void addedge(int a, int b){
    edge[cnt].to = b;
    edge[cnt].st = a;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}
void tarjan(int x){
    dfn[x] = low[x] = ++tot;
    vis[x] = 1;
    s.push(x);
    for(int i = head[x]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[x] = min(low[x], low[v]);
        }
        else if(vis[v]){
            low[x] =min(low[x], dfn[v]);
        }
    }
    if(dfn[x] == low[x]){
        cs++;
        int y;
        do{
            y = s.top();
            s.pop();
            scc[y] = cs;
            vis[y] = 0;
        }while(x != y);
    }
}
void excute(){
    for(int i = 1; i<= n; i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
}
int main(){
    int a, b;
    while(~scanf("%d %d", &n, &m)){
        init();
        for(int i = 0; i < m; i++){
            scanf("%d %d", &a, &b);
            addedge(a, b);
        }
        excute();
        for(int i = 0; i< m; i++){
            if(scc[edge[i].st] != scc[edge[i].to]){
                indree[scc[edge[i].st]]++;
                outdree[scc[edge[i].to]]++;
            }
        }
        int cnti, cnto ;
        cnti = cnto = 0;
        for(int i = 1; i<= cs; i++){
            if(!indree[i])
                cnti++;
            if(!outdree[i])
                cnto++;
        }
        if(cs == 1) printf("0\n");
        else printf("%d\n", max(cnti,cnto));
    }
    return 0;
}
