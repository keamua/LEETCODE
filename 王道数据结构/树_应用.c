//5.4 树和森林
//双亲表示法
#define maxsize 100
typedef struct{
    int data;
    int parent;
}ptnode;
typedef struct{
    ptnode nodes[maxsize];
    int n;
}ptree;

//孩子兄弟表示法
typedef struct csnode{
    int data;
    struct csnode *firstchild,*nextsibling;
}csnode,*cstree;

//5.求孩子兄弟表示法的叶子节点个数
int leaves(cstree t){
    if(t==null){
        return 0;
    }
    if(t->firstchild==null)
        return 1+leaves(t->nextsibling);
    else
        return leaves(t->firstchild)+leaves(t->nextsibling);
}

//6.孩子节点递归求树的深度
int height(cstree t){
    int hc,hs;
    if(t==null)
        return 0;
    else{
        hc=height(t->firstchild);
        hs=height(t->nextsibling);
        if(hc+1>hs)
            return hc+1;
        else
            return hs;
    }
}

//7.已知树的层次遍历序列和每个节点的度，求其孩子兄弟表示法的链表
void createcstree_degree(cstree t,int e[],int degree[],int n){
    cstree pointer[maxsize];
    int i,j,d,k=0;
    for(i=0;i<n;i++){
        pointer[i]->data = e[i];
        pointer[i]->firstchild = pointer[i]->nextsibling = null;
    }
    for(i=0;i<n;i++){
        d=degree[i];
        if(d){
            k++;
            pointer[i]->firstchild = pointer[k];
            for(j=2;j<=d;j++){
                k++;
                pointer[k-1]->nextsibling=pointer[k];
            }
        }
    }
    t=pointer[0];
    free(pointer);
}

//二叉排序树
typedef struct{
    int data,count;
    struct btnode *lchild,*rchild;
}bstnode,*bitree;

bstnode *bst_search(bitree t,int key){
    while(t!=null&&key!=t->data){
        if(key<t->data) t=t->lchild;
        else t=t->rchild;
    }
    return t;
}

int bst_insert(bitree t,int k){
    if(t==null){
        t=(bitree)malloc(sizeof(bstnode));
        t->data = k;
        t->lchild= t->rchild =null;
        return 1;
    }
    else if (k==t->data)
        return 0;
    else if (k<t->data)
        return bst_insert(t->lchild,k);
    else
        return bst_insert(t->rchild,k);
}

//创建
void creat_bst(bitree t,int a[],int n){
    t=null;
    int i=0;
    while(i<n){
        bst_insert(t,a[i]);
        i++;
    }
}


//6.判断给定的二叉树是否是二叉排序树
int predt= -32767;

int judgebst(bitree t){
    int b1,b2;
    if(t==null)
        return 1;
    else{
        b1=judgebst(t->lchild);
        if(b1==0||predt>=t->data)
            return 0;
        predt = t->data;
        b2=judgebst(t->rchild);
        return b2;
    }
}


//7.求指定节点在二叉排序树中的层次
int level(bitree t,bstnode *p){
    int n=0;
    bitree q=t;
    if(t!=null){
        n++;
        while(p->data!=q->data){
            if(p->data<q->data)
                q=q->lchild;
            else 
                q=q->rchild;
            n++;
        }
    }
    return n;
}

//8.遍历二叉树判断是否是平衡二叉树
void judge_avl(bitree t,int balance,int h){
    int bl=0,br=0,hl=0,hr=0;
    if(t==null){
        h=0;
        balance=1;
    }
    else if(t->lchild==null && t->rchild == null){
        h=1;
        balance=1;
    }
    else{
        judge_avl(t->lchild,bl,hl);
        judge_avl(t->rchild,br,hr);
        h=(hl>hr?hl:hr)+1;
        if(abs(hl-hr)<2)
            balance = bl && br;
        else
            balance = 0;
    }
}


//9.求二叉排序树的最大关键字和最小关键字
int minkey(bitree t){
    while(t->lchild!=null)
        t=t->lchild;
    return t->data;
}
int maxkey(bitree t){
    while(t->rchild!=null)
        t=t->rchild;
    return t->data;
}


//10.从大到小输出所有值不小于k的关键字
void output(bitree t,int k){
    if(t==null)
        return ;
    if(t->rchild!=null)
        output(t->rchild,k);
    if(t->data>k)
        printf("%d",t->data);
    if(t->lchild!=null)
        output(t->lchild,k);
}

//12.查找二叉排序树中第k小的节点
bstnode *search_small(bitree t,int k){
    if(k<1||k>t->count) return null;
    if(t->lchild==null){
        if(k==1) return t;
        else return search_small(t->rchild,k-1);
    }
    else{
        if(t->lchild->count == k-1) return t;
        if(t->lchild->count > k-1) return search_small(t->lchild,k);
        if(t->lchild->count < k-1) return search_small(t->rchild,k-(t->lchild->count+1));
    }
}
