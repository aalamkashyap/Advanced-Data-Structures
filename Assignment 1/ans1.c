#include <stdio.h>
#include <stdlib.h>

struct AVLTreeNode
{
	struct AVLTreeNode *left;
	struct AVLTreeNode *right;
	int data;
	int height;
};

int max(int a,int b)
{
	return (a>b)?a:b;
}


int minValue(struct AVLTreeNode *node)
{	
	struct AVLTreeNode *current = node;
	while(current->left!=NULL)
		current = current->left;
	return current->data;
}


struct AVLTreeNode *minValueNode(struct AVLTreeNode *node)
{	
	struct AVLTreeNode *current = node;
	while(current->left!=NULL)
		current = current->left;
	return current;
}

struct AVLTreeNode *maxValueNode(struct AVLTreeNode **node)
{	
	struct AVLTreeNode *current = *node;
	while(current->right!=NULL)
		current = current->right;
	return current;
}

int Height(struct AVLTreeNode **root)
{
	if(*root == NULL)
		return -1;
	else return (*root)->height;
}

int balancefactor(struct AVLTreeNode **node)
{
    if (*node == NULL)
        return 0;
    return Height(&((*node)->left)) - Height(&((*node)->right));
}

struct AVLTreeNode *SingleRotateLeft(struct AVLTreeNode **X)
{
	struct AVLTreeNode *W = (*X)->left;
	(*X)->left = W->right;
	W->right = *X;
	(*X)->height = max(Height(&((*X)->left)),Height(&((*X)->right)))+1;
	W->height = max(Height(&(W->left)),(*X)->height)+1;
	return W;	
}

struct AVLTreeNode *SingleRotateRight(struct AVLTreeNode **W)
{
	struct AVLTreeNode *X = (*W)->right;
	(*W)->right = X->left;
	X->left = *W;
	(*W)->height = max(Height(&((*W)->right)),Height(&((*W)->left)))+1;
	X->height = max(Height(&(X->right)),(*W)->height)+1;
	return X;	
}

struct AVLTreeNode *DoubleRotateWithLeft(struct AVLTreeNode **Z)
{
	(*Z)->left = SingleRotateRight(&((*Z)->left));
	return SingleRotateLeft(Z);
}

struct AVLTreeNode *DoubleRotateWithRight(struct AVLTreeNode **X)
{
	(*X)->right = SingleRotateLeft(&((*X)->right));
	return SingleRotateRight(X);
}

struct AVLTreeNode *Insert(struct AVLTreeNode **root, int data)
{
	if(*root==NULL)
	{
		*root = (struct AVLTreeNode*) malloc(sizeof(struct AVLTreeNode**));
		if(*root == NULL)
		{
			printf("Memory Error");
			return NULL;
		}
		else
		{
			(*root)->data = data;
			(*root)->height = 0;
			(*root)->left = (*root)->right = NULL;
		}
	}
	else if(data < (*root)->data)
	{
		(*root)->left = Insert(&((*root)->left),data);
		if(Height(&((*root)->left)) - Height(&((*root)->right)) == 2)
		{
			if(data < (*root)->left->data)
				*root = SingleRotateLeft(root);
			else
				*root = DoubleRotateWithLeft(root);
		}
	}
	else if(data > (*root)->data)
	{
		(*root)->right = Insert(&((*root)->right),data);
		if(Height(&((*root)->right)) - Height(&((*root)->left)) == 2)
		{
			if(data < (*root)->right->data)
				*root = SingleRotateRight(root);
			else
				*root = DoubleRotateWithRight(root);
		}
	}
	(*root)->height = max(Height(&((*root)->left)),Height(&((*root)->right)))+1;
	return *root;
}


struct AVLTreeNode *deleteNode(struct AVLTreeNode **root, int key)
{
	if (*root == NULL)
	        return *root;
	if ( key < (*root)->data )
        	((*root)->left) = deleteNode(&((*root)->left), key);
    	else if( key > (*root)->data)
        	((*root)->right) = deleteNode(&((*root)->right), key);
	else
	{
        	if( ((*root)->left == NULL) || ((*root)->right == NULL) )
        	{
            		struct AVLTreeNode *temp = ((*root)->left) ? ((*root)->left) : ((*root)->right);
            		if (temp == NULL)
            		{
                		temp = *root;
                		*root = NULL;
            		}
            		else
             		*root = temp;
		        free(temp);
        	}
        	else
        	{
            		struct AVLTreeNode* temp = minValueNode((*root)->right);
            		((*root)->data) = temp->data;
            		((*root)->right) = deleteNode(&((*root)->right), temp->data);
        	}
    	}
    	if (*root == NULL)
      		return *root;
    	
    	int balance = balancefactor(root);
 
