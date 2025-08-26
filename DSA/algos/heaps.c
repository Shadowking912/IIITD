#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

long long find_min(long long queue[],long long a,long long b){
    if((queue[a])<=queue[b]){
        return a;
    }
    return b;
}
void heapify(long long queue[],long long * z,long long s){
        long long small=s;
        if(2*s+1<*z && queue[2*s+1]<queue[s]){
            small=2*s+1;
        }
        if(2*s+2<*z && queue[2*s+2]<queue[small]){
            small=2*s+2;
        }
        if(s!=small){
            long long temp4=queue[s];
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
    
long long pop(long long queue[],long long * z){
    long long temp=queue[0];
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
void push(long long queue[],long long ptr,long long * z){
    queue[*z]=ptr;
    long long d=*z;
    while(d!=0 && queue[d]<queue[(d-1)/2]){
        long long temp3=queue[(d-1)/2];
        queue[(d-1)/2]=queue[d];
        queue[d]=temp3;
        d=(d-1)/2;
    }
    *z=*z+1;
}
int main() {
    long long n,c;
    scanf("%lld ",&n);
    long long arr[n];
    long long z=0;
    for(long long i=0;i<n;i++){
        scanf("%lld",&c);
        push(arr,c,&z);
    }
    int f=0;
    for(long long i=0;i<=(50-1)/2;i++){
        if(arr[i]<arr[2*i+1] && arr[i]<arr[2*i+2]){
            f++;
        }
    }
    printf("[");
    for(long long i=0;i<n-1;i++){
        printf("%lld,",pop(arr,&z));
    }
    printf("%lld]",pop(arr,&z));
    return 0;
}