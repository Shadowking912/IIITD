#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    long long data;
    long long weight;
    long long dist;
    struct Node * next;
    struct Node * parent;
}node;
typedef struct Node2{
    long long data;
    long long dis1;
}node2;

long long find_min(node * queue[],long long a,long long b){
    if((queue[a])->weight<=queue[b]->weight){
        return a;
    }
    return b;
}
void heapify(node2 * queue[],long long * z,long long s){
        long long small=s;
        if(2*s+1<*z && queue[2*s+1]->dis1<queue[s]->dis1){
            small=2*s+1;
        }
        if(2*s+2<*z && queue[2*s+2]->dis1<queue[small]->dis1){
            small=2*s+2;
        }
        if(s!=small){
            node2* temp4=queue[s];
            queue[s]=queue[small];
            queue[small]=temp4;
            heapify(queue,z,small);
        }
    //     long long d=*z-1;
    // while((d-1)/2>=0){
    //     if(d>0 && queue[d]->dist<queue[(d-1)/2]->dist){
    //     long long * temp=queue[(d-1)/2];
    //     queue[(d-1)/2]=queue[d];
    //     queue[d]=temp;
    //     }
    //     d--;
    // }
    
}
    
node2 * pop(node2 * queue[],long long * z){
    node2 * temp=queue[0];
    if(*z==1){
        *z=*z-1;
    }
    else{
        //long long * temp=queue[0];
        queue[0]=queue[*z-1];
        *z=*z-1;
        heapify(queue,z,0);
    }
    return temp;
}
void push(node2 * queue[],node2 * ptr,long long * z){
    queue[*z]=ptr;
    long long d=*z;
    while(d!=0 && queue[d]->dis1<queue[(d-1)/2]->dis1){
        node2 * temp3=queue[(d-1)/2];
        queue[(d-1)/2]=queue[d];
        queue[d]=temp3;
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
void dijkstra(node * list[],long long n,long long x,node2 * queue[],long long *z){
    long long vis[n+1];
    long long dis[n+1];
    for(long long i=0;i<n+1;i++){
        vis[i]=0;
        dis[i]=10e9;
        
    }
    dis[x]=0;
    node2 * temp=(node2 *)malloc(sizeof(node2));
    temp->data=x;
    temp->dis1=dis[x]; 
    push(queue,temp,z);
    while(*z>0){
        node2* cur=pop(queue,z);
        if(vis[cur->data]){
            continue;
        }
        vis[cur->data]=1;
        node *ptr=list[cur->data]->next;
        while(ptr!=NULL){
            if(vis[ptr->data]!=1){
                if(dis[ptr->data]>(dis[ptr->data]+ptr->weight)){
                   dis[ptr->data]=dis[cur->data]+ptr->weight;
                   node2 * temp=(node2 *)malloc(sizeof(node2));
                   temp->data=ptr->data;
                   temp->dis1=dis[ptr->data]; 
                   push(queue,temp,z);
                }
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
}
int main(){
    long long n,m,a,b,c,t;
    scanf("%lld",&t);
    for(long long j=0;j<t;j++){
    scanf(" %lld %lld",&n,&m);
    node * list[n+1];
    node * list1[n+1];
    node2 * queue[m+n];
    long long z=0;
    for(long long i=1;i<n+1;i++){
        list[i]=(node *)malloc(sizeof(node));
        list[i]->data=i;
        list[i]->weight=0;
        list[i]->dist=10e9;
        list[i]->next=NULL;
        list[i]->parent=NULL;
        list1[i]=list[i];
        //push(queue,list[i],&z);
        
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
        temp->dist=10e9;
        temp2->next=NULL;
        list1[b]->next=temp2;
        list1[b]=temp2;
    }
    long long x;
    scanf(" %lld",&x);
    list[x]->dist=0;
    //heapify(queue,&z);
    dijkstra(list,n,x,queue,&z);
    printf("\n");
    }
}