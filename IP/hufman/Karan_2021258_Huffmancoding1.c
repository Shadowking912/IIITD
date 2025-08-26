#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node{
    int data;
    struct Node * left;
    struct Node * right;
}node;
int n=0;
int total=0;
typedef struct Node2{
    int freq;
    char data;
    struct Node2 *left;
    struct Node2 *right;
}node2;
int find_min(node2 * heap[],int a,int b){
    if((heap[a])->freq<=heap[b]->freq){
        return a;
    }
    return b;
}

node2 * extract_min(node2 *heap[],int * z){
    node2 * temp2=heap[0];
    heap[0]=heap[*z-1];
    *z=*z-1;
    int d=0;
    while(d<(*z-1)/2 && (heap[d]->freq>heap[2*d+1]->freq || heap[d]->freq>heap[2*d+2]->freq) ){
        node2 * temp=heap[d];
        int m=find_min(heap,2*d+1,2*d+2);
        heap[d]=heap[m];
        heap[m]=temp;
        d++;
    }
    if(2*d+1<*z && (heap[d]->freq)>heap[2*d+1]->freq){
        node2 * temp=heap[d];
        int m=find_min(heap,2*d+1,2*d+2);
        heap[d]=heap[m];
        heap[m]=temp;
        d++;
    }
    return temp2;
}

node2 * tree(node2 * heap[],int *z){
    while(*z!=1){
    node2 * temp1=extract_min(heap,z);
    node2 * temp2=extract_min(heap,z);
    node2 * temp3=(node2 *)malloc(sizeof(node2));
    temp3->freq=temp1->freq+temp2->freq;
    temp3->data=(char)35;
    temp3->left=temp1;
    temp3->right=temp2;
    heap[*z]=temp3;
    *z=*z+1;
    }
    return heap[0];

}

node2* compress(char iname[]){
    int freq[128]={0};
    char x;
    FILE *ptr=fopen(iname,"r");
    while(fscanf(ptr,"%c",&x)!=EOF){
        freq[(int)x]++;
        ptr+sizeof(char);
    }
    int t=1;

    for(int i=0;i<128;i++){
        if(freq[i]!=0){
        t++;
        total=total+freq[i];
        }
    }
    node2 *heap[t-1];
    int z=0;
    for(int i=0;i<128;i++){
        if(freq[i]!=0){
            heap[z]=(node2 *)malloc(sizeof(node2));
            heap[z]->data=(char)i;
            heap[z]->freq=freq[i];
            heap[z]->left=NULL;
            heap[z]->right=NULL;
            int d=z;
            while(d>0 && heap[d]->freq<heap[(d-1)/2]->freq){
                node2 * temp=heap[(d-1)/2];
                heap[(d-1)/2]=heap[d];
                heap[d]=temp;
                d=(d-1)/2;
            }
            z++;
        }
    }
    // for(int i=0;i<t-1;i++){
    //     printf("%c %d\n",heap[i]->data,heap[i]->freq);
    // }
    node2* root=tree(heap,&z);
    fclose(ptr);
    return root;
}
int get_char(int buf[]){
    int h=0;
    int j=0;
    while(buf[j]!=-1 && j<7){
        h++;
        j++;
    }
    h--;
    int t=0;
    int z=1;
    j=0;
    while(h-j>-1){
        t=t+buf[h-j]*(z);
        z=z*2;
        j++;
    }
    return t;
}

