//150200011 Çağla Mıdıklı
// EB
// Implementing Binary Search Tree in C++

#include <iostream>

namespace BST {
  struct Node {
    int data;
    std::string name;
    Node *parent=NULL ;   //for begining ever y nodes parent left and right child is null
    Node *left=NULL;
    Node *right=NULL;
  };
}

class BinarySearchTree {
private:
  BST::Node *root;//to acces root node
  int size = 0; //to write tree on array

public:
  BinarySearchTree() {//constructor
    root = NULL;
  }
  BST::Node* getroot() {//return root node
    BST::Node* x = this->root;
       return x;
  }
  void preorder(std::pair<std::string, int> *array,int sizes) {//for walk all tree, call preorderfunction with root
    BST::Node *x = this->root;
    this->size = sizes;//start index
    preorderhelper(x,array);  
  }
   void preorderhelper(BST::Node* x,std::pair<std::string, int> *array) {//first parent, second left child then right child 
    if(x != NULL){
      array[this->size].first = x->name;
      array[this->size].second = x->data;//write array
      this->size++ ;
      preorderhelper(x->left,array);//call itself recursively
      preorderhelper(x->right,array);
    }
  }
  
 void inorder(std::pair<std::string, int> *array,int sizes) {//for walk all tree, call inorderhelperfunction with root
    BST::Node *x = this->root;
    this->size = sizes;
    inorderhelper(x,array);       
  }
   void inorderhelper(BST::Node* x,std::pair<std::string, int> *array) {//first left child, second parent then right child 
    if(x != NULL){
      inorderhelper(x->left,array);
      array[this->size].first = x->name;//write array
      array[this->size].second = x->data;
      this->size++ ; 
      inorderhelper(x->right,array);//call itself recursively
    }
  
        
  }
   void postorder(std::pair<std::string, int> *array,int sizes) {//for walk all tree, call postorderfunction with root
    BST::Node *x = this->root;
    this->size = sizes;
    postorderhelper(x,array);
  
        
  }
   void postorderhelper(BST::Node* x,std::pair<std::string, int> *array) {//first left child, second right child then  parent
    if(x != NULL){
      postorderhelper(x->left,array);
      postorderhelper(x->right,array);//call itself recursively
      array[this->size].first = x->name;
      array[this->size].second = x->data;
      this->size++ ; 
    }
  }
  BST::Node* searchTree(int testpop) {//It traverses the branches of the tree until it finds tinput value, determining its direction by comparing the input data with the current node s data at each step.
    BST::Node *x = this->root;
    while(x != NULL && x->data != testpop){
      if(testpop < x->data){
        x = x->left;
      }
      else{
        x = x->right;
      }
      } return x;
  }

  BST::Node* successor(BST::Node* x) {// for finding  e node with the smallest data value greater than x.data
    BST::Node *y =x->parent;
    if(x->right != NULL){//if x is not maximum 
      return this->getMinimumHelper(x->right);
    }
    else{
      while(y != NULL && x == y->right){
        x = y;
        y = y->parent;
      }
      return y;
    }
  }

  BST::Node* predecessor(BST::Node* x) {//symmetry with successor
    BST::Node *y =x->parent;
    if(x->left != NULL){
      return this->getMaximumHelper(x->left);
    }
    else{
      
      while(y != NULL && x == y->left){
        x = y;
        y = y->parent;
      }
    return y;
    }
    

  }

  

void insert(std::string name,int population ) {

    BST::Node *x = this->root;
    BST::Node *y =NULL;
    BST::Node *z = new BST::Node;//create new node for insertion

    z->data = population;
    z->name=name;y = x;
    while(y != NULL ){//To decide new node will be the child of which leaf.
        if(population < y->data ){
          if(y->left == NULL){//find the leaf break the loop
            break;
          }
          else{y =y->left;}
        }
        else{
          if(y->right == NULL){
            break;
          }else{
          y= y->right;}
        }
    }
    z->parent = y ; //set to new node parent finding leaf
    if(x ==NULL){
      this->root = z;
    }
    else if(z->data < y->data){//leaf left child
      y->left =z;
    }
    else{//leaf right child
      y->right = z;
    }
  }

  void deleteNode(int testpop) {
    BST::Node *x = NULL;
    x = searchTree( testpop);//find the node
    if(x->left == NULL){//z has no left child, according to deletion z's parent become z's right child parent
      deleteNodeHelper(x,x->right);
    }
    else if(x->right == NULL){//z has no right child, according to deletion z's parent become z's left child parent
      deleteNodeHelper(x,x->left);
    }
    else{
      BST::Node *y = this->getMinimumHelper(x->right);//return subtree s most left child minumum child
      if(y!=x->right){
        deleteNodeHelper(y,y->right);
        y->right = x->right;
        y->right->parent = y;
      }
      deleteNodeHelper(x,y);
      y->left=x->left;//exchange y and z attribute
      y->left->parent = y;
    }
      delete x;
  }
  void deleteNodeHelper(BST::Node *x,BST::Node *y) {//transparent
      BST::Node* k = x;
      if(x->parent == NULL){//if first element
        this->root = y;
      }

      else if (x == x->parent->left){//x = y
        x->parent->left = y;
      }
      else{//if z is a right child
        x->parent->right = y;
      }
      if(y != NULL){
        y->parent = x->parent;
      }
      
  }

  int getHeight() {//sends the root as a reference to calculate the total height of the tree
    BST::Node *x =this->root;
    int y = getHeightHelper(x);
    return y-1;//reason of minus 1 is root s height equal to zero
  }

  BST::Node* getMaximum() {//search the rightmost child, for calculate all tree ' s maximum send to root for reference
    BST::Node *x =this->root;
    while(x->right != NULL){
      x = x->right;
    }
    return x;
  }
    BST::Node* getMaximumHelper(BST::Node *x) {//search the rightmost child started reference node
    while(x->right != NULL){
      x = x->right;
    }
    return x;
  }
  int getHeightHelper(BST::Node *x){
    if(x==NULL){
      return 0;
    }
    else{
      int left_height = getHeightHelper(x->left);//calculate all branch recursively
      int right_height = getHeightHelper(x->right);
      if(right_height<left_height  ){
        return(left_height + 1);//return the higher value and iterate height
      }
      else{return right_height+1;}

    }
  }

  BST::Node* getMinimum() {//search the leftmost child, for calculate all tree ' s minumum send to root for reference
    
    BST::Node *x =this->root;
    while(x->left != NULL){
      x = x->left;
    }
    return x;
  }
    BST::Node* getMinimumHelper(BST::Node *x) {//search the leftmost child started reference node
    
    
    while(x->left != NULL){
      x = x->left;
    }
    return x;
  }


   
  
  int getTotalNodes() {//calculate all nodes recursively, for all tree send root as a reference
    
    if(this->root == NULL){
      return 0;
    }else{return getTotalNodesHelper(this->root);}
    
  }
  int getTotalNodesHelper(BST::Node *x) {//calculate all nodes recursively starting the reference point
    if(x == NULL){return 0;}
    else{
      int left = getTotalNodesHelper(x->left);
      int right = getTotalNodesHelper(x->right);
      return left + right + 1;
  }}
  


};