#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    long long data;
    long long weight;
    long long dist;
    struct Node * next;
    struct Node * parent;
}node;

long long find_min(node * queue[],long long a,long long b){
    if((queue[a])->weight<=queue[b]->weight){
        return a;
    }
    return b;
}
void heapify(node * queue[],long long * z){
    long long d=*z-1;
    while((d-1)/2>=0){
        if(d>0 && queue[d]->dist<queue[(d-1)/2]->dist){
        node * temp=queue[(d-1)/2];
        queue[(d-1)/2]=queue[d];
        queue[d]=temp;
        }
        d--;
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
    while(d>0 && queue[d]->weight<queue[(d-1)/2]->weight){
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
    for(long long i=0;i<n+1;i++){
        vis[i]=0;
    }
    for(long long i=1;i<n+1;i++){
        node * cur=pop(queue,z);
        vis[cur->data]=1;
        node *ptr=list[cur->data]->next;
        while(ptr!=NULL){
            if(vis[ptr->data]!=1){
                if(list[ptr->data]->dist>(list[cur->data]->dist+ptr->weight)){
                    list[ptr->data]->dist=list[cur->data]->dist+ptr->weight;
                    heapify(queue,z);
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
    node * queue[m];
    long long z=0;
    for(long long i=1;i<n+1;i++){
        list[i]=(node *)malloc(sizeof(node));
        list[i]->data=i;
        list[i]->weight=0;
        list[i]->dist=10e9;
        list[i]->next=NULL;
        list[i]->parent=NULL;
        list1[i]=list[i];
        push(queue,list[i],&z);
        
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
    heapify(queue,&z);
    dijkstra(list,n,x,queue,&z);
    printf("\n");
    }
}