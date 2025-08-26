#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node * next;
    struct Node* prev;
}node;
node * temp;

// void merge(node ** head,node ** headr){
//     node * i=*head;
//     node * j=*headr;
//     node * ptr=headfinal;
//     while(i!=NULL && j!=NULL){
//         if(i->data%2<j->data%2){
//             ptr->next=j;
//             j->prev=ptr;
//             ptr=j;
//             j=j->next;
//         }
//         else if(i->data%2=j->data%2){
//             if(i->data>j->data){
//                 ptr->next=j;
//                 j->prev=ptr;
//                 ptr=j;
//                 j=j->next;
//             }
//             else{
//                 ptr->next=i;
//                 i->prev=ptr;
//                 ptr=i;
//                 i=i->next;

//             }
//         }
//         else{
//             ptr->next=i;
//             i->prev=ptr;
//             ptr=i;
//             i=i->next;
//         }
//     }
//     while(i!=NULL){
//         ptr->next=i;
//         i->prev=ptr;
//         ptr=i;
//         i=i->next;
//     }
//     while(j!=NULL){
//         ptr->next=j;
//         j->prev=ptr;
//         ptr=j;
//         j=j->next;
//     }
//     *head=headfinal;
// }
node * mergesort(node **head){
    if((*head)->next==NULL){
        printf("%d",(*head)->data);
        return *head;
    }
    node * mid=(*head);
    node * tail=(*head)->next;
    while(1){
        if(tail->next==NULL){
            break;
        }
        else if(tail->next->next==NULL){
            tail=tail->next;
            mid=mid->next;
            break;
        }
        
        else{
            tail=tail->next->next;
            mid=mid->next;
        }
        printf("%d %d",mid->data,tail->data);
    }
    exit(0);
    node * headr=mid->next;
    mid->next=NULL;
    tail->next=NULL;
    head=mergesort(head);
    headr=mergesort(headr);
    //head=merge(*head,&headr);
}
int main(){
    int n,a;
    node * headfinal=(node *)malloc(sizeof(node));
    scanf("%d",&n);
    printf("%d\n",n);
    scanf(" %d",&a);
    node * head=(node *)malloc(sizeof(node));
    head->data=a;
    head->prev=NULL;
    head->next=NULL;
    node * ptr=head;
    for(int i=0;i<n-1;i++){
        scanf("%d",&a);
        temp=(node *)malloc(sizeof(node));
        temp->data=a;
        temp->prev=ptr;
        temp->next=NULL;
        ptr->next=temp;
        ptr=temp;
    }
    ptr=head;
    while(ptr!=NULL){
        printf("%d ",ptr->data);
        ptr=ptr->next;
    }
    mergesort(&head);
    
}