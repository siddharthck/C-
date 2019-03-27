/*
Problem statement: write a function for insertion of element in AVL tree.
Author :Siddharth Kulkarni
I have written insertToAVL,lRotate,rRotate functions. Rest of the code was available on geeksforgeeks.org

*/


//------------------------------------------------------------------------------------------------------------------------
#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};
int heigh(struct Node* Node)
{
   /* base case tree is empty */
   if(Node == NULL)
       return 0;
 
   /* If tree is not empty then height = 1 + max of left
      height and right heights */
   return 1 + max(heigh(Node->left), heigh(Node->right));
} 
bool isBalanced(struct Node *root)
{
   int lh; /* for height of left subtree */
   int rh; /* for height of right subtree */ 
 
   /* If tree is empty then return true */
   if(root == NULL)
    return 1; 
 
   /* Get the height of left and right sub trees */
   lh = heigh(root->left);
   rh = heigh(root->right);
 
   if( abs(lh-rh) <= 1 &&
       isBalanced(root->left) &&
       isBalanced(root->right))
     return 1;
 
   /* If we reach here then tree is not height-balanced */
   return 0;
}
 
/* UTILITY FUNCTIONS TO TEST isBalanced() FUNCTION */
 
/* returns maximum of two integers */
   
 
/*  The function Compute the "height" of a tree. Height is the
    number of Nodes along the longest path from the root Node
    down to the farthest leaf Node.*/
int _B_(Node *root)
{
    if(root==NULL)
        return 0;
    int lH = _B_(root->left);
    if(lH==-1)return -1;
    int rH = _B_(root->right);
    if(rH==-1)
        return -1;
    if(abs(lH-rH)>1)
        return -1;
    return max(lH,rH)+1;
}
bool _B(Node *root)
{
    if(_B_(root)==-1)
        return false;
    else 
        return true;
}
bool I_(Node* root)
{
    static struct Node *prev = NULL;
     
    if (root)
    {
        if (!I_(root->left))
          return false;
 
        if (prev != NULL && root->data <= prev->data)
          return false;
 
        prev = root;
 
        return I_(root->right);
    }
 
    return true;
}
Node* insertToAVL(Node* Node, int data);
vector<int> z;
void inorder(Node *root)
{
//	z.clear();
	if(root==NULL)
	return;
	{
		inorder(root->left);
		z.push_back(root->data);
		inorder(root->right);
	}
}
/* Drier program to test above function*/
int main()
{
int t;
cin>>t;
while(t--)
{
    int q;
    cin>>q;
    Node *root = NULL;
    bool f= true;
    vector<int> a;
    while(q--)
    {
        int k;
        cin>>k;
        a.push_back(k);
        root = insertToAVL(root,k);
    
        if(!isBalanced(root)){
         
            f=false;
            break;
        }
    }
    
    z.clear();
    
    inorder(root);
    
    set<int> s(a.begin(),a.end());
   	vector<int>zz(s.begin(),s.end());
    if(z.size()!=zz.size())
    f=false;
    else{
    for(int i=0;i<z.size();i++)
    {
    	if(z[i]!=zz[i])
    	f=false;
    }
    }
    if(f)
        cout<<1<<endl;
    else 
        cout<<0<<endl;
}
return 0;
}


//------------------------------------------------------------------------------------------------------------------------
//Above problem was on geeksorgeeks.org for practicing
//these are the functions i have written in order to insert an element in AVL tree
//

// function to return height
int height(Node * node){
if(node==NULL)return 0;
else return node->height;

}

// function returns balence of a node
int balence(Node * root){
  if(root==NULL)return 0;
  else return height(root->left) - height(root->right);

}
Node * newnode(int key){
struct Node* node = (struct Node*) 
                        malloc(sizeof(struct Node)); 
node->left=NULL;node->right=NULL;node->data=key;node->height=1;
return node;
}

//left rotate
Node * lRotate(Node *node){
Node * z,*y;Node * temp;
z=node;
y=z->right;
//x=y->right;
temp=y->left;
y->left =z;
z->right=temp;

// also we have to change the height first change the z's because z is now child of y
z->height=max(height(z->left),height(z->right))+1;

y->height=max(height(y->left),height(y->right))+1;
return y;
}

//right rotate
Node * rRotate(Node *node){
Node * z,*y;Node * temp;
z=node;
y=z->left;
//x=y->left;
temp=y->right;
y->right=z;
z->left=temp;

// also we have to change the height first change the z's because z is now child of y
z->height=max(height(z->left),height(z->right))+1;
y->height=max(height(y->left),height(y->right))+1;

return y;

}




Node* insertToAVL( Node* root, int key)
{
    //Your code here

if(root==NULL){return (newnode(key));}

if(key<root->data)root->left=insertToAVL(root->left,key);
else if(key>root->data) root->right=insertToAVL(root->right,key);
else return root;
//height is always maximum of its chilren's height +1
root->height=max(height(root->left),height(root->right))+1;
int bal=balence(root);
//if bal is negative right chid's height is more
if(bal>1 && key<root->left->data){//key got inserted in root-left-left
  //right rotate

   return rRotate(root);
}
if(bal>1 && key>root->left->data){//key got inserted in root-left-right
//left right rotate
root->left=lRotate(root->left);
return rRotate(root);
}
if(bal<-1 && key>root->right->data){//key got inserted in root-right-right
// left rotate
    return lRotate(root);
}

if(bal<-1 && key<root->right->data){//key got inserted in root-right-left
  //right left rotate
    root->right=rRotate(root->right);
  return lRotate(root);

}
//cout<<"root not null  "<<key<<endl;
return root;


}
