//1.求一个已经排好序的旋转数组的最小值
int min(int *numbers,int length){
    if(numbers==0||length<=0)
        return 0;
    int index1=0;
    int index2=length-1;
    int indexmid= index1;
    while(numbers[index1]>=numbers[index2]){
        if(index2-index1==1){
            indexmid = index2;
            break;
        }
        indexmid =(index1 +index2)/2;
        if(numbers[indexmid]>=numbers[index1])
            index1=indexmid;
        else if(numbers[index2]>=numbers[indexmid])
            index2=indexmid;
    }
    return numbers[indexmid];
}

//2.m+n个元素的数组前m个有序，后n个有序，排列成全有序
void merge(int *a,int m,int n){
    int *b= (int *)malloc(sizeof(int)*(m+n+1));
    int k1,k2,k3;
    k1=1;k2=m+1;k3=1;
    while(k1<=m&&k2<=m+n){
        if(a[k1]<a[k2])
            b[k3++]=a[k1++];
        else
            b[k3++]=a[k2++];
    }
    if(k1>m)
        while(k2<=m+n) b[k3++]=a[k2++];
    else
        while(k1<=m)   b[k3++]=a[k1++];
    for(int i=1;i<=m+n;i++)
        a[i]=b[i];
    free(b);
}

//3.判断一个单链表是否中心对称，xxyyxx
typedef struct lnode{
    char data;
    struct lnode *next;
} *linklist,lnode;
int str_sym(linklist l,int n){
    stack s;initstack(s);
    lnode *q,*p=l->next;
    for(int i=0;i<=n/2;i++){
        push(s,p);
        p=p->next;
    }
    if(n%2==1)  p=p->next;
    while(p!=null){
        pop(s,q);
        if(q->data==p->data)    p=p->next;
        else break;
    }
    if(isempty(s))
        return 1;
    else
        return 0;
}

//4.二叉树中求根节点到某给定节点的路径
typedef struct btnode{
    int data;
    struct btnode *lchild,*rchild;
}btnode,*bitree;
#define maxsize 100
int ancestopath(bitree t,btnode *s){
    btnode* st[maxsize];
    btnode *p;
    int i,flag,top=-1;
    do{
        while(t!=null){
            st[++top]=t;
            t=t->lchild;
        }
        p=null;
        flag=1;
        while(top!=-1&&flag){
            t=st[top];
            if(t->rchild==p){
                if(t==s){
                    for(int i=0;i<=top;++i)
                        printf("%c",st[i]->data);
                    return 1;
                }
                else{
                    top--;
                    p=t;
                }
            }
            else{
                t=t->rchild;
                flag=0;
            }
        }
    }while(top!=-1);
    return 0;
}

//5.求数组中数对之差的最大值，数对之差，数组中的数和他右边的数的差的最大值
//a.分治法
int maxdiff_solution1(int numbers[],unsigned length){
    if(numbers==null||length<2)
        return 0;
    int max,min;
    return maxdiffcore(numbers,numbers+length-1,&max,&min);
}
int maxdiffcore(int *start,int *end, int *max,int *min){
    if(end==start){
        *max=*min=*start;
        return 0;
    }
    int *middle = start+(end-start)/2;
    int maxleft,minleft;
    int leftdiff=maxdiffcore(start,middle,&maxleft,&minleft);
    int maxright,minright;
    int rightdiff=maxdiffcore(middle+1,end,&maxright,&minright);
    int crossdiff=maxleft-minright;
    *max=(maxleft>maxright)?maxleft:maxright;
    *min=(minleft<minright)?minleft:minright;
    int maxdiff=(leftdiff>rightdiff)?leftdiff:rightdiff;
    maxdiff=(maxdiff>crossdiff)?maxdiff:crossdiff;
    return maxdiff;
}
//b.动态规划法
int maxdiff_solution2(int numbers[],unsigned length){
    if(numbers==null||length<2)
        return 0;
    int max=numbers[0];
    int maxdiff=max-numbers[1];
    for(int i=2;i<length;i++){
        if(numbers[i-1]>max)
            max=numbers[i-1];   //max是到数组第i个的最大值
        int currentdiff=max-numbers[i]; //用最大值减第i个值
        if(currentdiff>maxdiff);    //如果比上个数对差要大，则替换
            maxdiff=currentdiff;
    }
    return maxdiff;
}
//pv问题：猴子过绳索，只有一根绳，一个方向的可以一直过
int smonkeyconut = 0;
int nmonkeycount = 0;
#define semaphore int
semaphore mutex=1;
semaphore smutex=1;
semaphore nmutex=1;
process_south_i(){
    while(1){
        p(smutex);
        if(smonkeyconut==0);
            p(mutex);
        smonkeyconut++;
        v(smutex);
        //过桥
        p(smutex);
        smonkeyconut--;
        if(smonkeyconut==0)
            v(mutex);
        v(smutex);
    }
}
process_north_i(){
    while(1){
        p(nmutex);
        if(nmonkeycount==0)
            p(mutex);
        nmonkeycount++;
        v(nmutex);
        //过桥
        p(nmutex);
        nmonkeycount--;
        if(nmonkeycount==0)
            v(mutex);
        v(nmutex);
    }
}


