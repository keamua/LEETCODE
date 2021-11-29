#define maxsize 100
typedef struct lnode{
    int data;
    struct lnode *next;
}lnode,*linklist;
typedef struct tnode{
    int data;
    struct tnode *lchild,*rchild;
}tnode,*bitree;

//1.1给两个逆序储存大整数的链表相加
lnode* addlargeint(lnode *p,lnode *q){
    lnode *result;
    lnode *tempp=p->next;
    lnode *tempq=q->next;
    lnode *r=null;
    result = (lnode*)malloc(sizeof(lnode));
    result->next=null;
    r=result;
    int carry=0;

    while(tempp!=null && tempq!=null){
        lnode *temp=(lnode*)malloc(sizeof(lnode));
        temp->next = null;
        temp->data= (tempp->data + tempq->data + carry )%10;
        carry = (tempp->data + tempq->data +carry)/10;
        r->next=temp;
        r=r->next;
        tempp=tempp->next;
        tempq=tempq->next;
    }
    if(tempp==null) tempp=tempq;
    while(tempp!=null){
        lnode *temp=(lnode*)malloc(sizeof(lnode));
        temp->next = null;
        temp->data= (tempp->data + carry )%10;
        carry = (tempp->data + carry)/10;
        r->next=temp;
        r=r->next;
        tempp=tempp->next;
    }
    if(carry > 0){
        lnode *temp=(lnode*)malloc(sizeof(lnode));
        temp->next = null;
        temp->data= carry;
        r->next = temp;
    }
    return result;
}

//1.2 求二叉树节点p的双亲节点,(p在树里面)
tnode *getparent(bitree t,tnode *p){
    if(t==null)
        return null;
    if(t==p)
        return null;
    if(t->lchild==p||t->rchild==p)
        return t;
    tnode *parent=getparent(t->lchild,p);
    if(parent!=null)
        return parent;
    else
        return getparent(t->rchild,p);
}

//2.带权有向图中各个顶点到一指定顶点的最短路径
//迪杰斯特拉，反向修改。注释为原来代码
void reverse_dijkstrea(int n,int mgraph[][n],int v0,int dist[],int path[]){
    int set[maxsize];
    int min,v;
    for(int i=0;i<n;++i){
        dist[i]=mgraph[i][v0];   //dist[i]=mgraph[v0][v];
        set[i]=0;
        if(mgraph[i][v0]<0x7fffffff)  //if(mgraph[v0][i]<INF)
            path[i]=v0;
        else    
            path[i]=-1;
    }
    set[v0]=1;path[v0]=-1;
    for(int i=0;i<n-1;++i){
        min=0x7fffffff;
        for(int j=0;j<n;++j)
            if(set[j]==0&&dist[j]<min){
                v=j;
                min=dist[j];
            }
        set[v]=1;
        for(int j=0;j<n;++j){
            if(set[j]==0&&dist[v]+mgraph[j][v]<dist[j]){    //dist[v]+mgraph[v][j]<dist[j]
                dist[j]=dist[v]+mgraph[j][v];   //dist[j]=dist[v]+mgraph[v][j]
                path[j]=v;
            }     
        }
    }
}

//3.以二元组（f，c）保存的树的各条边，f是双亲，c是孩子，建立这棵树的孩子——兄弟链表节点
typedef struct csbtnode{
    int data;
    struct csbtnode *child,*sibling;
}csbtnode,*csbtree;

csbtnode* createtree(char ttuple[][3]){
    csbtnode *t=null;
    csbtnode *parents[maxsize];int pn=0;    //记录pn的双亲节点
    int i=0;
    while(ttuple[i][0]!='^'&&ttuple[i][1]!='^'){ //当不是结束组（^，^）时
        if(ttuple[i][0]=='^'){  //如果没有父亲节点，即根节点
            t=(csbtnode*)malloc(sizeof(csbtnode));
            t->data=ttuple[i][1];
            t->child=t->sibling=null;
            parents[pn]=t;  //第一个父亲结点
            ++pn;++i;
        }
        else{
            csbtnode *tempp=null;
            csbtnode *ls=null;
            int j=0;
            for(j=0;j<pn;++j)   //找三元组中，最后一个与加入到父亲节点一样的数据
                if(ttuple[i][0]==parents[j]->data)
                    tempp=parents[j];
            int flag=0;
            for(j=i;ttuple[j][0]==tempp->data;++j){ //找到对应同一个父亲的节点
                if(flag==0){ //如果是第一个孩子
                    flag=1;
                    csbtnode *tempc=(csbtnode*)malloc(sizeof(csbtnode));
                    tempc->data=ttuple[j][1];
                    tempc->child=tempc->sibling=null;
                    tempp->child=tempc; //链接到父亲节点后面
                    ls=tempc; //暂时储存这个长兄
                    parents[pn]=tempc;  //保存
                    ++pn;
                }
                else{   //如果不是第一个孩子
                    csbtnode *temps=(csbtnode*)malloc(sizeof(csbtnode));
                    temps->data=ttuple[j][1];
                    temps->child=temps->sibling=null;
                    ls->sibling=temps;  //连接到长兄后面
                    ls=temps;
                    parents[pn]=temps;
                    ++pn;
                }
            }
            i=j;
        }
    }
    return t;
}


