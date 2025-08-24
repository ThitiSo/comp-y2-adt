#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node* parent;
    struct node* firstchild;
    struct node* nextchild;
} tree_t;
typedef struct stack{
    int val;
    struct stack* next;

}stack;

stack* add(stack* s, int x){
    stack * tmp = (stack* )malloc(sizeof(stack));
    tmp->val = x;
    tmp->next=NULL;
    tmp->next = s;
    return tmp;
}
stack *pop(stack* s){
    if (s == NULL) return NULL;
    return s->next;
}


tree_t* search_node(tree_t *t, int val){
    if (t == NULL) return NULL;
    if (t->val == val) return t;

    tree_t *found = search_node(t->firstchild, val);
    if (found != NULL) return found;

    return search_node(t->nextchild, val);
}

tree_t * attach(tree_t * t,int valpar,int valchild){
    tree_t *newnode = (tree_t * )malloc(sizeof(tree_t));
    newnode->val = valchild;
    newnode->parent = NULL;
    newnode->firstchild = NULL;
    newnode->nextchild = NULL;

    tree_t* tmp = search_node(t,valpar);
    newnode->parent = tmp;
    if(tmp == NULL) return newnode;
    if(tmp->firstchild == NULL){
        tmp->firstchild = newnode;
    }else{
        tree_t* si = tmp->firstchild;
        while(si->nextchild != NULL){
            si = si->nextchild;
        }
        si->nextchild = newnode;


    }
    return t;

}
tree_t* detach(tree_t *t, int x) {
    tree_t *target = search_node(t, x);
    tree_t *parent = target->parent;
    tree_t *child = parent->firstchild;

    if (child == target) {
        parent->firstchild = target->nextchild;
    } else {
        while (child->nextchild != target) {
            child = child->nextchild;
        }
        child->nextchild = target->nextchild;
    }

    target->parent = NULL;
    target->nextchild = NULL;

    return t;
}


int search(tree_t * t ,int x){
    tree_t * se  = search_node(t,x);
    return se != NULL;
}

int degree(tree_t* t,int x){
    tree_t* root = search_node(t,x);
    if (root->firstchild  == NULL) return 0;
    int count = 1;
    tree_t* tmp = root-> firstchild;
    while(tmp-> nextchild != NULL){
        tmp = tmp->nextchild;
        count++;
    }
    return count;
}
int is_root(tree_t * t , int x){
    tree_t* root = search_node(t,x);
    if(root->parent == NULL) return 1;
    return 0;
}
int is_leaf(tree_t * t,int x){
    tree_t* leaf = search_node(t,x);
    if(leaf->firstchild == NULL) return 1;
    return 0;
}

void siblings(tree_t * t, int x){
    tree_t * node = search_node(t,x);
    if (node == NULL || node->parent == NULL){
        printf("\n");
        return;
    }
    tree_t* parent = node->parent;

    int count_sibling = 0;
    tree_t* child = parent->firstchild;
    while(child != NULL){
        if (child->val!= x){
            count_sibling ++;
            printf("%d",child->val);
        }
        child=child->nextchild;
    }
    if (count_sibling == 0) printf("\n");
    return;
}

int depth(tree_t * t,int x){
    tree_t* node = search_node(t,x);
    if (node == NULL) return 0;
    int count_depth =0;
    while (node->parent != NULL){
        count_depth++;
        node= node->parent;

    }
    return count_depth;
}

void print_path(tree_t * t , int x, int y){
    tree_t* child = search_node(t,y);
    stack *s = NULL;
    while(child->val !=x){
        s = add(s,child->val);

        child=child->parent;
    }
    s = add(s,child->val);
    while(s!=NULL){
        printf("%d ",s->val);
        s=pop(s);
    }
    printf("\n");
    return;
}

