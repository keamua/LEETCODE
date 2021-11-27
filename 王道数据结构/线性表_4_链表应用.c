#include("线性表_3_链表结构.h")
//单链表
typedef struct lnode{
    int data;
    struct lnode *next;
}lnode, *linklist;

//1.递归实现不带头节点的链表中删除值为x的节点
void del_x_3(linklist &l,int x){
    lnode *p;
    if(l==null)
        return;
    if(l->data==x){
        p=l;
        l=l->next;
        free(p);
        del_x_3(l,x);
    }
    else
        del_x_3(l->next,x);
}

//2.删除带头节点l中所有值为x的节点
void del_X_1(linklist &l, int x){
    lnode *p=l->next,*pre=l,*q;
    while(p!=null){
        if(p->data==x){
            q=p;
            p=p->next;            
            pre->next=p;
            free(q);
        }
        else{
            pre=p;
            p=p->next;
        }
    }
}
//或者把不等于x的插到新表中
void del_x_2(linklist &l,int x){
    lnode *p=l->next,*r=l,*q;
    while(p!=null){
        if(p->data!=x){
            r->next=p;
            r=p;
            p=p->next;
        }
        else{
            q=p;
            p=p->next;
            free(q);
        }
    }
    r->next=null;
}

//3.反向输出链表的值
void r_print(linklist l){
    if(l->next!=null)
        r_print(l->next);
    if(l!=null) print(l->data);
}
void r_ignore_head(linklist l){
    if(l!=null) r_print(l->next);
}

//4.删除链表中的最小值
linklist delete_min(linklist &l){
    lnode *pre=l,*p=pre->next;
    lnode *minpre=pre,*minp=p;
    while(p!=null){
        if(p->data<minp->data){
            minp=p;
            minpre=pre;
        }
        pre=p;
        p=p->next;
    }
    minpre->next = p->next;
    free(minp);
    return l;
}

//5. 就地逆置(带头节点)
linklist reverse_1(linklist l){
    lnode *p,*r;
    p=l-next;
    l->next=null;
    while(p!=null){
        r=p->next;
        p->next= l->next;
        l->next =p;
        p = r;
    }
    return l;
}
linklist reverse_2(linklist l){
    lnode *pre,*p=l->next,*r=p->next;
    p->next=null;
    while(r!=null){
        pre = p;
        p =r;
        r = r->next;
        p ->next=pre;
    }
    l->next=p;
    return l;
}


//6.单链表节点重排递增有序(插入排序)
void sort(linklist &l){
    lnode *p=l->next,*pre;
    lnode *r=p->next;
    p->next = null; //此时的链表只有头节点和第一个节点
    p = r; //此时的p为第二个节点
    while(p!=null){
        r=p->next; //r为第三个节点，及下一轮的要插入到l中的节点
        pre=l;
        while(pre->next!=null&&pre->next->data<p->data) //找到合适的插入位置
            pre=pre->next;
        p->next=pre->next;
        pre->next=p;
        p=r; //下一个
    }
}

//7.无序单链表删除两个值之间的节点
void rangedelete(linklist &l,int min,int max){
    lnode *pre=l,*p=l->next;
    while(p!=null)
        if(p->data<max&&p->data>min){
            pre->next = p->next
            free(p);
            p=pre->next;
        }
        else{
            pre=p;
            p=p->next;
        }
}


//8.找出两个链表的公共节点
linklist  search_1st_common(linklist l1,linklist l2){
    int len1=length(l1),len2=length(l2),dist;
    linklist longlist,shortlist;
    if(len1>len2){
        longlist=l1->next;shortlist->next=l2->next;
        dist = len1-len2;
    }
    else{
       longlist=l2->next;shortlist->next=l1->next;
        dist = len2-len1; 
    }
    while(dist--){
        longlist=longlist->next;
    }
    while(longlist!=null){
        if(longlist = shortlist)
            return longlist;
        else{
            longlist=longlist->next;
            shortlist=shortlist->next;
        }
    }
    return null;
}

