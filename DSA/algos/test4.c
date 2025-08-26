#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
    int weight;
	struct Node * next;
}node;

int find_min(node * queue[],int a,int b){
    if((queue[a])->weight<=queue[b]->weight){
        return a;
    }
    return b;
}
void heapify(node * queue[],int * z){
    int d=0;
    while(d<(*z-1)/2){
        if(queue[d]->weight>queue[2*d+1]->weight || queue[d]->weight>queue[2*d+2]->weight){
        node * temp=queue[d];
        int m=find_min(queue,2*d+1,2*d+2);
        queue[d]=queue[m];
        queue[m]=temp;
        d=m;}
    }
    if(2*d+1<*z && (queue[d]->weight)>queue[2*d+1]->weight){
        node * temp=queue[d];
        int m=find_min(queue,2*d+1,2*d+2);
        queue[d]=queue[m];
        queue[m]=temp;
        d++;
    }
}
node * pop(node * queue[],int * z){
    node * temp=queue[0];
    if(*z==1){
        queue[0]=NULL;
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
void push(node * queue[],node * ptr,int * z){
    queue[*z]=ptr;
    int d=*z;
    while(d>0 && queue[d]->weight<queue[(d-1)/2]->weight){
        node * temp=queue[(d-1)/2];
        queue[(d-1)/2]=queue[d];
        queue[d]=temp;
        d=(d-1)/2;
    }
    *z=*z+1;
}

void dijkstra(node * list[],int n,int x){
    int vis[n+1];
    int dist[n+1];
    for(int i=0;i<n+1;i++){
        vis[i]=0;
        dist[i]=10e7;
    }
    node * queue[n+1];
    for(int i=0;i<n+1;i++){
        queue[i]=NULL;
    }
    int z=0;
    list[x]->weight=0;
    push(queue,list[x],&z);
    dist[list[x]->data]=list[x]->weight;
    while (queue[0]!=NULL){
        node *cur=pop(queue,&z);
        if(vis[cur->data]){
            continue;
        }
        vis[cur->data]=1;
        node *ptr=list[cur->data]->next;
        while(ptr!=NULL){
            if(dist[ptr->data]>dist[cur->data]+ptr->weight){
                dist[ptr->data]=dist[cur->data]+ptr->weight;
                push(queue,ptr,&z);
            }
            ptr=ptr->next;
        }
    }
    printf("%d",dist[n]);
}
int main(){
	int n,m,x,y,a,b,c;
	scanf("%d %d",&n,&m);
	node * list[n+1];
    node * list1[n+1];
	for(int i=0;i<n+1;i++){
		list[i]=(node *)malloc(sizeof(node));
		list[i]->data=i;
		list[i]->next=NULL;
        list1[i]=list[i];
	}
	for(int i=0;i<m;i++){
		scanf(" %d %d %d",&a,&b,&c);
		node* temp=(node *)malloc(sizeof(node));
		temp->data=b;
        temp->weight=c;
        temp->next=NULL;
        list1[a]->next=temp;
		list1[a]=temp;
        temp=(node *)malloc(sizeof(node));
		temp->data=a;
        temp->weight=c;
        temp->next=NULL;
        list1[b]->next=temp;
		list1[b]=temp;
	}
    dijkstra(list,n,1);
}