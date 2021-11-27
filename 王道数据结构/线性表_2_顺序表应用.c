//题的答案解析
#include("线性表_1_顺序表结构.h")

//1.删除最小元素，并用最后的填充上
bool delmin(sqlist &l,int &value){
    if(l.length == 0)
        return false;
    value = l.data[0];
    int pos;
    for(int i =1;i<l.length;i++)
        if(l.data[i]<value){
            value = l.data[i];
            pos = i;
        }
    l.data[pos]= l.data[l.length-1];
    l.length --;
    return true;
}
//函数返回值只能返回一个值，而引用传参能返回多个值



//2.顺序表所有元素逆置
void reverse(sqlist &l){
    int temp;
    for(i=0;i<l.length/2;i++){
        temp = l.data[i];
        l.data[i]=l.data[l.length-1 - i ];
        l.data[l.length-1-i] = temp;
    }
}

//3.删除线性表中所有值为x的元素
void del_x_1(sqlist &l, int x){
    int k = 0;//用来记录不等于x的元素个数
    for(int i =0;i<l.length;i++)
        if(l.data[i]!=x){
            l.data[k]=l.data[i]; //不为x的元素迁移
            k++;
        }
    l.length = k;
}
void del_x_2(sqlist &l, int x){
    int k=0;i=0;
    while(i<l.length){
        if(l.data[i]==x)
            k++;
        else
            l.data[i-k]=l.data[i];
        i++;
    }
    l.length = l.length - k;      
}

//4.删除有序表中所有值在s t之间的元素
void del_s_t(sqlist &l,int s,int t){
    int i,j;
    if(s>t||l.length==0)
        return false;
    for(i=0;i<l.length&&l.data[i]<s;i++);
    if (i>=l.length)
        return false;
    for(j=0;j<l.length&&l.data[j]<=t; j++);
    for(;j<l.length;i++,j++)
        l.data[i]=l.data[j]; //元素迁移
    l.length=i;
    return ture;
}

//5.删除顺序表中在s.t之间的元素
bool del_s_t2(sqlist &l,int s,int t){
    int i,j,k;
    if(l.length == 0||s>=t)
        return false;
    for(i=0;i<l.length;i++){
        if(l.data[i]>s&&l.data[i]<t)
            k++;
        else
            l.data[i-k]=l.data[i];
    }
    l.length -= k;
    return true;
}
        

//6.删除有序表中所有值重复的元素
bool deleta_same(seqlist &l){
    if(l.length==0)
        return false;
    int i,j;
    for(i=0,j=1;j<l.length;j++)
        if(l.data[i]!=l.data[j])
            l.data[++i] = l.data[j]; //相当于取不相等的放到前面
    l.length =i+1;
    return ture;
}  
    

//7.合并两个有序顺序表a，b到c
bool merge(seqlist a,seqlist b,seqlist &c){
    if(a.length+b.length>c.maxsize)
        return false;
    int i=0,j=0,k=0;
    while(i<a.length&&j<b.length){
        if(a.data[i]<b.data[j])
            c.data[k++]=a.data[i++];
        else
            c.data[k++]=b.data[j++];
    }
    while(j<b.length)
        c.data[k++]=b.data[j++];
    while(i<a.length)
        c.data[k++]=a.data[i++]
    c.length = k;
    return ture;
}

//8.将一个顺序表中存放的两个表a与b的位置互换,思想，翻a，翻b，翻ab即可
void reverse(int a[],int left,int right,int arraysize){
    if(left>right||right>arraysize)
        return;
    int mid = (left+right)/2,temp;
    for(int i = 0;i<mid;i++){
            temp = a[left + i];
            a[left + i] = a[right - i];
            a[right - i] = temp;
    }
}
void exchange(int a[],int m ,int n,int arraysize){
    reverse(a,0,m+n-1,arraysize);
    reverse(a,0,n-1,arraysize);
    reverse(a,n,m+n-1,arraysize);
}


//9.顺序存储递增的有序表，找到x值则与后继交换，找不到则插入。
void searchexchangeinsert(int a[],int x){
    int low = 0,high = n,mid;
    while(low<=high){
        mid = (low+high)/2;
        if (a[mid]==x) break;
        else if(a[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    if (a[mid]==x){
        int t = a[mid];
        a[mid] = a[mid+1];
        a[mid+1] = t;
    }
    if(low>high){
        int i;
        for(i = n-1;i>high;i--)
            a[i+1] = a[i];
        a[i+1]=x;
    }
}


//10.数组ab到ba，和8相同


//11.求两个等长升序序列的中位数
int m_search(int a[],int b[],int n){
    int s1=0,d1=n-1,m1,s2=0,d2=n-1,m2;
    while(s1!=d1||s2!=d2){
        m1 = (s1+d1)/2;
        m2 = (s2+d2)/2;
        if(a[m1]==b[m2])
            return a[m1];
        else if (a[m1]<b[m2]){
            if((s1+d1)%2==0){   //元素个数为奇数
                s1=m1;
                d2=m2;
            }
            else{
                s1=m1+1;
                d2=m2;
            }
        }
        else{
            if((s2+d2)%2==0){
                d1=m1;
                s2=m2;
            }
            else{
                d1=m1;
                s2=m2+1;
            }
        }
    }
    return a[s1]<b[s2]?a[s1]:b[s2];
}

//12.主元素的选择，若有超过一半的值在数组中，则相同+1不同-1对他是一定成立的
int majority(int a[],int n ){
    int i,c,count =1;
    c = a[0];
    for(i=1;i<n;i++){
        if(a[i]==c)
            count++;
        else
        {
            if(count>0)
                count--;
            else
                c=a[i];
                count = 1;
        }
    }
    if (count>0)
        for(i=count=0;i<n;i++)
            if(c==a[i])
                count++;
    if(count>n/2) return c;
    else return -1;    
}


//13.找到数组中未出现的最小整数
int findmissmin(int a[],int n){
    int i,*b;   //b用来表示是否有存在
    b = (int*)malloc(sizeof(int)*n);
    memset(b,0,sizeof(int)*n);
    for(i=0;i<n;i++)
        if(a[i]>0&&a[i]<=n)
            b[a[i]-1]==1;
    for(i=0;i<n;i++)
        if(b[i]==0) break;
    return i+1;
}


//14.找三个升序序列中选出来的元素所构成的三元组，令其距离最小
#define INT_MAX 0x7fffffff
int abs(int a){
    return a>0?a:-a;
}
bool xls_min(int a,int b, int c){
    if(a<=b&&a<=c) return ture;
    return false;
}
int findminoftrip(int a[],int n,int b[],int m,int c[],int p){
    int i=0,j=0,k=0,min=INT_MAX,d;
    while(i<n&&j<m&&k<p&&min>0){
        d=abs(a[i]-b[j])+abs(a[i]-c[k])+abs(b[j]-c[k]);
        if(d<min) min=d;
        if(xls_min(a[i],b[j],c[k])) i++;
        else if(xls_min(b[j],c[k],a[i]))    j++;
        else k++;
    }
    return min;
}