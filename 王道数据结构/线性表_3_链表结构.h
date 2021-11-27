//链表表示的线性表

//单链表
typedef struct lnode{
    int data;
    struct lnode *next;
}lnode, *linklist;

//头插法创建(带头节点)
linklist list_headinsert(linklist &l){
    lnode *s; int x;
    l = (linklist)malloc(sizeof(lnode));
    l->next = NULL;
    scanf("%d",&x);
    while(x!=9999){
        s=(lnode*)malloc(sizeof(lnode));
        s->data = x;
        s->next = l->next;
        l->next = s;
        scanf("%d",&x);
    }
    return l;
}

//尾插法创建
linklist list_tailinsert(linklist &l){
    int x;
    l=(linklist)malloc(sizeof(lnode));
    lnode *s,*r=l;
    scanf("%d",&x);
    while(x!=9999){
        s=(lnode*)malloc(sizeof(lnode));
        s->data=x;
        r->next=s;
        r=s;
        scanf("%d",&x);
    }
    r->next=null;
    return l;
}

//找第i个节点
lnode *getelem(linklist l,int i ){
    int j = 1;
    lnode *p=l->next;
    if(i==0)
        return l;
    while(p&&j<i){
        p=p->next;
        j++;
    }
    return p;
}

//按值查找节点
lnode *locateelem(linklist l,int e){
    lnode *p=l->next;
    while(p!=null&&p->data!=e)
        p=p->next;
    return p;
}

//插入节点
void insertnode(linklist l,lnode *s,int i){
    lnode *p=getelem(l,i);
    s->next = p->next;
    p->next = s;

    //或者插到p后面交换数据
    int temp = p->data;
    p->data = s->data;
    s->data = temp;
}

//删除节点
void deletenode(linklist l,int i){
    lnode *p=getelem(l,i-1);
    q=p->next;
    p->next=q->next;
    free(q);
}


//双链表数据结构
typedef struct dnode{
    int data;
    struct dnode *prior,*next;
}dnode, *dlinklist;

//双链表的插入与删除
void dlistdeleteandinsert(dlinklist l,int i,dnode* s){
    dnode *p;
    s->next = p->next;
    s->prior = p;
    p->next->prior = s;
    p->next=s;

    dnode* q;
    p->next = q->next;
    q->next->prior = p;
    free(q);
}

//静态链表结构，以next==-1作为结束的标志
typedef struct snode{
    int data;
    int next;
}slinklist[50]




