#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node * left;
    struct Node * right;
}node;

void compress(char *iname){
    int freq[127];
    char x[10];
    const char * name=iname;
    FILE *ptr=fopen(name,"r");
    fscanf(ptr,"%s",x);
    printf("%s %s",x,iname);
    exit(0);
    while(fscanf(ptr,"%s",&x)!=0){
        printf("%s",x);
    }
    
}
int main(){
    printf("Enter file name: ");
    char s[100];
    char i=-1;
    int z=0;
    while(i!='\n'){
    scanf("%c",&s[z]);
    i=s[z];
    z++;
    }
    char s2[z];
    for(int i=0;i<z;i++){
        s2[i]=s[i];
    }
    printf("%s\n",s2);
    compress(s2);
    printf("Enter output file name: ");

}