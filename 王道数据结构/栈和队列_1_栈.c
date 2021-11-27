//栈的结构和应用
#define maxsize 50
typedef struct{
    int data[maxsize];
    int top;
}stack;

void initstack(stack &s){
    s.top = -1;
}

bool stackempty(stack s){
    if(s.top == -1)
        return true;
    else
        return false;
}

bool stackoverflow(stack s){
    if(s.top == maxsize -1)
        return ture;
    else
        return flase;
}

bool push(stack &s,int x){
    if(s.top==maxsize-1)
        return false;
    s.data[++s.top]=x;
    return ture;
}

bool pop(stack &s,int &x){
    if(s.top==-1)
        return false;
    x=s.data[s.top--];
    return true;
}

bool gettop(stack s,int &x){
    if(s.top==-1)
        return false;
    x=s.data[s.top];
    return true;
}

//栈的链式存储结构
typedef struct linknode{
    int data;
    struct linknode *next;
}*listack;

//4.用栈判断链表是否对称
int dc(linknode l,int n){
    int i;
    char s[n/2];
    p=l->next;
    for(i=0;i<n/2;i++){
        s[i]=p->data;
        p=p->next;
    }
    i--;
    if(n%2==1)
        p=p->next;
    while(p!=null&&s[i]==p->data){
        i--;
        p=p->next;
    }
    if(i==-1)
        return 1;
    else
        return 0;
}

//5.两个共享空间的栈
typedef struct{
    int data[maxsize];
    int top[2];
}stk;
int tpush(int i,int x,stk s){
    if(i<0||i>1){
        printf("栈号不对\n");
        exit(0)''
    }
    if(s.top[i]-s.top[0]==1){
        printf("栈已满\n");
        return 0;
    }
    switch (i)
    {
    case 0:
        s.data[++s.top[0]]=x;return 1;
        break;
    case 1:
        s.data[--s.top[1]]=x;return 1;
    default:
        break;
    }
}
int tpop(int i,stk s){
    if(i<0||i>1){
        printf("栈号不对\n");
        exit(0);
    }
    switch(i){
        case 0:
        if(s.top[0]==-1){
            printf("empty\n");
            return -1;
        }
        else
        {
            return s.data[s.top[0]--];
        }
        case 1:
        if(s.top[1]==-1){
            printf("empty\n");
            return -1;
        }
        else
        {
            return s.data[s.top[1]++];
        }
        
    }
}


//3.2 队列
typedef struct{
    int data[maxsize];
    int front,rear;
}queue;

void initqueue(queue q){
    q.front=q.rear=0;
}

bool isempty(queue q){
    if(q.rear==q.front) return ture;
    else return false;
}

bool enqueue(queue q,int x){
    if((q.rear+1)%maxsize == q.front) return false;
    q.data[q.rear] = x;
    q.rear = (q.rear +1)%maxsize;
    return ture;
}

bool dequeue(queue q,int x){
    if(q.rear==q.front) return false;
    x=q.data[q.front];
    q.front=(q.front+1)%maxsize;
    return true;
}

typedef struct{
    int data;
    struct linknode *next;
}linknode;

typedef struct{
    linknode *front,*rear;
}linkqueue;

void initlqueue(linkqueue q){
    q.front=(linknode*)malloc(sizeof(linknode));
    q.frongt->next=null;
}

bool isempty2(linkqueue q){
    if(q.rear==q.front) return true;
    return false;
}

void enqueuel(linkqueue q,int x){
    linknode *s=(linknode *)malloc(sizeof(linknode));
    s->data= x;  s->next=null;
    q.rear->next = s;
    q.rear=s;
}

void dequeue(linkqueue q,int x){
    if(q.rear==q.front) return false;
    linknode *p=q.front->next;
    x=p->data;
    q.front->next = p->next;
    if(q.rear==p)
        q.rear=q.front;
    free(p);
    return true;
}

