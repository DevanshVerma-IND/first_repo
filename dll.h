//much more to edit here
#ifndef DDL_H
#define DDL_H

#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* prev;
    struct node* next;
};

static inline struct node* createNode(int val);
static inline int size(struct node** head);
static inline void insertBegin(struct node** head,int val);
static inline void insertEnd(struct node** head,int val);
static inline void insertAfter(struct node** head,int val,int k);
static inline void insertBefore(struct node** head,int val,int k);
static inline void insertAt(struct node** head,int val,int pos);
static inline void deleteBegin(struct node** head);
static inline void deleteK(struct node** head,int k);
static inline void deleteEnd(struct node** head);
static inline void deleteAt(struct node** head,int pos);
static inline void display(struct node** head);
static inline void deleteAll(struct node** head);

static inline struct node* createNode(int val){
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    if(!temp){
        printf("Heap overflow\n");
        exit(1);
    }
    temp->data=val;
    temp->prev=temp->next=NULL;
    return temp;
}

static inline int size(struct node** head){
    int count=0;
    struct node* temp=*head;
    while(temp){
        count++;
        temp=temp->next;
    }
    return count;
}

static inline void insertBegin(struct node** head,int val){
    if(!*head){
        *head=createNode(val);
        return;
    }
    struct node* temp=createNode(val);
    (*head)->prev=temp;
    temp->next=*head;
    *head=temp;
}

static inline void insertEnd(struct node** head,int val){
    if(!*head){
        *head=createNode(val);
        return;
    }
    struct node* temp=createNode(val);
    struct node* tail=*head;
    while(tail->next){
        tail=tail->next;
    }
    tail->next=temp;
    temp->prev=tail;
}

static inline void insertAfter(struct node** head,int val,int k){
    if(!*head){
        *head=createNode(val);
        return;
    }
    struct node* curr=*head;
    while(curr && curr->data!=k){
        curr=curr->next;
    }
    if(curr){
        struct node* temp=createNode(val); // writing here and not before declaring curr prevents memory leak
        temp->next=curr->next;
        temp->prev=curr;
        if(curr->next) // this saves from segmention fault because k can be found at last and (curr->next)->prev dereferences curr->next which is NULL
        curr->next->prev=temp;
        curr->next=temp;
    }
    else{
        printf("%d not found\n",k);
    }
}

static inline void insertBefore(struct node** head,int val,int k){
    if(!*head){
        *head=createNode(val);
        return;
    }
    if((*head)->data==k){
        insertBegin(head,val);
        return;
    }
    struct node* curr=*head;
    struct node* p=NULL;
    while(curr && curr->data!=k){
        p=curr;
        curr=curr->next;
    }
    if(curr){
        struct node* temp=createNode(val);
        temp->next=curr;
        temp->prev=p;
        p->next=temp;
        curr->prev=temp;
    }
    else{
        printf("%d not found\n",k);
    }
}

static inline void insertAt(struct node** head,int val,int pos){
    if(!*head){
        *head=createNode(val);
        return;
    }
    if(pos<0 || pos>size(head)){
        printf("index error\n");
        exit(1);
    }
    if(pos==0){
        insertBegin(head,val);
        return;
    }
    struct node* temp=createNode(val);
    struct node* curr=*head;
    for(int i=0;i<pos-1;i++){
        curr=curr->next;
    }
    temp->next=curr->next;
    temp->prev=curr;
    if(curr->next)
    curr->next->prev=temp;
    curr->next=temp;
}

static inline void deleteBegin(struct node** head){
    if(!*head){
        return;
    }
    struct node* temp=*head;
    *head=(*head)->next;
    if(*head) // somehow i need to check this despite the checking in earlier if block, helps in deleteAll()
    (*head)->prev=NULL;
    free(temp);
}


static inline void deleteEnd(struct node** head){
    if(!*head){
        return;
    }
    struct node* temp=*head;
    if(!temp->next){
        free(temp);
        *head=NULL;
        return;
    }
    struct node* p=NULL;
    while(temp->next){
        p=temp;
        temp=temp->next;
    }
    p->next=NULL;
    free(temp);
}

static inline void deleteK(struct node** head,int k){
    if(!*head){
        return;
    }
    if((*head)->data==k){
        deleteBegin(head);
        return;
    }
    struct node* curr=*head;
    while(curr && curr->data!=k){
        curr=curr->next;
    }
    if(curr){
        curr->prev->next=curr->next;
        if(curr->next){
            curr->next->prev=curr->prev;
        }
        free(curr);
    }
    else{
        printf("%d not found\n",k);
    }
}

static inline void deleteAt(struct node** head,int pos){
    if(!*head){
        return;
    }
    if(pos<0 || pos>=size(head)){
        printf("index error\n");
        return;
    }
    if(pos==0){
        deleteBegin(head);
        return;
    }
    struct node* curr=*head;
    for(int i=0;i<pos;i++){
        curr=curr->next;
    }
    curr->prev->next=curr->next;
    if(curr->next){
        curr->next->prev=curr->prev;
    }
    free(curr);
}

static inline void deleteAll(struct node** head){
    while(*head){
        deleteBegin(head);
    }
    printf("cleared\n");
}

static inline void display(struct node** head){
    struct node* temp=*head;
    while(temp){
        printf("%d->",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}

#endif
