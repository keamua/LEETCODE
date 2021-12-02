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