//9.带头节点链表递增顺序输出并删除节点
void min_delete(linklist &l){
    while(l->next!=null){
        lnode *pre=l,*p=pre->next;
        while(p->next!=null){
            if(p->next->data < pre->next->data)
                pre=p;
            p=p->next;
        }
        print(pre->next->data);
        lnode *q=pre->next;
        pre->next=q->next;
        free(q);
    }
    free(l);
}

//10.把一个链表的奇偶个数裁开成两个链表
linklist discreat_1(linklist &a){
    linklist b=(linklist)malloc(sizeof(lnode));
    lnode *p=a->next,*ra=a,*rb=b;a->next=null;b->next=null;
    while(p!=null){
        rb->next=p;
        rb=p;
        ra->next=p->next;
        ra = p->next;
        p=p->next->next;
    }
    ra->next = null;
    rb->next = null;
    return b;
}

//11.拆开b倒序.
linklist discreat_2(linklist &a){
    linklist b=(linklist)malloc(sizeof(londe));
    b-next=null;
    lnode *p=a->next,*q;
    lnode *ra=a;
    while(p!=null){
        ra->next=p;ra=p;
        p=p->next;
        if(p!=null) q=p->next;
        p->next=b->next;
        b->next=p;
        p=q;
    }
    ra->next=null;
    return b;
}


//12.去掉递增有序链表中一样的元素。
void del_same(linklist &l){
    lnode *p=l->next,*q;
    while(p!=null){
        q=p->next;
        if(p->data=q->data){
            p->next=q->next;
            free(q);
        }
        else{
            p=p->next;
        }
    }
}


//13.两个递增归并成递减，且用原来的空间作为新链表
void mergelist(linklist &la,linklist &lb){
    lnode *r,*pa=la->next,*pb=lb->next;
    la->next=null;
    while(pa&&pb){
        if(pa->data<pb->data){
            r=pa->next;
            pa->next = la->next;
            la->next = pa;
            pa=r;
        }
        else{
            r=pb->next;
            pb->next = la->next;
            la->next = pb;
            pb =r;            
        }
    }
    if(pa)
        pb=pa;
    while(pb){
        r=pb->next;
        pb->next = la->next;
        la->next = pb;
        pb =r;
    }
    free(lb);
}


//14.从递增有序的两个链表的公共元素生成c
linklist get_common(linklist a,linklist b){
    lnode *p=a->next,*q=b->next,*r,*s;
    linklist c=(linklist)malloc(sizeof(lnode));
    r=c;
    while(p!=null&&q!=null){
        if(p->data < q->data)
            p=p->next;
        else if(p->data > q->data)
            q=q->data;
        else{
            s=(lnode *)malloc(sizeof(lnode));
            s->data = p->data;
            r->next = s;
            r=s;
            p=p->next;
            q=q->next;
        }
    }
    r->next = null;
}

//15.求两个递增序列的交集，就一个
linklist union(linklist &la,linklist &lb){
    lnode *pa=la->next,*pb = lb->next, *pc=la, *u;
    while(pa&&pb){
        if(pa->data == pb->data){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            u=pb;
            pb = pb->next;
            free(u);
        }
        else(pa->data < pb->data){
            u = pa;
            pa = pa-next;
            free(u);
        }
        else{
            u = pb;
            pb = pb->next;
            free(u);
        }
    }
    while(pa){
        u=pa;
        pa=pa->next;
        free(u);
    }
    while(pb){
        u=pb;
        pb=pb->next;
        free(u);
    }
    pc->next = null;
    free(lb);
    return la;
}

//16.判断b链表是否是a链表的子序列
int pattern (linklist a,linklist b){
    lnode *p=a->next,*q=b->next,*pre=p;
    while(p&&q){
        if(p->data == q->data){
            p=p->next;
            q=q->next;
        }
        else{
            pre=pre->next;
            p=pre;
            q=b;
        }
    }
    if(q==null)
        return 1;
    else
        return 0;    
}


//17.判断带头节点的循环双链表是否对称
bool symmetry(dlinklist l){
    dnode *p=l->next,*q=l->prior;
    while(p!=q&&q->next!=p){
        if(p->data == q->data){
            p=p->next;
            q=q->prior;
        }
        else
            return false;
    }
    return ture;
}