//4.1判断输入和输出队列，判断是栈还是队列
int stackorqueue(int a[],int b[],int n){
    bool isqueue=true;
    bool isstack=true;
    for(int i=0;i<n;++i){
        if(a[i]!=b[i])  isqueue=false;
        if(a[i]!=b[n-i-1])  istack=false;
    }
    if(isqueue == true && isstack == true)
        return 1;
    else if(isstack == true)
        return 2;
    else if(isqueue == true)
        return 3;
    else    
        return 4;
}



//4.2邻接表存储的有向无环图，不用栈也不用队列实现拓扑排序
typedef struct arcnode{
    int data;
    struct arcnode *next;
}arcnode,* arcnodes;
typedef struct {
    int data;
    arcnode *first;
}vexnode;
typedef struct{
    int vnum,e;
    vexnode adjlist[maxsize];
}agraph;

void topsortnsq(agraph *ag){
    int visited[maxsize];
    int in[maxsize];    //记录入度
    int i,j;
    for(i=0;i<ag->vnum;++i){
        visited[i]=0;
        in[i]=0;
    }
    for(i=0;i<ag->vnum;++i){    //计算每个点的入度
        arcnode *r=ag->adjlist[i].first;
        while(r!=null){
            ++in[r->data];
            r=r->next;
        }
    }
    for(i=0;i<ag->vnum;++i){  //遍历图
        for(j=0;j<ag->vnum;++j)
            if(in[j]==0&&visited[j]==0) //寻找入度为0，且没有被访问过的点（即没有被删除）
                break;
        if(j==ag->vnum){    //是第n个点，说明还有点没有被删除却遍历完了，即有环删除不了
            printf("there is loop\n");
            return;
        }
        visited[j]=1;   //标记为被访问
        printf("%d\n",ag->adjlist[j].data);
        arcnode *r=ag->adjlist[j].first;//找这个点的临界点
        while(r!=null){
            --in[r->data]; //将邻接点的入度给减一
            r=r->next;
        }
    }
}


//5.寻找相同字符在字符串中的最大距离
int getmaxlength(char str[],int n){
    int max=0;
    int i;
    int ischinarray[128];
    for(i=0;i<128;++i)
        ischinarray[i]=-1;
    for(i=0;i<n;++i){
        if(ischinarray[str[i]==-1])
            ischinarray[str[i]]==i;
        else{
            int templ=i-ischinarray[str[i]];
            if(max<templ)
                max=templ;
        }
    }
    return max;
}


//6.判断一个有向无环图中是否有个顶点到任意一个顶点都有路径
void dfsforcount(agraph *g,int v,int visited[],int& n){
    bool has=false;
    arcnode *p;
    visited[v]=1;
    ++n;
    p=g->adjlist[v].first;
    while(p!=null){
        if(visited[p->data]==0)
            dfsforcount(g,p->data,visited,n);
        p=p->next;
    }
}
bool isonetoall(agraph *g){
    int n,i,j;
    int visited[maxsize];
    for(i=0;i<g->vnum;++i){
        for(j=0;j<g->vnum;++j)
            visited[j]=0;
        n=0;
        dfsforcount(g,i,visited,n);
        if(n==g->vnum)
            return true;
    }
    return false;
}

//7.递增有序的二叉排序树变成递减有序
void reverseLR(bitree root){
    if(root!=null){
        reverseLR(root->lchild);
        reverseLR(root->rchild);
        tnode*temp=root->lchild;
        root->lchild=root->rchild;
        root->rchild=temp;
    }
}

//8.以邻接矩阵存储的有向无环图，求图中最长路径的长度
int lengestpath(int mg[][maxsize],int mn){
    int i,j,k;int max=0;int a[][maxsize];
    for(i=0;i<mn;++i)
        for(j=0;j<mn;++j){
            if(mg[i][j]<0x7fffffff)
                a[i][j]=-mg[i][j];
            else
                a[i][j]=mg[i][j];
        }
    for(k=0;k<mn;++k)
        for(i=0;i<mx;++i)
            for(j=0;j<mn;++j)
                if(a[i][j]>a[i][k]+a[k][j])
                    a[i][j]=a[i][k]+a[k][j];
    for(i=0;i<mn;++i)
        for(j=0;j<mn;++j){
            if(a[i][j]<0x7fffffff && max<-a[i][j])
                max=-a[i][j];
        }
    return max;
}

//8.2 东西车过桥，只能一个方向，桥上最多5个
#define semaphore int
semaphore mutex=1;
semaphore wmutex=1;
semaphore emutex=1;
semaphore roadwidth=5;
int westcount=0,eastcount=0;

westvehicle(){
    while(1){
        p(wmutex);
        if(westcount==0)
            p(mutex);
        westcount++;
        v(wmutex);
        p(roadwidth);
        cross();
        v(roadwidth);
        p(wmutex);
        westcount--;
        if(westcount==0)
            v(mutex);
    }
}
westvehicle(){
    while(1){
        p(emutex);
        if(eastcount==0)
            p(mutex);
        eastcount++;
        v(emutex);
        p(roadwidth);
        cross();
        v(roadwidth);
        p(emutex);
        eastcount--;
        if(eastcount==0)
            v(mutex);
    }
}

