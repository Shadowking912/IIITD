#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    long long data;
    long long count;
    struct Node * parent;
}node;

typedef struct Node2{
    node * u;
    node *v;
    long long weight;
}edge;

void set_union(node * u,node *v){
    if(u->count<v->count)
    {
        u->parent=v;
        v->count=v->count+u->count;
    }
    else{
        v->parent=u;
        u->count=v->count+u->count;
    }
    
}
node * set_find(node * u){
    node * temp=u;
    while(temp->parent!=NULL){
        temp=temp->parent;
    }
    return temp;
}
long long find_min(edge * heap[],long long a,long long b){
    if((heap[a])->weight<=heap[b]->weight){
        return a;
    }
    return b;
}
edge * extract_min(edge * heap[],long long z){
    edge *temp1=heap[0];
    heap[0]=heap[z-1];
    heap[z-1]=temp1;
    z--;
    long long d=0;
    while(d<(z-1)/2 && (heap[d]->weight>heap[2*d+1]->weight || heap[d]->weight>heap[2*d+2]->weight) ){
        edge* temp=heap[d];
        long long m=find_min(heap,2*d+1,2*d+2);
        heap[d]=heap[m];
        heap[m]=temp;
        d++;
    }
    if(2*d+1<z && (heap[d]->weight)>heap[2*d+1]->weight){
        edge * temp=heap[d];
        long long m=find_min(heap,2*d+1,2*d+2);
        heap[d]=heap[m];
        heap[m]=temp;
        d++;
    }
    return temp1;
}

int main(){
    long long a,b,n=0,m=0;
    long long c;
    scanf("%lld %lld",&n,&m);
    edge * heap[m];
    long long t=0;
    edge * list[m];
    node * vert[n+1];
    for(long long i=0;i<n+1;i++){
        node * temp=(node *)malloc(sizeof(node));
        temp->count=1;
        temp->data=i;
        vert[i]=temp;
        temp->parent=NULL;
    }
    for(long long i=0;i<m;i++){
        scanf(" %lld %lld %lld",&a,&b,&c);
        edge * temp=(edge *)malloc(sizeof(edge));
        temp->u=vert[a];
        temp->v=vert[b];
        temp->weight=c;
        heap[t]=temp;
        long long d=t;
        while(d>0 && heap[d]->weight<heap[(d-1)/2]->weight){
            edge * temp=heap[(d-1)/2];
            heap[(d-1)/2]=heap[d];
            heap[d]=temp;
            d=(d-1)/2;
        }
        t++;
    }
    long long z=0;
    while(z<n){
        edge * temp2=extract_min(heap,t);
        t--;
        node * t1=set_find(temp2->u);
        node * t2=set_find(temp2->v);
        if(t1!=t2){
            list[z]=temp2;
            set_union(t1,t2);
            z++;
        }
    }
    long long sum=0;
    for(long long i=0;i<z;i++){
        printf("%lld %lld %lld\n",list[i]->u->data,list[i]->v->data,list[i]->weight);
        sum=sum+list[i]->weight;
    }
    printf("sum %lld",sum);
}