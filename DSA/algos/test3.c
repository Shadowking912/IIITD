#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	long long data;
    long long weight;
    long long timeperiod;
	struct Node * next;
}node;

long long find_min(node * queue[],long long a,long long b){
    if((queue[a])->weight<=queue[b]->weight){
        return a;
    }
    return b;
}
void heapify(node * queue[],long long * z){
    long long d=0;
    if(*z==2 && queue[0]>queue[1]){
        node * temp=queue[0];
        queue[0]=queue[1];
        queue[1]=temp;
    }
    if(*z==1){
        return;
    }
    while(d<(*z-1)/2){
        if(queue[d]->weight>queue[2*d+1]->weight || queue[d]->weight>queue[2*d+2]->weight){
        node * temp=queue[d];
        long long m=find_min(queue,2*d+1,2*d+2);
        queue[d]=queue[m];
        queue[m]=temp;
        d=m;}
        else{
            break;
        }
    }
    if(2*d+1<*z && (queue[d]->weight)>queue[2*d+1]->weight){
        node * temp=queue[d];
        long long m=find_min(queue,2*d+1,2*d+2);
        queue[d]=queue[m];
        queue[m]=temp;
        d++;
    }
}
node * pop(node * queue[],long long * z){
    node * temp=queue[0];
    if(*z==1){
        //queue[0]=NULL;
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
void dijkstra(node * list[],long long n,long long x,long long y){
    long long vis[n+1];
    long long dist[n+1];
    for(long long i=0;i<n+1;i++){
        vis[i]=0;
        dist[i]=10e6;
    }
    node * queue[n*n];
    for(long long i=0;i<n*n;i++){
        queue[i]=NULL;
    }
    long long z=0;
    list[x]->weight=0;
    push(queue,list[x],&z);
    dist[list[x]->data]=0;
    while (z!=0){
        node *cur=pop(queue,&z);
        if(vis[cur->data]){
            continue;
        }
        vis[cur->data]=1;
        node *ptr=list[cur->data]->next;
        long long timer;
        while(ptr!=NULL){
            // if(ptr->timeperiod!=0 && (dist[cur->data])%(ptr->timeperiod)!=0){
            //     long long t=(((dist[cur->data])/ptr->timeperiod)+1)*ptr->timeperiod;
            //     timer=(t)-dist[cur->data]+ptr->weight;
            // }
            // else{
            //     timer=ptr->weight;
            // }
            timer=ptr->weight;
            if(dist[ptr->data]>dist[cur->data]+timer){
                dist[ptr->data]=dist[cur->data]+timer;
                push(queue,ptr,&z);
            }
            ptr=ptr->next;
        }
    }
    for(int i=1;i<n+1;i++){
        if(i!=x){
            if(dist[i]==10e6){
                printf("-1 ");
            }
            else{
                printf("%lld ",dist[i]);
            }

        }
    }
    // if(vis[y]==0){
    //     printf("-1");
    // }
    // else{
    //     printf("%lld",dist[y]);
    // }
}
int main(){
	long long n,m,a,b,c,t;
    scanf("%lld ",&t);
    for(int j=0;j<t;j++){
	// scanf("%lld %lld %lld %lld",&n,&m,&x,&y);
	// node * list[n+1];
    // node * list1[n+1];
	// for(long long i=0;i<n+1;i++){
	// 	list[i]=(node *)malloc(sizeof(node));
	// 	list[i]->data=i;
    //     list[i]->weight=0;
    //     list[i]->timeperiod=0;
	// 	list[i]->next=NULL;
    //     list1[i]=list[i];
	// }
	// for(long long i=0;i<m;i++){
	// 	scanf(" %lld %lld %lld %lld",&a,&b,&c,&k);
	// 	node* temp=(node *)malloc(sizeof(node));
	// 	temp->data=b;
    //     temp->weight=c;
    //     temp->timeperiod=k;
    //     temp->next=NULL;
    //     list1[a]->next=temp;
	// 	list1[a]=temp;
    //     node * temp2=(node *)malloc(sizeof(node));
	// 	temp2->data=a;
    //     temp2->weight=c;
    //     temp2->timeperiod=k;
    //     temp2->next=NULL;
    //     list1[b]->next=temp2;
	// 	list1[b]=temp2;
	// }
    scanf("%lld %lld",&n,&m);
	node * list[n+1];
    node * list1[n+1];
	for(long long i=0;i<n+1;i++){
		list[i]=(node *)malloc(sizeof(node));
		list[i]->data=i;
        list[i]->weight=0;
        list[i]->timeperiod=0;
		list[i]->next=NULL;
        list1[i]=list[i];
	}
	for(long long i=0;i<m;i++){
		scanf(" %lld %lld %lld",&a,&b,&c);
		node* temp=(node *)malloc(sizeof(node));
		temp->data=b;
        temp->weight=c;
        temp->timeperiod=0;
        temp->next=NULL;
        list1[a]->next=temp;
		list1[a]=temp;
        node * temp2=(node *)malloc(sizeof(node));
		temp2->data=a;
        temp2->weight=c;
        temp2->timeperiod=0;
        temp2->next=NULL;
        list1[b]->next=temp2;
		list1[b]=temp2;
	}
    long long x;
    scanf(" %lld",&x);
    long long y=1;
    dijkstra(list,n,x,y);
    printf("\n");
    }
}