#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    long long data;
    long long weight;
    struct Node * next;
}node;
typedef struct Node2{
    long long data;
    long long weight;
    long long timeperiod;
    struct Node2 * next;
}node2;
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
void dijkstra(node2 * list[],node * queue[],long long n,long long x,long long y,long long d[]){
    for(long long i=0;i<n+1;i++){
        d[i]=10e6;
    }
    long long z=0;
    d[x]=0;
    list[x]->weight=0;
    node * temp=(node *)malloc(sizeof(node));
    temp->data=x;
    temp->weight=0;
    push(queue,temp,&z);
    while(z!=0){
        node * cur=pop(queue,&z);
        if (cur->weight!=d[cur->data]){
			continue;
        }
        node2 *ptr=list[cur->data]->next;
        long long timer;
        while(ptr!=NULL){
                if(ptr->timeperiod!=0 && (d[cur->data])%(ptr->timeperiod)!=0){
                    long long t=(((d[cur->data])/ptr->timeperiod)+1)*ptr->timeperiod;
                    timer=(t)-d[cur->data]+ptr->weight;
                }
                else{
                    timer=ptr->weight;
                }
                if(d[ptr->data]>d[cur->data]+timer){
                    d[ptr->data]=d[cur->data]+timer;
                    node * temp=(node *)malloc(sizeof(node));
                    temp->data=ptr->data;
                    temp->weight=d[ptr->data];
                    push(queue,temp,&z);
                }
            ptr=ptr->next;
        }
    }
    // for(int i=1;i<n+1;i++){
    //     if(i!=x){
    //     if(d[i]!=10e6){
    //         printf("%lld ",d[i]);
    //     }
    //     else{
    //         printf("-1 ");
    //     }
    //     }
    // }
    if(d[y]==10e6){
        printf("-1");
    }
    else{
    printf("%lld",d[y]);
    }

}
int main(){
    long long n,m,a,b,c,k,x,y,t;
    scanf("%lld %lld %lld %lld",&n,&m,&x,&y);
	node2 * list[n+1];
    node2 * list1[n+1];
    node * queue[m+1];
	for(long long i=0;i<n+1;i++){
		list[i]=(node2 *)malloc(sizeof(node2));
		list[i]->data=i;
        list[i]->weight=0;
        list[i]->timeperiod=0;
		list[i]->next=NULL;
        list1[i]=list[i];
	}
	for(long long i=0;i<m;i++){
		scanf(" %lld %lld %lld %lld",&a,&b,&c,&k);
		node2* temp=(node2 *)malloc(sizeof(node2));
		temp->data=b;
        temp->weight=c;
        temp->timeperiod=k;
        temp->next=NULL;
        list1[a]->next=temp;
		list1[a]=temp;
        node2 * temp2=(node2 *)malloc(sizeof(node2));
		temp2->data=a;
        temp2->weight=c;
        temp2->timeperiod=k;
        temp2->next=NULL;
        list1[b]->next=temp2;
		list1[b]=temp2;
	}
    long long d[n+1];
    dijkstra(list,queue,n,x,y,d);
    printf("\n");
}