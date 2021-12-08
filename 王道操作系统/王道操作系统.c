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
p2(){
    while(1){
        p(odd);
        p(mutex);
        getodd();
        v(mutex);
        v(empty);
        countodd();
    }
}
p3(){
    while(1){
        p(even);
        p(mutex);
        geteven();
        v(mutex);
        v(empty);
        counteven();
    }
}

//6.仓库中可以放a，b两个商品，且m<b-a<n;
semaphore sa=m-1,sb=n-1;
semaphore mutex;
pa(){
    while(1){
        p(sa);
        p(mutex);
        Aintocage();
        v(mutex);
        v(sb);
    }
}
pb(){
    while(1){
        p(sb);
        p(mutex);
        Bintocage();
        v(mutex);
        v(sa);
    }
}

//7.顾客买面包，销售叫号
int i=0,j=0;
semaphore mutex_i=1,mutex_j=1;
bread_consumer(){
    intodoor();
    p(mutex_i);
    getnumber();
    i++;
    v(mutex_i);
    waitnumber();
}
seller(){
    while(1){
        p(mutex_j);
        if(j<i){
            wakeupnumber(j);
            j++;
            v(mutex_j);
            sellbread();
        }
        else{
            v(mutex_j);
            rest();
        }
    }
}

//8.500个人参观图书馆
semaphore empty = 500;
visiter(){
    p(empty);
    p(mutex);
    intodoor();
    v(mutex);
    visit();
    p(mutex);
    outodoor();
    v(mutex);
    v(empty);
}

//9.两个车间生产，一个车间组装
semaphore empty1=10,empty2=10,full1=0,full2=0,mutex1=1,mutex2=1;
pa(){
    while(1){
        produceA();
        p(empty1);
        p(mutex1);
        putA();
        v(mutex1);
        v(full1);
    }
}
pb(){
    while(1){
        produceB();
        p(empty2);
        p(mutex2);
        putB();
        v(mutex2);
        v(full2);
    }
}
pd(){
    while(1){
        p(full1);
        p(mutex1);
        getA();
        v(mutex1);
        v(empty1);
        p(full2);
        p(mutex2);
        getB();
        v(mutex2);
        v(empty2);
        combineAB();
    }
}

//10.老和尚和小和尚打水
semaphore well=1,mutex=1,empty=10,full=0,pail=3;
oldmonk(){
    while(1){
        p(full);
        p(pail);
        p(mutex);
        getwater();
        v(mutex);
        v(empty);
        drinkwater();
        v(pail);
    }
}
littlemonk(){
    while(1){
        p(empty);
        p(pail);
        p(well);
        gotwaterfromwell();
        v(well);
        p(mutex);
        pourwater();
        v(mutex);
        v(pail);
        v(full);
    }
}

//12.10个座位顾客，营销员
semaphore service=0;
consumer_people(){
    while(1){
        p(empty);
        p(mutex);
        getnumber();
        v(mutex);
        v(full);
        p(service);
        waitserve();
    }
}
seller_people(){
    while(1){
        p(full);
        v(empty);
        v(service);
        giveserve();
    }
}

//13.过桥
semaphore bridge=1;
ntos(){
    p(bridge);
    throughbridge();
    v(bridge);
}
ston(){
    p(bridge);
    throughbridge();
    v(bridge);
}

//14.可以多车行驶的桥
int countsn=0;
int countns=0;
ston1(){
    p(mutex1);
    if(countsn==0)
        p(mutex);
    countsn++;
    v(mutex1);
    throughbridge();
    p(mutex1);
    countsn--;
    if(countsn==0)
        v(mutex);
    v(mutex1);
}
ntos1(){
    p(mutex2);
    if(countns==0)
        p(mutex);
    countns++;
    v(mutex2);
    throughbridge();
    p(mutex2);
    countns--;
    if(countns==0)
        v(mutex);
    v(mutex2);
}

//15.车架车轮组装车三个工人
semaphore empty=n,wheel=0,frame=0,s1=n-2,s2=n-1;
worker1(){
    while(1){
        produceframe();
        p(s1);
        p(empty);
        put();
        v(frame);
    }
}
worker2(){
    while(1){
        producewheel();
        p(s2);
        p(empty);
        put();
        v(wheel);
    }
}
worker3(){
    p(frame);
    gotframe();
    v(empty);
    v(s1);
    p(wheel);
    p(wheel);
    gettwowheel();
    v(empty);
    v(empty);
    v(s2);
    v(s2);
    combinetoacar();
}

