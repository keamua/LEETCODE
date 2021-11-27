//5.1 基本概念
//5.2 结构
typedef struct bitnode{
    int data;
    struct bitnode *lchild,*rchild;
}bitnode,*bitree;

//5.2.5 顺序存储的二叉树寻找最近公共节点
int comm_ancestor(int t[],int i,int j){
    if(t[i]!='#'&&t[j]!='#'){
        while(i!=j){
            if(i>j)
                i=i/2;
            else
                j=j/2;
        }
        return t[i];
    }
}

//5.3
//遍历
void visit(bitnode *t){
    int vi = t->data;
}

void preorder(bitree t){
    if(t!=null){
        visit(t);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}

void inorder(bitree t){
    if(t!=null){
        inorder(t->lchild);
        visit(t);
        inorder(t->rchild);
    }
}

void postorder(bitree t){
    if(t!=null){
        postorder(t->lchild);
        postorder(t->rchild);
        visit(t);
    }
}

//中序遍历非递归
void inorder2(bitree t){
    stack s;
    initstack(s);
    bitree p=t;
    while(p||!stackempty(s)){
        if(p){
            push(s,p);
            p=p->lchild;
        }
        else{
            pop(s,p);visit(p);
            p=p->rchild;
        }
    }
}

//先序遍历非递归
void preorder2(bitree t){
    stack s;initstack(s);
    bitree p=t;
    while(p||!stackempty(s)){
        if(p){
            visit(p);
            push(s,p);
            p=p->lchild;
        }
        else{
            pop(s,p);
            p=p->rchild;
        }
    }
}

//后序遍历非递归
void postorder2(bitree t){
    stack s;initstack(s);
    bitree p=t,r=null;
    while(p||!stackempty(s)){
        if(p){
            push(s,p);
            p=p->lchild;
        }
        else{
            gettop(s,p);
            if(p->rchild!=null&&p->rchild!=r)
                p=p->rchild;
            else{
                pop(s,p);
                visit(p);
                r=p;
                p=null;
            }
        }
    }
}

//层次遍历
void levelorder(bitree t){
    queue q;initqueue(q);
    bitree p = t;
    enqueue(q,t);
    while(!isempty(q)){
        dequeue(q,p);
        visit(p);
        if(p->lchild !=null)
            enqueue(q,p->lchild);
        if(p->rchild !=null)
            enqueue(q,p->rchild);
    }
}

//线索二叉树
typedef struct threadnode{
    int data;
    struct threadnode *lchild,*rchild;
    int ltag,rtag;
}threadnode, *threadtree;

//中序遍历线索化,pre:刚刚访问过的节点
void inthread(threadtree p,threadtree pre){
    if(p!=null){
        inthread(p->lchild,pre);
        if(p->lchild==null){
            p->lchild=pre;
            p->ltag=1;
        }
        if(pre!=null&&pre->rchild==null){
            pre->rchild=p;
            pre->rtag=1;
        }
        pre=p;
        inthread(p->rchild,pre);
    }
}
void creatinthread(threadtree t){
    threadtree pre=null;
    if(t!=null){
        inthread(t,pre);
        pre->rchild=null;
        pre->rtag=1;
    }
}

//遍历中序线索二叉树
threadnode *firstnode(threadnode *p){
    while (p->ltag==0) p=p->lchild;
    return p;
}
threadnode *nextnode(threadnode *p){
    if(p->rtag==0) return firstnode(p->rchild);
    else return p->rchild;
}
void inorder(threadtree t){
    for(threadnode *p=firstnode(t);p!=null;p=nextnode(p))
        visit(p);
}

//应用题
//4.自下而上，自右到左的遍历
void invertlevel(bitree t){
    stack s;queue q;bitree p;
    initstack(s);initqueue(q);
    if(t!=null){
        enqueue(q,t)
        while(!isempty(q)){
            dequeue(q,p);push(s,p);
            if(p->lchild!=null)
                enqueue(q,p->lchild);
            if(p->rchild!=null)
                enqueue(q,p->rchild);
        }
        while(!stackempty(s)){
            pop(s,p);
            visit(p);
        }
    }
}

//5.非递归算法求树的高度
int bidepth(bitree t){
    if(!t)
        return 0;
    int front=-1,rear = -1;
    int last =0,level =0;
    bitree q[50];
    q[++rear]=t;
    bitree p;
    while(front<rear){
        p=q[++front];
        if(p->lchild)
            q[++rear]=p->lchild;
        if(p->rchild)
            q[++rear]=p->rchild;
        if(front==last){
            level++;
            last=rear; //每当front等于last的时候，rear指向了下一层的第一个，因为此时出队列的front是上一层的最后一个，那么他的孩子也是下一层的最后一个。
        }
    }
    return level;
}
//递归实现
int btdepth2(bitree t){
    if(t==null)
        return 0;
    int ldep=btdepth2(t->lchild);
    int rdep=btdepth2(t->rchild);
    if(ldep>rdep)
        return ldep+1;
    else 
        return rdep+1;
}



//6.由先序和中序数列来求二叉树。
bitree preincreat(int a[],int b[],int l1,int h1,int l2,int h2){
    bitnode *root = (bitnode *)malloc(sizeof(bitnode));
    root->data=a[l1];//先序遍历的第一个是根节点
    int i;
    for(i=l2;b[i]!=root->data;i++); //中序遍历从根节点分成了左右子树两部分
    int llen = i -l2; //左子树大小
    int rlen = h2-i;    //右子树大小
    if(llen)
        root->lchild = preincreat(a,b,l1+1,l1+llen,l2,l2+llen-1); //在左子树上进行找左子树的根节点
    else   
        root->lchild = null;
    if(rlen)
        root->rchild = preincreat(a,b,h1-rlen+1,h1,h2-rlen+1,h2); //右子树上找右子树的根节点
    else
        root->rchild = null;
    return root;
}

//7.判断链表二叉树是否是完全二叉树,层次遍历直到没有空节点
bool iscomplete(bitree t){
    bitree p=t;
    if(!t)
        return 1;
    queue q;initqueue(q);
    enqueue(t);
    while(!isempty(q)){
        dequeue(q,p);
        if(p){
            enqueue(q,p->lchild);
            enqueue(q,p->rchild);
        }
        else{ //当p为空的时候，必然是队列中为空的时候，即已经遍历完，如果在进队列是进了一个null，则到这里能检测出来
            while(isempty(q)){
                dequeue(q,p);
                if(p) return 0;
            }
        }
    }
    return 1;
}

//8.计算二叉树所有双分支节点个数
int dsonnodes(bitree t){
    if (t==null)
        return 0;
    if(t->rchild!=null&&t->lchild!=null)
        return dsonnodes(t->lchild)+dsonnodes(t->rchild)+1;
    else
        return dsonnodes(t->lchild)+dsonnodes(t->rchild);
}

//9.所有节点左右子树进行交换
void swap(bitree t){
    if(t){
        swap(t->lchild);
        swap(t->lchild);
        bitnode *temp = t->lchild;
        t->lchild = t->rchild;
        t->rchild = temp;
    }
}

//10.求先序遍历第k个节点的值
int i1=1;
int prenode(bitree t,int k){
    if(t==null){
        return -1;
    }
    if(i1==k)
        return t->data;
    i1++;
    int num=prenode(t->lchild,k);
    if(num != -1)
        return num;
    num = prenode(t->rchild,k);
    if(num != -1)
        return num;
}

//11.删除二叉树中每个以x的值为节点的树，释放空间。
void deletetree(bitree t){
    if(t){
        deletetree(t->lchild);
        deletetree(t->rchild);
        free(t);
    }
}
void del_X_bitree(bitree t,int x){
    bitree q[50] ,p;
    if(t){
        if(t->data==x){
            deletetree(t);
            exit(0);
        }
        initqueue(q);
        enqueue(q,t);
        while(!isempty(q)){
            dequeue(q,p);
            if(p->lchild){
                if(p->lchild->data==x){
                    deletetree(p->lchild);
                    p->lchild=null;
                }
                else
                    enqueue(q,p->lchild);
            }
            if(p->rchild){
                if(p->rchild->data==x){
                    deletetree(p->rchild);
                    p->rchild=null;
                }
                else
                    enqueue(q,p->rchild);
            }
        }
    }
}

//12.输出所有值为x的节点祖先
typedef struct{
    bitree t;
    int tag;
}stackfortree;
void search_x_ancestor(bitree t,int x){
    stackfortree s[50];
    int top=0;
    while(t!=null||top>0){
        while(t!=null&&t->data!=x){
            s[++top].t=t;
            s[top].tag=0;
            t=t->lchild
        }
        if(t->data==x){
            printf("all ancestor for x:\n");        
            for(int i=0;i<=top;i++)
                printf("%d",s[i].t->data);
            exit(1);
        }
        while(top!=0&&s[top].tag==1)
            top--;
        if(top!=0){
            s[top].tag=1;
            t=s[top].t->rchild;
        }
    }
}

//13.找p和q的最近公共祖先
bitree ancestor_p_q(bitree root,bitnode *p,bitnode *q){
    int top=0,top1;stackfortree s[50],s1[50];
    bitree t=root;
    while(t!=null || top>0){
        while(t!=null){
            s[++top].t=t;
            s[top].tag=0;
            t=t->lchild;
        }
        while(top!=0&&s[top].tag==1){
            if(s[top].t==p){
                for(int i=1;i<=top;i++)
                    s1[i]=s[i];
                top1=top;
            }
            if(s[top].t==q){
                for(int i=top;i>0;i--){
                    for(int j=top1;j>0;j--)
                        if(s1[j].t==s[i].t)
                            return s[i].t;
                }
            }
            top--;
        }
        if(top!=0){
            s[top].tag=1;
            t=s[top].t->rchild;
        }
    }
    return null;
}

//14.求非空二叉树的宽度
typedef struct{
    bitree data[50];
    int level[50];
    int front,rear;
}qu;
int btwidth(bitree t){
    bitree p;
    int k,max,i,n;
    qu q;
    q.front=q.rear=-1;
    q.rear++;
    q.data[q.rear]=t;
    q.level[q.rear]=1;
    while(q.front<q.rear){
        p=q.data[q.front++];
        k=q.level[q.front];
        if(p->lchild!=null){
            q.data[q.rear++]=p->lchild;
            q.level[q.rear]=k+1;
        }
        if(p->rchild!=null){
            q.data[q.rear++]=p->rchild;
            q.level[q.rear]=k+1;
        }
    }
    max=0;i=0;
    k=1;
    while(i<=q.rear){
        int n=0;
        while(i<=q.rear&&q.level[i]==k){
            n++;i++;
        }
        k=q.level[i];
        if(n>max)
            max=n;
    }
    return max;
}

//15.用满二叉树的pre序列求post序列
void pre2post(int pre[],int l1,int h1,int post[],int l2,int h2){
    int half;
    if(h1>=l1){
        post[h2]=pre[l1];
        half = (h1-l1)/2;
        pre2post(pre,l1+1,l1+half,post,l2,l2+half-1);
        pre2post(pre,l1+half+1,h1,post,l2+half,h2-1);
    }
}

//16.叶节点从左到右构成链表
typedef struct linknode{
    int data;
    struct linknode *next;
}linknode,* linklist ;
linklist head,pre=null;
linklist inorder3(bitree t){
    if(t){
        inorder3(t->lchild);
        if(t->lchild == null &&t->rchild == null){
            if(pre == null){
                head = t;
                pre=t;
            }
            else{
                pre->next=t;
                pre=t;
            }
        }
        inorder3(t->rchild);
        pre->next=null;
    }
    return head;
}

//17.判断两个二叉树是否相似
int similar(bitree t1,bitree t2){
    int lefts,rights;
    if(t1==null&t2==null)
        return 1;
    else if(t1==null||t2==null)
        return 0;
    else{
        lefts=similar(t1->lchild,t2->lchild);
        rights=similar(t1->rchild,t2->rchild);
        return lefts&&rights;
    }
}

//18.中序线索二叉树找节点p在后续的前驱节点,根据关系的情况讨论
threadnode inpostpre(threadtree t,threadnode *p){
    threadnode *q;
    if(p->rtag==0)
        q=p->rchild;
    else if(p->ltag==0)
        q=p->lchild;
    else if(p->lchild==null)
        q=null;
    else{
        while(p->ltag==1&&p->lchild!=null)
            p=p->lchild;
        if(p->ltag==0)
            q=p->lchild;
        else   
            q=null;
    }
    return q;
}

//19.计算树的带权路径WPL
int wpl(bitree root){
    return wpl_preorder(root,0);
}
int wpl_preorder(bitree root,int deep){
    static int wpl=0;
    if(root->lchild==null&&root->rchild==null)
        wpl+=deep*root->data;
    if(root->lchild!=null)
        wpl_preorder(root->lchild,deep+1);
    if(root->rchild!=null)
        wpl_preorder(root->rchild,deep+1);
    return wpl;
}

int wpl_leverorder(bitree root){
    bitree q[100];
    int end1,end2;
    end1=end2=0;
    int wpl=0,deep=0;
    bitree lastnode;
    bitree newlastnode;
    lastnode = root;
    newlastnode = null;
    q[end2++]=root;
    while(end1!=end2){
        bitree t=q[end1++];
        if(t->lchild==null&&t->rchild==null)
            wpl+=deep*t->data;
        if(t->lchild!=null){
            q[end2++]=t->lchild;
            newlastnode = t->lchild;
        }
        if(t->rchild!=null){
            q[end2++]=t->rchild;
            newlastnode = t->rchild;
        }
        if(t=lastnode){
            lastnode = newlastnode;
            deep+=1;
        }
    }
    return wpl;
}

//20.树转化成中缀表达式
void bitree2e(bitree t){
    btree2exp(t,1);
}
void btree2exp(bitree root,int deep){
    if(root==null) return;
    else if(root->lchild == null &&root->rchild==null)
        printf("%s",root->data);
    else{
        if(deep>1)  printf("(");
        btree2exp(root->lchild,deep+1);
        printf("%s",root->data);
        btree2exp(root->rchild,deep+1);
        if(deep>1)  printf(")");
    }
}