int path_length(tree_t * t , int x, int y){
    tree_t* child = search_node(t,y);
    stack *s = NULL;
    int count = 0;
    while(child->val !=x){
        s = add(s,child->val);

        child=child->parent;
    }
    s = add(s,child->val);
    while(s!=NULL){
        //printf("%d ",s->val);
        count++;
        s=pop(s);
    }
    return count;

}

void ancestor(tree_t * t , int x){
    tree_t* child = search_node(t,x);
    stack *s = NULL;
    while(child->parent !=NULL){
        s = add(s,child->val);

        child=child->parent;
    }
    s = add(s,child->val);
    while(s!=NULL){
        printf("%d ",s->val);
        s=pop(s);
    }
    printf("\n");
    return;

}
typedef struct queue {
    tree_t* node;
    struct queue* next;
} queue;

queue* enqueue(queue* q, tree_t* node) {
    queue* tmp = (queue*)malloc(sizeof(queue));
    tmp->node = node;
    tmp->next = NULL;
    if (q == NULL) return tmp;

    queue* tail = q;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = tmp;
    return q;
}

queue* dequeue(queue* q, tree_t** node_out) {
    if (q == NULL) return NULL;
    *node_out = q->node;
    queue* next = q->next;
    free(q);
    return next;
}

void descendant(tree_t* t, int x) {
    tree_t* start = search_node(t, x);
    if (start == NULL) return;

    queue* q = NULL;
    q = enqueue(q, start);

    while (q != NULL) {
        tree_t* current;
        q = dequeue(q, &current);
        printf("%d ", current->val);

        tree_t* child = current->firstchild;
        while (child != NULL) {
            q = enqueue(q, child);
            child = child->nextchild;
        }
    }

    printf("\n");
}


void bfs(tree_t* t) {
    if (t == NULL) return;

    queue* q = NULL;
    q = enqueue(q, t);

    while (q != NULL) {
        tree_t* current;
        q = dequeue(q, &current);
        printf("%d ", current->val);

        tree_t* child = current->firstchild;
        while (child != NULL) {
            q = enqueue(q, child);
            child = child->nextchild;
        }
    }
    printf("\n");
}
void dfs(tree_t* t) {
    if (t == NULL) return;

    printf("%d ", t->val);

    tree_t* child = t->firstchild;
    while (child != NULL) {
        dfs(child);
        child = child->nextchild;
    }

}





void print_tree(tree_t* t) {
    if (t == NULL) return;


    static int level = 0;

    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d\n", t->val);

    level++;
    tree_t* child = t->firstchild;
    while (child != NULL) {
        print_tree(child);
        child = child->nextchild;
    }
    level--;
}


int main(void) {
tree_t *t = NULL;
int n, i, command;
int parent, child, node, start, end;
scanf("%d", &n);
for (i=0; i<n; i++) {
scanf("%d", &command);
switch(command) {
case 1:
scanf("%d %d", &parent, &child);
t = attach(t, parent, child);
break;
case 2:
scanf("%d", &node);
t = detach(t, node);
break;
case 3:
scanf("%d", &node);
printf("%d\n", search(t, node));
break;
case 4:
scanf("%d", &node);
printf("%d\n", degree(t, node));
break;
case 5:
scanf("%d", &node);
printf("%d\n", is_root(t, node));
break;


case 6:
scanf("%d", &node);
printf("%d\n", is_leaf(t, node));
break;
case 7:
scanf("%d", &node);
siblings(t, node);
break;
case 8:
scanf("%d", &node);
printf("%d\n", depth(t, node));
break;
case 9:
scanf("%d %d", &start, &end);
print_path(t, start, end);
break;
case 10:
scanf("%d %d", &start, &end);
printf("%d\n",
path_length(t, start, end));
break;
case 11:
scanf("%d", &node);
ancestor(t, node);
break;
case 12:
scanf("%d", &node);
descendant(t, node);
break;
case 13:
bfs(t);
break;
case 14:
dfs(t);
break;
case 15:
print_tree(t);
break;
 }
}
return 0;
}
