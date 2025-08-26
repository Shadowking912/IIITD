#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int x;
    scanf("%d",&x);
    int start=0,end=n-1;
    int mid;
    while(start<end){
        mid=end+start/2;
        if(x>arr[mid]){
            start=mid+1;
        }
        else if(x<arr[mid]){
            end=mid-1;
        }
        else{
            printf("%d",mid);
            break;
        }
    }
}