//16.一个生产者，一个消费者，一个既可以生产又可以消费，
pp(){
    while(1){
        p(empty);
        p(mutex);
        product();
        v(mutex);
        v(full);
    }
}
pq(){
    while(1){
        p(full);
        p(mutex);
        consume();
        v(mutex);
        v(empty);
    }
}
pr(){
    while(1){
        if(empty==1){
            p(empty);
            p(mutex);
            product();
            v(mutex);
            v(full);
        }
        if(full==1){
            p(full);
            p(mutex);
            consume();
            v(mutex);
            v(empty);
        }
    }
}

//17.顾客和理发师
int waiting=0;
int chairs=n;
semaphore custumers=0,barbers=0,mutex=1;
barber(){
    while(1){
        p(custumers);
        p(mutex);
        waiting--;
        v(barbers);
        v(mutex);
        cuthair();
    }
}
customer(){
    p(mutex);
    if(waiting<chairs){
        waiting=waiting+1;
        v(custumers);
        v(mutex);
        p(barbers);
        gethaircut();
    }
    else
        v(mutex);
}

//18.影院放三个电影
semaphore s=1,s0=1,s1=1,s2=1;
int count0=0,count1=0,count2=0;
video1(){
    p(s0);
    if(count0==0)
        p(s);
    count0++;
    v(s0);
    watchvideo();
    p(s0);
    count0--;
    if(count0==0)
        v(s);
    v(s0);
}
video2(){
    p(s1);
    if(count1==0)
        p(s);
    count1++;
    v(s1);
    watchvideo();
    p(s1);
    count1--;
    if(count1==0)
        v(s);
    v(s1);
}
video3(){
    p(s2);
    if(count2==0)
        p(s);
    count2++;
    v(s2);
    watchvideo();
    p(s2);
    count2--;
    if(count2==0)
        v(s);
    v(s2);
}


//19.南开天大过桥有中心岛
semaphore t2n=1,n2t=1,l=1,k=1;
tgoton(){
    p(t2n);
    p(l);
    goTtoL();
    gointoM();
    v(l);
    p(k);
    goKtoN();
    v(k);
    v(t2n);
}
ngotot(){
    p(n2t);
    p(k);
    goNtok();
    gointoM();
    v(k);
    p(l);
    goLtoT();
    v(l);
    v(n2t);
}

//20.消费者连续取十件的生产者消费者问题
produceA(); //略
consumer10(){
    p(mutex1);
    for(int i=0;i<10;i++){
        p(full);
        p(mutex2);
        got();
        v(mutex2);
        v(empty);
    }
    v(mutex1);
}

//21.售票员和司机
semaphore s1=0,s2=0;
driver(){
    while(1){
        p(s1);
        start();
        driving();
        stop();
        v(s2);
    }
}
conductor(){
    while(1){
        closedoor();
        v(s1);
        sellticket();
        p(s2);
        opendoor();
    }
}

//22.信箱通信
semaphore full_a=x,empty_a=m-x;
semaphore full_b=y,empty_b=n-y;
semaphore mutex_a=1,mutex_b=1;
maila(){
    while(1){
        p(full_a);
        p(mutex_a);
        gotMail();
        v(mutex_a);
        v(empty_a);
        answerandputquestion();
        p(empty_b);
        p(mutex_b);
        putmailB();
        v(mutex_b);
        v(full_b);
    }
}
mailb(){
    while(1){
        p(full_b);
        p(mutex_b);
        gotMail();
        v(mutex_b);
        v(empty_b);
        answerandputquestion();
        p(empty_a);
        p(mutex_a);
        putmailB();
        v(mutex_a);
        v(full_a);
    }
}

//24.加了碗的哲学家进餐问题。
semaphore bowl;
semaphore chopsticks[n];
for(int i=0;i<n;i++)
    chopsticks[i]=1;
bowl=min(n-1,m);

philospher_i(){
    while(1){
        thinking();
        p(bowl);
        p(chopsticks[i]);
        p(chopsticks[(i+1)%n]);
        eating();
        v(chopsticks[i]);
        v(chopsticks[(i+1)%n]);
        v(bowl);
    }
}