//18.将一个循环链表连接到另一个循环链表的后面
linklist link(linklist &h1,linklist &h2){
    lnode *p,*q;
    p=h1;
    q=h2;
    while(p->next!=h1)
        p=p->next;
    while(q->next!=h2)
        q=q->next;
    p->next = h2;
    q->next = h1;
    return h1;
}

//19.循环链表一直删除最小的值
void delete_all(linklist &l){
    lnode *p,*pre,*minp,*minpre;
    while(l->next!=l){
        p=l->next;pre = l;
        minp=p;minpre=pre;
        while(p!=l){
            if(p->data < minp->data){
                minp=p;
                minpre=pre;
            }
            pre=p;
            p=p->next;
        }
        printf("%d",minp->data);   
        minpre->next=minp->next;
        free(minp);        
    }
    free(l);
}


//20.带头节点的双向非循环链表，按频度递减排列
dlinklist locate(dlinklist &l, int x){
    dnode *p=l->next,*q;
    while(p->data!=x&&p){
        p=p->next;
    }
    if(!p){
        printf("不存在值为x的节点\n");
        exit(0);
    }
    else{
        p->freq++;
        if(p->next!=null) p->next->prior = p->prior;
        p->prior->next = p->next;
        q=p->prior;
        while(q!=l&&q->freq<=p->freq)
            q=q->prior;
        p->next=q->next;
        p->prior=q;
        q->next->prior=p;
        q->next=p;
    }
    return p;
}


//21. 查找倒数第k个位置的节点
int search_k(linklist l,int k){
    lnode *p=l->next,*q=p;
    int count=0;
    while(p!=null){
        if(count<k)
            count++;
        else
            q=q->next;
        p=p->next;        
    }
    if(count<k)
        return 0;
    else{
        printf("%d",q->data);
        return 1;
    }
}

//22.找字符串共同后缀起始位置
int listlen(lnode *head){
    int len = 0;
    while(head->next!=null){
        len++;
        head=head->next;
    }
    return len;
}
lnode* find_addr(lnode *s1,lnode *s2){
    int m=listlen(s1),n=listlen(s2);
    lnode *p,*q;
    for(p=s1;m>n;m--){
        p=p->next;
    }
    for (q=s2; n>m; n--)
        q=q->next;
    while(p->next!=null&&q->next!=null){
        p=p->next;
        q=q->next;
    }
    return p->next;   
}

//23.删除绝对值小于n，相等的节点，保留第一个.
void delete_abs_same(linklist l,int n){
    lnode *p=l,r;
    int *q,m;
    q=(int *)malloc(sizeof(int)*(n+1));
    for(int i=0;i<n+1;i++)
        *(q+i)=0;
    while(p->next!=null){
        m=p->next->data > 0? p->next->data:-p->next->data;
        if(*(q+m)==0){
            *(q+m)=1;
            p=p->next;
        }
        else{
            r=p->next;
            p->next=r->next;
            free(r);
        }
    }
    free(q);
}

//24.判断一个链表是否有环，如果有返回环的入口节点
lnode *findloopstart(lnode *head){
    lnode *fast=head,*slow=head;
    while(slow!=null&&fast->next!=null){
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast)
            break;
    }
    if(slow==null||fast->next==null){
        return null;
    }
    lnode *p1=head,*p2=slow;
    while(p1!=p2){
        p1=p1->next;
        p2=p2->next;
    }
    return p1;
}


//25.把1，2，3，……，n-1，n，改成1，n，2，n-1这样
void changelist(lnode *l){
    lnode *p,*q,*r,*s;
    p=q=l;
    while(q->next!=null){
        p=p->next;
        q=q->next;
        if(q->next!=null)
            q=q->next;
    }//找p是链表的中点
    q=p->next;
    p->next=null;
    while(q!=null){
        r=q->next;
        q->next=p->next;
        p->next = q;
        q=r;
    }
    s=l->next;
    q=p->next;
    p->next=null;
    while(q->null){
        r=q->next;
        q->next = s->next;
        s->next = q;
        s=q->next;
        q=r;
    }
}