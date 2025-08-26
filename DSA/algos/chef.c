#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    long long data;
    long long weight;
    long long dist;
    struct Node * next;
    struct Node * parent;
    long long time;
}node;

long long find_min(node * queue[],long long a,long long b){
    if((queue[a])->weight<=queue[b]->weight){
        return a;
    }
    return b;
}
void heapify(node * queue[],long long * z){
    long long d=0;
    while(2*d+1<*z){
        node * smaller=queue[d];
        long long small=0;
        if(queue[d]->dist>queue[2*d+1]->dist){
            smaller=queue[2*d+1];
            small=2*d+1;
        }
        if(2*d+2<*z && queue[2*d+2]->dist<smaller->dist){
            smaller=queue[2*d+1];
            small=2*d+2;
        }
        
        if(smaller->dist==queue[d]->dist){
            break;
        }
        else{
            node * temp=queue[d];
            queue[d]=smaller;
            smaller=temp;
            d=small;
        }
    }
}
node * pop(node * queue[],long long * z){
    node * temp=queue[0];
    if(*z==1){
        *z=*z-1;
    }
    else{
        node * temp=queue[0];
        queue[0]=queue[*z-1];
        queue[*z-1]=temp;
        *z=*z-1;
        heapify(queue,z);
    }
    return temp;
}
void push(node * queue[],node * ptr,long long * z){
    queue[*z]=ptr;
    long long d=*z;
    while(d>0 && queue[d]->dist<queue[(d-1)/2]->dist){
        node * temp=queue[(d-1)/2];
        queue[(d-1)/2]=queue[d];
        queue[d]=temp;
        d=(d-1)/2;
    }
    *z=*z+1;
}
long long min1(long long a,long long b){
    if(a<b){
        return a;
    }
    return b;
}
void dijkstra(node * list[],long long n,long long x,node * queue[],long long *z){
    long long vis[n+1];
    long long timeperiod;
    for(long long i=0;i<n+1;i++){
        vis[i]=0;
    }
    push(queue,list[x],z);
    while(*z>0){
        node * cur=pop(queue,z);
        if(vis[cur->data]){
            continue;
        }
        vis[cur->data]=1;
        node *ptr=list[cur->data]->next;
        while(ptr!=NULL){
                timeperiod=ptr->weight;
                // if((list[cur->data]->dist)%ptr->time==0){
                //     timeperiod=ptr->weight;
                // }
                // else{
                //     timeperiod=((((list[cur->data]->dist)/ptr->time)+1)*ptr->time)-list[cur->data]->dist+ptr->weight;
                // }
                if(list[ptr->data]->dist>(list[cur->data]->dist+timeperiod)){
                    list[ptr->data]->dist=list[cur->data]->dist+timeperiod;
                    push(queue,list[ptr->data],z);
                }
                ptr=ptr->next;
            }
            
    }
    for(long long i=1;i<n+1;i++){
        if(list[i]->dist==10e9){
            printf("-1 ");
        }
        else if(i!=x){
            printf("%lld ",list[i]->dist);
        }
    }
    // if(list[y]->dist==10e9){
    //     printf("-1");
    // }
    // else{
    //     printf("%lld",list[y]->dist);
    // }
}
int main(){
    long long n,m,x,a,b,c,t;
    scanf("%lld",&t);
    for(int j=0;j<t;j++){
    scanf(" %lld %lld",&n,&m);
    node * list[n+1];
    node * list1[n+1];
    node * queue[m+n];
    long long z=0;
    for(long long i=1;i<n+1;i++){
        list[i]=(node *)malloc(sizeof(node));
        list[i]->data=i;
        list[i]->weight=0;
        list[i]->dist=10e9;
        list[i]->next=NULL;
        list[i]->parent=NULL;
        list1[i]=list[i];
        // push(queue,list[i],&z);
    }
    if(m==0){
        printf("-1");
        exit(0);
    }
    for(long long i=0;i<m;i++){
        scanf(" %lld %lld %lld",&a,&b,&c);
        node* temp=(node *)malloc(sizeof(node));
        temp->data=b;
        temp->weight=c;
        temp->dist=10e9;
        temp->next=NULL;
        list1[a]->next=temp;
        list1[a]=temp;
        node * temp2=(node *)malloc(sizeof(node));
        temp2->data=a;
        temp2->weight=c;
        temp2->dist=10e9;
        temp2->next=NULL;
        list1[b]->next=temp2;
        list1[b]=temp2;
    }
    scanf(" %lld",&x);
    list[x]->dist=0;
    // heapify(queue,&z);
    dijkstra(list,n,x,queue,&z);
    printf("\n");
    }
}