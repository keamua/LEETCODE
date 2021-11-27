//定长顺序串
#define maxlen 255
typedef struct{
    char ch[maxlen];
    int length;
}sstring;

typedef struct{
    char *ch;
    int length;
}hstring;

//暴力匹配
int index(sstring s,sstring t){
    int i=1,j=1;
    while(i<=s.length&&j<=t.length){
        if(s.ch[i]==t.ch[j]){
            ++i;++j;
        }
        else{
            i=i-j+2;j=1;
        }
    }
    if(j>t.length) return i-t.length;
    else return 0;
}

//KMS算法
void get_next(sstring t,int next[]){
    int i=1,j=0;
    next[1]=0;
    while (i<t.length){
        if(j==0||t.ch[i]==t.ch[j]){
            ++i;++j;
            next[i]=j;
        }
        else j=next[j];
    }
}

int index_kmp(sstring s,sstring t,int next[]){
    int i=1,j=1;
    while(i<=s.length&&j<=t.length){
        if(j==0||s.ch[i]==t.ch[j]){
            ++i,++j;
        }
        else
            j=next[j];
    }
    if(j>t.length)
        return i-t.length;
    else
        return 0;
}

void get_nextval(sstring t,int nextval[]){
    int i=1,j=0;
    nextval[i]=0;
    while(i<t.length){
        if(j==0||t.ch[i]==t.ch[j]){
            ++i,++j;
            if(t.ch[i]!=t.ch[j]) nextval[i]=j;
            else nextval[i]=nextval[j];
        }
        else
            j=nextval[j];
    }
}

