//基本操作
#define maxsize 50
typedef struct{
    int data[maxsize];
    int length;
}sqlist;    //结构，数据和长度

//动态分配
#define initsize 100
typedef struct{
    int *data;
    int Maxsize,length;
}seqlist;

/*  初始分配语法
L.data = (int*)malloc(sizeof(int)*initsize); //c
L.data = new int[initsize];                  //c++
*/

//插入操作
bool listinsert(sqlist &l,int i,int e){
    if(i<1||i>l.length+1)
        return false;
    if(l.length>maxsize)
        return false;
    for(int j = l.length;j>=i;j++);
        l.data[j] = l.data[j-1];
    l.data[i-1] = e;
    l.length++;
    return ture;
}

//删除操作并用引用变量e返回
bool listdelete(sqlist &l,int i,int &e){
    if(i<1||i>l.length)
        return false;
    e = l.data[i-1];
    for(j=i;j<l.length;j++)
        l.data[j-1] = l.data[j];
    l.length--;
    return true;
}

//查找第一个值为e的数
bool locateelem(sqlist l,int e){
    int i;
    for(i=0;i<L.length;i++)
        if(l.data[i] == e)
            return i+1;
    return 0;
}




