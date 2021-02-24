#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXITERATIONS 100

struct tnode {
    int tnum;
    struct tnode *right;
    struct tnode *left;
};

static struct tnode *talloc(void);
static void push(int *v,int c,int dim);
static int pop(int v[]);
static void put(int *s,struct tnode *t);
static void toprintt(struct tnode *t,char **list);
char **ntoaMS2020(char *s);

static int nterms;
static int memstack[MAXITERATIONS];
static int ilist;
static int tnodenum;
static int bufp;


char **ntoaMS2020(char *s)
{
    nterms = ilist = tnodenum = bufp = 0;

    int a[strlen(s)];
    
    // converts from char to int the string
    int bg;
    for (bg = 0;s[bg] != '\0';++bg)
        a[bg] = s[bg] - '0';
        
    a[bg] = -1;

    /* Parse the string */
    struct tnode *origin;

    origin = talloc();  // allocate the base ( first node )
    origin->tnum = 0;   // the first element is useless

    put(a,origin);  // generate the structure

    // creates the array of pointers detectable from outside
    char **mem = (char **) malloc(sizeof(char *) * nterms);

    // creates the solutions from the structure
    toprintt(origin,mem);

    // terminate the array
    mem[nterms] = NULL;

    return mem;
}



static void put(int *s, struct tnode *t)
{
    int c1 = s[0];
    int c2 = -1;

    t->left = NULL;     // contrary to right, left may not exist during the tree,
                        // so it must be initialized
    if (s[0] < 1 || s[0] > 26)     // sequence ended
    {
        t->right = NULL;
        ++nterms;       // number of terminations = number of solutions
        return;
    }

    if (s[1] != -1)
        c2 = s[1] + c1 * 10;
    
    if (c2 <= 26 && c2 >= 1)
    {
        t->left = talloc();    // create the left child
        t->left->tnum = c2;
        put(s + 2,t->left);
    }
    
    if (c1 != 0 && s[1] != 0)       // there is no character 0, it only exists as a one digit for a number> = of 10
    {
        t->right = talloc();    // create the right child
        t->right->tnum = c1;
        put(s + 1,t->right);
    }
    else
        t->right = NULL;  
}


static void toprintt(struct tnode *t,char **list)
{
    if ((t->left != NULL || t->right != NULL) && t->tnum != 0)    // its a node
    {
        push(memstack,t->tnum,MAXITERATIONS);     // save the element
        ++tnodenum;
    }

    else if (t->left == NULL && t->right == NULL)    // end of tree (the last node of each branch)
    {
        tnodenum++;
        push(memstack,t->tnum,MAXITERATIONS);     // save the element
        char *nbuf = (char*) malloc(tnodenum);  // memorise the branch of the tree

        int i = 0;
        for (i = 0;i < tnodenum;++i)
            nbuf[i] = memstack[i] + 96;
       
        nbuf[i] = '\0';

        list[ilist++] = nbuf;
    }
    
    // find a node (recursive)
    if (t->right != NULL)
        toprintt(t->right,list);
    if (t->left != NULL)
        toprintt(t->left,list);
    
    if (t->tnum != 0)
    {
        pop(memstack);  // extract to go up the tree
        --tnodenum;
    }    
}


static struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}


static void push(int *v,int c,int dim) // add
{
    if (bufp < dim)
        v[bufp++] = c; 
    else
        printf("STACK FULL\n"); 
}

static int pop(int v[]) // remove
{
    if (bufp > 0)
        return v[bufp--] = 0;
    else
        printf("STACK EMPTY\n");
}



