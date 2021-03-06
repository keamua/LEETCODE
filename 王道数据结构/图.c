//6.2图的存储及基本操作
//邻接矩阵法
#define maxsize 100
typedef char vertextype;
typedef int edgetype;
typedef struct{
    vertextype vex[maxsize];
    edgetype edge[maxsize][maxsize];
}mgraph;

//邻接表
typedef struct arcnode{
    int adjvex;
    struct arcnode *next;
}arcnode;

typedef struct vnode{
    vertextype data;
    arcnode *first;
}vnode,adjlist[maxsize];

typedef struct{
    adjlist vertices;
    int vernum,arcnum;
}algraph;

//十字链表法，有向图的一种链式存储结构
//邻接多重表，无向图

//从邻接表转换为邻接矩阵
void convert(algraph g,int **arcs,int m,int n){
    for(int i=0;i<n;i++){
        arcnode *p=(g.vertices[i]).first;
        while(p!=null){
            arcs[i][p->adjvex]=1;
            p=p->next;
        }
    }
}
//因为可以从邻接表转化为邻接矩阵，所以下面应用中图的类型采用邻接表


//6.3图的遍历
//广度优先搜索
bool visited[maxsize];
queue q;
void bfstreaverse(algraph g){
    for(int i=0;i<g.vernum;++i)
        visited[i]=false;
    initqueue(q);
    for(int i=0;i<g.vernum;++i)
        if(!visited[i])
            bfs(g,i);
}
void bfs(algraph g,int v){
    visit(v);
    visited[v]=true;
    enqueue(q,v);
    while(!isempty(q)){
        dequeue(q,v);
        for(arcnode *w=g.vertices[v].first;w!=null;w=w->next)
            if(!visited[w->adjvex]){
                visit(w);
                visited[w->adjvex]=true;
                enqueue(q,w);
            }
    }
}

//bsf求单源最短路径，非带权图
void bfs_min_bistance(algraph g,int u){
    int d[maxsize];
    for(int i=0;i<g.vernum;++i)
        d[i]=32737;
    visited[u]=true;
    d[u]=0;
    enqueue(q,u);
    while(!isempty(q)){
        dequeue(q,u);
        for(arcnode *w=g.vertices[u].first;w!=null;w=w->next)
            if(!visited[w->adjvex]){
                visited[w->adjvex]=true;
                d[w->adjvex]=d[u]+1;
                enqueue(q,w);
            }
    }
}//从u开始广度遍历，d类似深度


//深度优先搜索
void dfstraverse(algraph g){
    for(int v=0;v<g.vernum;++v)
        visited[v]=false;
    for(int v=0;v<g.vernum;++v)
        if(!visited[v])
            dfs(g,v);
}
void dfs(algraph g,int v){
    visit(v);
    visited[v]=true;
    for(arcnode *w=g.vertices[v].first;w!=null;w=w->next)
        if(!visited[w->adjvex])
            dfs(g,w);
}

//2.判断无向图是否是树
bool istree(algraph g){
    for(int i=1;i<=g.vernum;i++)
        visited[i]=false;
    int vnum=0,enum1=0;
    dfs2(g,1,vnum,enum1,visited);
    if(vnum==g.vernum && enum1==2*(g.vernum-1))
        return true;
}
void dfs2(algraph g,int v,int vnum,int enum1,bool visited[]){
    visited[v]=true;vnum++;
    arcnode *w= g.vertices[v].first;
    while(w!=null){
        enum1++;
        if(!visited[w->adjvex])
            dfs2(g,w,vnum,enum1,visited);
        w=w->next;
    }
}

//邻接表图的非递归深度遍历
void dfs_non_rc(algraph g,int v){
    int w;
    stack s;
    initstack(s);
    for(int i=0;i<g.vernum;i++)
        visited[i]=false;
    push(s,v);visited[v]=true;
    while(!isempty(s)){
        int k=pop(s);
        visit(k);
        for(arcnode *w=g.vertices->first;w!=null;w=w->next)
            if(!visited[w->adjvex]){
                push(!visited[w->adjvex]);
                visited[w->adjvex]=true;
            }
    }
}

//4.用深度优先和宽度优先遍历判断是否有i到j的路径
void dfs2(algraph g,int i,int j,bool can_reach){
    if(i==j){
        can_reach==true;
        return;
    }
    visited[i]=1;
    for(arcnode *p=g.vertices[i].first;p!=null;p=p->next){
        if(!visited[p->adjvex]&&!can_reach)
            dfs2(g,p->adjvex,j,can_reach);
    }
}
void bfs2(algraph g,int i,int j){
    queue q;initqueue(q);enqueue(q,i);
    int u;
    while(!isempty(q)){
        dequeue(q,u);
        visited[u]=1;
        if(u==j)
            return 1;
        for(arcnode *p=g.vertices[u].first;p;p=p->next){
            if(p==j)
                return 1;
            if(!visited[p->adjvex]){
                enqueue(q,p->adjvex);
                visited[p->adjvex]=1;
            }
        }
    }
    return 0;
}


//5.邻接表的图输出所有i到j的简单路径

void findpath(algraph *g,int u,int v,int path[],int d){
    int w,i;
    arcnode *p;
    d++;
    path[d]=u;
    visited[u]=1;
    if(u==v)
        printf("path[]");
    p=g->vertices[u].first;
    while(p){
        w=p->adjvex;
        if(visited[w]==0)
            findpath(g,w,v,path,d);
        p=p->next;
    }
    visited[u]=0;
}







//图的应用


//1.prim算法

void prim(g,t){
    t=null;
    u={w};
    while((V-U)!=∅){
        (u,v)=min(u∈U,v∈(V-U))
        t=t∪{(u,v)};
        U=U∪{v};
    }
}

//2.kruskal算法
void kruskal(v,t){
    t=v;
    nums=n;
    while(nums>1){
        (v,u)=min(g.e);
        if(v∈ && u ∉){
            t=t∪{(u,v)};
            nums--;
        }
    }
}

//拓扑排序
bool topologicalsort(algraph g){
    stack s;initstack(s);int in[maxsize],i;
    for(i=0;i<g.vernum;i++)
        if(in[i]==0)
            push(s,i);
    int count=0;
    while(!isempty(s)){
        pop(s,i);
        printf("%d\n",i);
        count++;
        for(arcnode *p=g.vertices[i].first;p;p=p->next){
            int v=p->adjvex;
            if(!(--in[v]))
                push(s,v);
        }
    }
    if(count<g.vernum)
        return false;
    else
        return true;
}

//9.有向无环图实现拓扑排序
void dfstraverse(algraph g){
    for(int v=0;v<g.vernum;++v)
        visited[v]=false;
    time = 0;
    for(int v=0;v<g.vernum;++v)
        if(!visited[v])
            dfs3(g,v);
}
int finishtime[maxsize];
void dfs3(algraph g,int v){
    visited[v]=true;
    visit(v);
    for(arcnode *w=g.vertices[v].first;w;w=w->next)
        if(!visited[w->adjvex]){
            dfs3(g,w);
        }
    time = time +1;finishtime[v]=time;
}


