#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    int connected;
    struct node* parent;
    struct node* firstchild;
    struct node* nextchild;
} tree_t;



tree_t* search_node(tree_t *t, int val){
    if (t == NULL) return NULL;
    if (t->val == val) return t;

    tree_t *found = search_node(t->firstchild, val);
    if (found != NULL) return found;

    return search_node(t->nextchild, val);
}

tree_t *attach(tree_t *t, int valpar, int valchild){
    tree_t *newnode = (tree_t *)malloc(sizeof(tree_t));
    newnode->val = valchild;
    newnode->connected = 0;
    newnode->parent = NULL;
    newnode->firstchild = NULL;
    newnode->nextchild = NULL;

    if (t == NULL) {
   
        tree_t *root = (tree_t *)malloc(sizeof(tree_t));
        root->val = valpar;
        root->connected = 0;
        root->parent = NULL;
        root->firstchild = newnode;
        root->nextchild = NULL;

        newnode->parent = root;
        return root;
    }

    tree_t *tmp = search_node(t, valpar);
    newnode->parent = tmp;

    if (tmp == NULL) return t;

    if (tmp->firstchild == NULL) {
        tmp->firstchild = newnode;
    } else {
        tree_t *si = tmp->firstchild;
        while (si->nextchild != NULL) {
            si = si->nextchild;
        }
        si->nextchild = newnode;
    }

    return t;
}




int dfs(tree_t* t, int* tower_count) {
    if (t == NULL) return 1; 

    int child_needs_tower = 0;

    tree_t* child = t->firstchild;
    while (child != NULL) {
        int child_status = dfs(child, tower_count);
        if (child_status == 0) {
            child_needs_tower = 1; 
        }
        child = child->nextchild;
    }

    if (child_needs_tower) {
        t->connected = 2; 
        (*tower_count)++;
        return 1; 
}
  
    child = t->firstchild;
    while (child != NULL) {
        if (child->connected == 2) {
            t->connected = 1;
            return 1;
        }
        child = child->nextchild;
    }

    return 0; 

}

int main(void) {

tree_t *t = NULL;
int n, i, command;
int parent, child, node, start, end;
scanf("%d", &n);
for (i=0; i<n; i++) {
scanf("%d %d", &parent, &child);
t = attach(t, parent, child);

 }
int tower_count = 0;
if (t == NULL) {
    
}
else if (dfs(t, &tower_count) == 0) {

    t->connected = 2;
    tower_count++;
}
printf("%d", tower_count);
}