//6.将数组中所有的奇数号元素移到偶数号元素的前面
void bobble_swap(int a[],int n){
    int i=n,v=1;
    int temp;
    if(n%2==0)  i=n-1;
    while(i>1){
        temp=a[i-1];
        for(int j=0;j<v;j++)//在数组最后的连续的奇数从1个、2个慢慢增加，每次这些个奇数向前移动一位，把最后的位置给之前的那个偶数
            a[i-1+j]=a[i+j];
        a[i+v-1]=temp;
        i=i-2;v++;
    }
}

//7.求一个数组的连续子数组的最大值
//a.
int maxsum1(int n,int a[]){
    int sum=0,b=0;
    for(int i=0;i<=n;i++){
        if(b>0) b+=a[i];
        else b=a[i];
        if(b>sum)   sum=b;
    }
    return sum;
}

//b.
int maxsum2(int a[],int left,int right){
    if(left==right)
        return max(a[left],0);
    int mid=(left+right)/2;
    int lmax=0,lsum=0;
    for(int i=mid;i>=left;i--){
        lsum+=a[i];
        if(lsum>lmax)
            lmax=lsum;
    }
    int rmax=0,rsum=0;
    for(int i=mid+1;i<=right;i++){
        rsum+=a[i];
        if(rsum>rmax)
            lmax=lsum;
    }
    return max(lmax+rmax,max(maxsum2(a,left,mid),maxsum2(a,mid+1,right)));
}

//8.求二叉树某一层k，的叶子节点个数
int leafklevel(bitree t,int k){
    btnode *q[maxsize];
    int end1,end2,sum=0;
    end1=end2=0;
    int deep=0;
    btnode *lastnode,*newlastnode;
    lastnode=t;
    newlastnode=null;
    q[end2++]=t;
    while(end2!=end1){
        btnode *p=q[end1++];
        if(k==deep){
            while(end2!=end1){
                p=q[end1++];
                if(p->lchild==null&&p->rchild==null)
                    ++sum;
            }
            break;
        }
        else{
            if(p->lchild!=null){
                q[end2++]=t->lchild;
                newlastnode=t->lchild;
            }
            if(t->rchild!=null){
                q[end2++]=t->rchild;
                newlastnode=t->rchild;
            }
            if(t==lastnode){
                lastnode=newlastnode;
                deep+=1;
            }
        }
    }
    return sum;
}

//b.
int n;
int leafklevel2(bitree t,int k){
    n=0;
    preorder(t,0,k);
    return 0;
}
int preorder(bitree t,int deep,int k){
    if(deep<k){
        if(t->lchild!=null)
            preorder(t->lchild,deep+1,k);
        if(t->rchild!=null)
            preorder(t->rchild,deep+1,k);
    }
    else if(deep==k&&t->lchild==null&&t->rchild==null)
        ++n;
    
}

