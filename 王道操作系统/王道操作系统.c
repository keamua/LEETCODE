//实现临界区互斥的基本方法
//1.软件实现方法
//1)单标志法，必须交替进入进程，一个不进，另一个也没办法
int turn;
p0(){
    while(turn!=0);
    printf("critical section");
    turn=1;
    printf("remainder section");
}
p1(){
    while(turn!=1);
    printf("critical section");
    turn=1;
    printf("remainder section");
}
//2)双标志先检查，可以连续使用，但按照1，2，3，4顺序运行时，会同时进入临界区，违背忙则等待
#define maxsize 50
bool flag[maxsize];
int i,j;
pi(){
    while(flag[j]);     //1
    flag[i]=true;       //3
    printf("critical section");
    flag[i]=false;
    printf("remainder section");
}
pj(){
    while(flag[i]);     //2
    flag[j]=true;       //4
    printf("critical section");
    flag[j]=false;
    printf("remainder section");
}
//3)双标志后检查，按照1324的顺序执行会导致饥饿现象
pi(){
    flag[i]=true;       //1
    while(flag[j]);     //2
    printf("critical section");
    flag[i]=false;
    printf("remainder section");
}
pj(){
    flag[j]=true;       //3
    while(flag[i]);     //4
    printf("critical section");
    flag[j]=false;
    printf("remainder section");
}
//4)peterson's algorithm,可以实现互斥，但没有实现让权等待，即可能有进程忙等待
pi(){
    flag[i]=true;turn=j;
    while(flag[j]==true&&turn==j);
    printf("critical section");
    flag[i]=false;
    printf("remainder section");
}
pj(){
    flag[j]=true;turn=i;
    while(flag[i]==true&&turn==i);
    printf("critical section");
    flag[j]=false;
    printf("remainder section");
}
//2.硬件
//1)中断
//2)硬件指令
bool testandset(bool *lock){
    bool old;
    old=*lock;
    *lock=ture;
    return old;
}
bool lock;
p(){
    while(testandset(&lock));
    printf("critical section");
    lock=false;
    printf("remainder section");
}
swap(bool *a,bool *b){
    bool temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
bool key = true;
p(){
    while(key!=false)
        swap(&lock,&key);
    printf("critical section");
    lock=false;
    printf("remainder section");
}

//1.整型信号量
#define semaphore int
wait(int s){
    while(s<=0);
    s=s-1;
}
signal(int s){
    s=s+1;
}


//2.记录型信号量
typedef struct lnode{
    int data;
    struct lnode *next;
}lnode,process,*linklist;
typedef struct{
    int value;
    struct process *l;
}semaphore_record;

process pc;
void wait(semaphore_record s){
    s.value--;
    if(s.value<0){
        printf("add this process to s.l");
        push(s.l,pc);
        block(s.l);
    }
}
void signal(semaphore_record s){
    s.value++;
    if(s.value<=0){
        printf("remove a process from s.l");
        pop(s.l,pc);
        wakeup(pc);
    }
}

//经典同步问题
//1.生产者消费者问题
int n;
semaphore mutex=1;
semaphore empty=n;
semaphore full=0;
producer(){
    while(1){
        printf("produce an item in nextp");
        p(empty);
        p(mutex);
        printf("add nextp to buff");
        v(mutex);
        v(full);
    }
}
consumer(){
    while(1){
        p(full);
        p(mutex);
        printf("remove an item from buffer");
        v(mutex);
        v(empty);
        printf("consume the item");
    }
}

//2.爸妈放苹果橘子问题
semaphore plate=1,apple=0,orange=0;
dad(){
    while(1){
        printf("prepare an apple");
        p(plate);
        printf("put the apple on the plate");
        v(apple);
    }
}
mom(){
    while(1){
        printf("prepare an orange");
        p(plate);
        printf("put the orange on the plate");
        v(orange);
    }
}
son(){
    while(1){
        p(orange);
        printf("take an orange from the plate");
        v(plate);
        printf("eat the orange");
    }
}
daughter(){
    while(1){
        p(apple);
        printf("take an apple from the plate");
        v(plate);
        printf("eat the apple");
    }
}

//2.读者写者问题
int count =0;
semaphore rw=1;
writer(){
    while(1){
        p(rw);
        printf("writing");
        v(rw);
    }
}
reader(){
    while(1){
        p(mutex);
        if(count==0)
            p(rw);
        count++;
        v(mutex);
        printf("reading");
        p(mutex);
        count--;
        if(count==0);
            v(rw);
        v(mutex);
    }
}
//允许写进程优先的改进
semaphore w=1;

writer(){
    while(1){
        p(w);
        p(rw);
        printf("writing");
        v(rw);
        v(w);
    }
}
reader(){
    while(1){
        p(w);
        p(mutex);
        if(count==0)
            p(rw);
        count++;
        v(mutex);
        v(w);
        printf("reading");
        p(mutex);
        count--;
        if(count==0);
            v(rw);
        v(mutex);
    }
}


//3.哲学家进餐问题
semaphore chopstick[5]={1,1,1,1,1};
pi(){
    do{
        p(mutex);
        p(chopstick[i]);
        p(chopstick[(i+1)%5]);
        v(mutex);
        printf("eat");
        v(chopstick[i]);
        v(chopstick[(i+1)%5]);
        printf("thinking");
    }while(1);
}

//4.吸烟者问题
int num=0;
semaphore offer1=0;
semaphore offer2=0;
semaphore offer3=0;
semaphore finish=0;
p1(){
    while(1){
        num++;
        num=num%3;
        if(num==0)
            v(offer1);
        else if(num==1)
            v(offer2);
        else   
            v(offer3);
        printf("put material in table");
        p(finish);
    }
}

p2(){
    while(1){
        p(offer3);
        printf("use paper glue to ciger,smoke it");
        v(finish);
    }
}
p3(){
    while(1){
        p(offer2);
        printf("use cao glow to ciger,smoke it");
        v(finish);
    }
}
p2(){
    while(1){
        p(offer1);
        printf("use paper cao to ciger,smoke it");
        v(finish);
    }
}

//课后题
//3.生产奇数偶数问题。
semaphore odd=0,even=0;
semaphore empty=n;
p1(){
    while(1){
        int x=produce();
        p(empty);
        p(mutex);
        put();
        v(mutex);
        if(x%2==0)
            v(even);
        else
            v(odd);
    }
}