typedef struct{
    int data[maxsize];
    int front,rear,tag;
}tqueue;
//设置tag，判断队列是否是空的还是满的
int enqueue2(tqueue q,int x){
    if(q.front==q.rear&&q.tag) return 0;
    q.data[q.rear]=x;
    q.rear=(q.rear+1)%maxsize;
    tag=1;
    return 1;
}
int dequeue2(tqueue q,int x){
    if(q.front==q.rear&&tag==0) return 0;
    x=q.data[q.front];
    q.front=(q.front+1)%maxsize;
    tag=0;
    return 1;
}

//2.队列和栈实现逆置
void inverser(stack s,queue q){
    int x;
    while(!isempty(q)){
        dequeue(q,x);
        push(s,x);
    }
    while(!stackempty(s)){
        pop(s,x);
        enqueue(q,x);
    }
}

//3.用两个栈来模拟一个队列
int enqueue3(stack s1,stack s2,int e){
    int x;
    if(!stackoverflow(s1)){
        push(s1,e);
        return 1;
    }
    if(stackoverflow(s1)&&!stackempty(s2)){
        printf("queue full\n");
        return 0;
    }
    if(stackoverflow(s1)&&stackempty(s2)){
        while(!stackempty(s1)){
            pop(s1,x);
            push(s2,x);
        }
    }
    push(s1,e);
    return 1;
}
int dequeue(stack s1,stack s2,int e){
    int x;
    if(!stackempty(s2)){
        pop(s2,e);
        return 1;
    }
    if(stackempty(s1)){
        printf("empty queue\n");
        return 0;
    }
    while(!stackempty(s1)){
        pop(s1,x);
        push(s2,x);
    }
    pop(s2,e);
    return 1;
}
int queue3empty(stack s1,stack s2){
    if(stackempty(s1)&&stackempty(s2))
        return 1;
    else
        return 0;
}

//1.括号匹配
bool bracketscheck(char *str){
    stack s;int e,i=0;
    initstack(s);
    while(str[i]!="\0"){
        switch(str[i]){
            case '(': push(s,1);break;
            case '[': push(s,2);break;
            case '{': push(s,3);break;
            case ')': pop(s,e);if(e!=1) return false;break;
            case ']': pop(s,e);if(e!=2) return false;break;
            case '}': pop(s,e);if(e!=3) return false;break;
            default: break;
        }
        i++;
    }
    if(!stackempty(s)){
        printf("didnot compare\n");
        return false;
    }
    else{
        printf("ok\n")
        return ture;
    }
}

//2.调硬座软座车厢
void trainarrange(char *train){
    char *p=train,*q=p,c;
    stack s;
    initstack(s);
    int x;
    while(*p){
        if(*p=='H')
            push(s,1);
        else
            *(q++)=*p;
        p++;
    }
    while(!stackempty(s)){
        pop(s,x);
        *(q++)=c;
    }
}

//3.栈实现递归函数的运算
int p(int n,int x){
    stack s;
    initstack(s);
    int i;
    int fv1=1,fv2=2*x;
    for(i=n;i>=2;i--){
        push(s,i);
    }
    while(!stackempty){
        s.data[s.top]=2*x*fv2-2*(s.data[s.top-1])*fv1;
        fv1=fv2;
        pop(s,fv2);
    }
    if(n==0){
        return fv1;
    }
    return fv2;
}

//4.渡口管理模拟
void manager(queue q,queue q1,queue q2){
    int i=0,j=0,x;
        while(j<10){
        if(!stackempty(q1)&&i<4){
            dequeue(q1,x);
            enqueue(q,x);
            i++;
            j++;
        }
        else if(i==4&&!stackempty(q2)){
            dequeue(q2,x);
            enqueue(q,x);
            j++;
            i=0;
        }
        else{
            while(j<10&&i<4&&!stackempty(q2)){
                dequeue(q2,x);
                enqueue(q,x);
                i++;
                j++;
            }
            i=0;
        }
        if(stackempty(q1)&&stackempty(q2))
            j=11;

    }
}