node2* create_tree(FILE * ptr3){
    char x;
    node2* stack[10000];
    int top=0;
    int flag=0;
    int f=0;
    while(1){
        fscanf(ptr3,"%c",&x);
        ptr3+sizeof(char);
    if(x=='1'){
        flag=1;
    }
    else if(x=='0'){
        if(top>1){
            node2* temp1=stack[top-1];
            top--;
            node2* temp2=stack[top-1];
            top--;
            node2* temp3=(node2*)malloc(sizeof(node2));
            temp3->right=temp1;
            temp3->left=temp2;
            stack[top]=temp3;
            top++;
        }
        else if(top==1){
            return stack[top-1];
        }
        flag=0;
    }
    else if(flag==1){
        node2 * temp=(node2*)malloc(sizeof(node2));
        temp->data=x;
        temp->right=NULL;
        temp->left=NULL;
        stack[top]=temp;
        top++;
    }
    }
}
void getbyte(int data1[],int * v,unsigned char h){
    unsigned char x=h;
    int z=x;
    int t=0;
    while(z!=0){
        z=z/2;
        t++;
    }
    z=x;
    for(int l=0;l<7-t;l++){
        data1[*v+l]=0;
    }
    *v=*v+7-t;
    int l=t;
    while(z!=0){
        data1[*v+t-1]=z%2;
        z=z/2;
        t--;
    }
    *v=*v+l;
}
void decoder(int data1[],int * v,FILE * ptr,node2* root,FILE * ptr3,int total){
    unsigned char x;
    while(fscanf(ptr,"%c",&x)!=EOF){
        getbyte(data1,v,x);
        ptr+sizeof(char);
    }
    *v=0;
    int g=0;
    node2* ptr2=root;
    while(g<total){
        if(data1[*v]==1){
            ptr2=ptr2->right;
        }
        else if(data1[*v]==0){
            ptr2=ptr2->left;
        }
        if(ptr2->right==NULL && ptr2->left==NULL){
            //printf("%c",ptr2->data);
            fprintf(ptr3,"%c",ptr2->data);
            ptr2=root;
            g++;
        }
        *v=*v+1;
    }
}
void postorder(node2* ptr,FILE * ptr2){
    if(ptr->right==NULL && ptr->left==NULL){
        fprintf(ptr2,"1%c",ptr->data);
        return;
    }
    postorder(ptr->left,ptr2);
    postorder(ptr->right,ptr2);
    fprintf(ptr2,"0");
}
void printcode(node2 * root,int code[],int t){
    if(root->right==NULL && root->left==NULL){
        int j=0;
        printf("%c->",root->data);
        while(code[j]!=-1){
            printf("%d",code[j]);
            j++;
        }
        printf("\n");
        return;
    }
    if(root->left){
        code[t]=0;
        printcode(root->left,code,t+1);
        code[t]=-1;
    }
    if(root->right){
        code[t]=1;
        printcode(root->right,code,t+1);
        code[t]=-1;
    }
}  
void encode1(node2 * root,int buf[],char x,int code[],int t,FILE *ptr2){
    if(root->data==x){
        int j=0;
        while(code[j]!=-1){
            if(n==7){
                unsigned char result=get_char(buf);
                fprintf(ptr2,"%c",result);
                memset(buf, -1, 7*sizeof(int));
                n=0;
            }
            buf[n]=code[j];
            n=n+1;
            j++;
        }
        return;
    }
    if(root->left){
        code[t]=0;
        encode1(root->left,buf,x,code,t+1,ptr2);
        code[t]=-1;
    }
    if(root->right){
        code[t]=1;
        encode1(root->right,buf,x,code,t+1,ptr2);
        code[t]=-1;
    }
}   
int main(){
    printf("Enter file name: ");
    int data1[100000];
    memset(data1,-1,100000*sizeof(int));
    char s[100];
    char i=-1;
    int z=0;
    while(i!='\n'){
        scanf("%c",&s[z]);
        i=s[z];
        z++;
    }
    char s2[z];
    for(int i=0;i<z-1;i++){
        s2[i]=s[i];
    }
    s2[z-1]='\0';
    printf("Enter output file name: ");
    i=-1;
    z=0;
    while(i!='\n'){
        scanf("%c",&s[z]);
        i=s[z];
        z++;
    }
    char s3[z];
    for(int i=0;i<z-1;i++){
        s3[i]=s[i];
    }
    s3[z-1]='\0';
    int mode;
    FILE *ptr=fopen(s2,"r");
    if(ptr==NULL){
        printf("No such input file exists");
        exit(0);
    }
    FILE *ptr2=fopen(s3,"w+");
    printf("Enter mode(0 for compression, 1 for decompression): ");
    scanf("%d",&mode);
    if(mode==0){
        char x;
        node2* root=compress(s2);
        postorder(root,ptr2);
        fprintf(ptr2,"0");
        fprintf(ptr2,"%d",total);
        fprintf(ptr2,"%c",'@');
        int buf[7];
        memset(buf, -1, 7*sizeof(int));
        int code[11];
        memset(code, 0, 11*sizeof(code[0]));
        while(fscanf(ptr,"%c",&x)!=EOF){
            memset(code, -1, 11*sizeof(int));
            encode1(root,buf,x,code,0,ptr2);
            ptr+sizeof(char);
        }
        fclose(ptr);
        if(n!=0){
            while(n!=7){
                buf[n]=0;
                n++;
            }
            int k=0;
            while(buf[k]!=-1 && k<7){
                k++;
            }
            unsigned char result=get_char(buf);
            fprintf(ptr2,"%c",result);
        }
        fclose(ptr2);
        printcode(root,code,0);
        printf("Generating %s",s2);
        }
    else{
        int v=0;
        node2* root2=create_tree(ptr);
        unsigned char q='a';
        fscanf(ptr,"%c",&q);
        int a1[6];
        z=0;
        memset(a1,-1,6*sizeof(int));
        while(q!=64){
            a1[z]=q-'0';
            ptr+sizeof(char);
            fscanf(ptr,"%c",&q);
            z++;
        }
        z=5;
        total=0;
        int f=1;
        while(z>-1){
            if(a1[z]!=-1){
                total=total+f*a1[z];
                f=f*10;
            }
            z--;
        }
        decoder(data1,&v,ptr,root2,ptr2,total);
        printf("Generating %s",s3);
        fclose(ptr);
        fclose(ptr2);
        }
    
}