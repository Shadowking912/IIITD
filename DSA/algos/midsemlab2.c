#include<stdio.h>
int search(long long k){
    long long x=1;
    for(int i=1;i<30;i++){
        x=x*2;
        if(k<=x){
            x=x/2;
            return x;
        }
    }
}
int finder(long long x){
    if(x==1){
        return 0;
    }
    int i=search(x);
    long long y=x-i;
    int t=!(finder(y));
    return t;
}
int main(){
    long long x;
    int n;
    scanf("%d %lld",&n,&x);
    printf("%d",finder(x));   
}