    	if (balance > 1 && balancefactor(&((*root)->left)) >= 0)
        	return SingleRotateLeft(root);
 
 	if (balance > 1 && balancefactor(&((*root)->left)) < 0)
    		return DoubleRotateWithLeft(root);
    
    	if (balance < -1 && balancefactor(&((*root)->right)) <= 0)
        	return SingleRotateRight(root);
 
 	if (balance < -1 && balancefactor(&((*root)->right)) > 0)
        	return DoubleRotateWithRight(root);
	(*root)->height = max(Height(&((*root)->left)),Height(&((*root)->right)))+1;
 	return *root;
}

void preorder(struct AVLTreeNode *root)
{
	if(root != NULL)
	{
		printf("%d ",root->data);
		preorder(root->left);
		preorder(root->right);
	}
	
}
struct AVLTreeNode *mergeTree(struct AVLTreeNode **root1, struct AVLTreeNode **root2, int temp)
{
	if(abs(Height(root1) - Height(root2))<=1)
     	{  
		struct AVLTreeNode *troot = (struct AVLTreeNode*) malloc(sizeof(struct AVLTreeNode*));
        	troot->data = temp;
        	troot->left = *root1;
        	troot->right = *root2;
        	*root2 = NULL;
        	return troot;
     	}
     	else if(Height(root1) > Height(root2))
     	{
		struct AVLTreeNode *temproot = (struct AVLTreeNode*) malloc(sizeof(struct AVLTreeNode*));
        	temproot = mergeTree(&((*root1)->right), root2, temp);
		temproot->height = max(Height(&(temproot->left)),Height(&(temproot->right)))+1;
         	(*root1)->right = temproot;
         	int balance = balancefactor(root1);
 
    		if (balance > 1 && balancefactor(&((*root1)->left)) >= 0)
        		return SingleRotateLeft(root1);
 
 		if (balance > 1 && balancefactor(&((*root1)->left)) < 0)
    			return DoubleRotateWithLeft(root1);
    
    		if (balance < -1 && balancefactor(&((*root1)->right)) <= 0)
        		return SingleRotateRight(root1);
 
 		if (balance < -1 && balancefactor(&((*root1)->right)) > 0)
        		return DoubleRotateWithRight(root1);
         	return *root1;
     	}

     	else if(Height(root1) < Height(root2))
     	{
		struct AVLTreeNode *temproot = (struct AVLTreeNode*) malloc(sizeof(struct AVLTreeNode*));
        	temproot = mergeTree(root1, &((*root2)->left), temp);
		temproot->height = max(Height(&(temproot->left)),Height(&(temproot->right)))+1;
         	(*root2)->left = temproot;
         	int balance = balancefactor(root2);
    		if (balance > 1 && balancefactor(&((*root2)->left)) >= 0)
        		return SingleRotateLeft(root2);
 
 		if (balance > 1 && balancefactor(&((*root2)->left)) < 0)
    			return DoubleRotateWithLeft(root2);
    
    		if (balance < -1 && balancefactor(&((*root2)->right)) <= 0)
        		return SingleRotateRight(root2);
 
 		if (balance < -1 && balancefactor(&((*root2)->right)) > 0)
        		return DoubleRotateWithRight(root2);
         	return *root2;
     } 
     	
}

struct AVLTreeNode *merge(struct AVLTreeNode **root1, struct AVLTreeNode **root2)
{
	struct AVLTreeNode *temp = maxValueNode(root1);
	*root1  = deleteNode(root1,temp->data);	
	struct AVLTreeNode *tree = mergeTree(root1,root2,temp->data);
	return tree;
}



int main()
{
	struct AVLTreeNode *root1 = NULL;
	struct AVLTreeNode *root2 = NULL;
	struct AVLTreeNode *root4 = NULL;
	struct AVLTreeNode *v = NULL;
	int k,data,ch,x;
	
	int i = 0,n,m,h,h11;
	printf("Enter the number of nodes in tree 1:\n");
	scanf("%d",&n);
	while(i<n)
	{
		printf("Enter value %d :\n",i+1);
		scanf("%d",&data);
		root1 = Insert(&root1,data);
		i++;
	}
	
	i = 0;
	printf("Enter the number of nodes in tree 2:\n");
	scanf("%d",&m);
	while(i<m)
	{
		printf("Enter value %d :\n",i+1);
		scanf("%d",&data);
		root2 = Insert(&root2,data);
		i++;
	}
	printf("\n");
	preorder(root1);
	printf("\n");
	preorder(root2);
	printf("\n");
	root4 = merge(&root1,&root2);
	printf("Preorder traversal of final tree:\n");
	preorder(root4);
	printf("\n");	
	return 0;
}

