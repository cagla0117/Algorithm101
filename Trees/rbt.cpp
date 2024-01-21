//150200011 Çağla Mıdıklı
// EB
// Implementing Red-Black Tree in C++

#include <iostream>

namespace RBT {
  struct Node {
    int data;
    std::string name;
    Node *parent = nullptr;     //for begining ever y nodes parent left and right child is nullptr
    Node *left = nullptr;
    Node *right = nullptr;
    int color = 1;
  };
}

class RedBlackTree {
private:
RBT::Node *root;      //to acces root node
int size = 0;         //to write tree on array

public:
  RedBlackTree() {
    root = nullptr;   //constructor
  }
  RBT::Node* getroot() {//return root node
    RBT::Node* x = this->root;
       return x;
  }
  
  void preorder(std::pair<std::string, int> *array,int sizes) {//for walk all tree, call preorderfunction with root
    RBT::Node *x = this->root;
    this->size = sizes;//start index
    preorderhelper(x,array);  
  }
  void preorderhelper(RBT::Node* x,std::pair<std::string, int> *array) {//first parent, second left child then right child 
    if(x != NULL){
      array[this->size].first = x->name;
      array[this->size].second = x->data;//write array
      this->size++ ;
      preorderhelper(x->left,array);//call itself recursively
      preorderhelper(x->right,array);
    }
  }
  void inorder(std::pair<std::string, int> *array,int sizes) {//for walk all tree, call inorderhelperfunction with root
    RBT::Node *x = this->root;
    this->size = sizes;
    inorderhelper(x,array);
  }
  void inorderhelper(RBT::Node* x,std::pair<std::string, int> *array) {//first left child, second parent then right child 
    if(x != NULL){
      inorderhelper(x->left,array);
      array[this->size].first = x->name;//write array
      array[this->size].second = x->data;
      this->size++ ; 
      inorderhelper(x->right,array);//call itself recursively
    }      
  }
  void postorder(std::pair<std::string, int> *array,int sizes) {//for walk all tree, call postorderfunction with root
    RBT::Node *x = this->root;
    this->size = sizes;
    postorderhelper(x,array); 
  }
  void postorderhelper(RBT::Node* x,std::pair<std::string, int> *array) {//first left child, second right child then  parent
    if(x != NULL){
      postorderhelper(x->left,array);
      postorderhelper(x->right,array);//call itself recursively
      array[this->size].first = x->name;
      array[this->size].second = x->data;
      this->size++ ; 
    }
  }
  void rightrotate(RBT::Node* x) {//In this function,  node y is the new root of the subtree, with x as its left child and y's original left child as its right child.
    RBT::Node* y = x->left;     // y equals to x's left child
    if(y != NULL){x->left = y->right;}
    if(y->right != NULL){y->right->parent = x;}
    y->parent = x->parent;
    if(x->parent == nullptr){this->root = y;}
    else if (x == x->parent->right){ x->parent->right = y;}
    else { x->parent->left = y;}
    y->right = x;//y's right child parent is x
    x->parent =y;//x parents equals to y
  }

  void leftrotate(RBT::Node* x) {//symmetric to right rotate and complexity is O(1).
    RBT::Node* y;
    y = x->right;
    if(y != NULL){x->right = y->left;}
    if(y->left != NULL){ y->left->parent = x;}
    y->parent = x->parent;
    if(x->parent == nullptr){this->root = y;  }
    else if (x == x->parent->left){  x->parent->left = y;  }
    else{  x->parent->right = y; }
    y->left = x;
    x->parent =y;
    
  }

  RBT::Node* searchTree(int testpop) {//It traverses the branches of the tree until it finds tinput value, determining its direction by comparing the input data with the current node s data at each step.
    RBT::Node *x = this->root;
    while(x != NULL && x->data != testpop){
      if(testpop < x->data){
        x = x->left;
      }
      else{
        x = x->right;
      }
      } return x;
  }


  RBT::Node* successor(RBT::Node* x) {// for finding  e node with the smallest data value greater than x.data
    RBT::Node *y =x->parent;
    if(x->right != NULL){//if x is not maximum 
      return this->getMinimumHelper(x->right);//return minumum node
    }
    else{
      while(y != NULL && x == y->right){
        x = y;
        y = y->parent;
      }
    return y;
    } 
  }

  RBT::Node* predecessor(RBT::Node* x) {//symmetry with successor
    RBT::Node *y =x->parent;
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
    RBT::Node *x = this->root;
    RBT::Node *y =NULL;
    RBT::Node *z = new RBT::Node;//create new node for insertion
    z->data = population;
    z->name=name;
    y = x;
    while(y != NULL ){//To decide new node will be the child of which leaf.
        if(population < y->data ){          
          if(y->left == NULL){ break;}//find the leaf break the loop
          else{y =y->left;}  
        }
        else{
          if(y->right == NULL){break; }
          else{  y= y->right;} 
        }
    }
    if(y !=NULL ){ z->parent = y ; }//set to new node parent finding leaf
    if(x ==NULL){ this->root = z;}
    else if(z->data < y->data){ y->left =z;  }//leaf left child
    else{y->right = z; }//leaf right child
    //0 black 1 red
  if(x ==nullptr){
    z->color = 0;//root is black
    this->root=z;
  }
  else{
    z->color = 1;//firstly i insert red nodes because red nodes cant affect black height, the after change if it is necessary, 
    inserthelper(z);}
  }
  void inserthelper(RBT::Node* z){
    RBT::Node *y =NULL;
    while(z->parent != NULL && z->parent->color == 1 ){//if z's parent red it is a confict otherwise dont change 
      if(z->parent == z->parent->parent->left &&  z->parent->parent != NULL ){
          y = z->parent->parent->right;
          if(y !=  NULL && y->color == 1){//check for the segmentation fault
            z->parent->color = 0;//red nodes parent must be black
            y->color = 0; 
            z->parent->parent->color = 1;
            z = z->parent->parent;
          }
          else{
            if(z == z->parent->right){//if z is right child
              z=z->parent;
              leftrotate(z);//call left rotate
            }
            z->parent->color = 0;
          if(z->parent->parent != NULL ){//check the grandparent
            z->parent->parent->color = 1;
            rightrotate(z->parent->parent); }
          }
        }
      else{//symmetrict to if condition
        y = z->parent->parent->left;
        if(y != NULL && y->color == 1){
          z->parent->color = 0;
          y->color = 0; 
          z->parent->parent->color = 1;
          z = z->parent->parent;
        }
        else{
          if(z == z->parent->left){
            z=z->parent;
            rightrotate(z);
          }
          z->parent->color = 0;
          if(z->parent->parent != NULL ){
            z->parent->parent->color = 1;
            leftrotate(z->parent->parent); }
          }
        }
      }
    root->color = 0;//root always be black

  }

   void deleteNode(int testpop) {
    RBT::Node *z = NULL;
    RBT::Node *y = NULL;
    RBT::Node *x = NULL;
    int color;
    z = searchTree( testpop);//find the node
    y =z;
    if(z->left == NULL){//z has no left child, according to deletion z's parent become z's right child parent
      x = z->right;
      deleteNodeHelper(z,z->right);
    }
    else if(z->right == NULL){//z has no right child, according to deletion z's parent become z's left child parent
      x = z->left;
      deleteNodeHelper(z,z->left);
    }
    else{
      y = this->getMinimumHelper(z->right);//return subtree s most left child minumum child
      color = y->color;
      x = y->right;
      if(y!=z->right){
        deleteNodeHelper(y,y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      else{if(x != NULL){x->parent=y;}}
      if(z!=NULL){deleteNodeHelper(z,y);}
      
      y->left=z->left;//exchange y and z attribute
      y->left->parent = y;
      y->color= z->color;
    }
    if(color==0){
      if(x!=NULL){deletefixup(x);}//call fix up function for color and length arrangement
    }
    size--;//decrement size of tree
    delete z;
  }
  void deletefixup(RBT::Node *x){ // Organizes the rb tree to comply with the rules
    RBT::Node *w = NULL;
    while(x != root && x->color == 0){
      if(x==x->parent->left){
        w=x->parent->right;
        if(w->color == 1){
          w->color= 0;
          x->parent->color = 1;
          leftrotate(x->parent);
          w = x->parent->right;
        }
        if(w->left->color == 0 && w->right->color == 0){
          w->color = 1;
          x = x->parent;
        }
        else{
          if(w->right->color == 0){
            w->left->color = 0;
            w->color =1;
            rightrotate(w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color=0;
          w->right->color=0;
          leftrotate(x->parent);
          x = root;
        }
      
      }else{//symmetric if condition
        w=x->parent->left;
        if(w->color == 1){
          w->color= 0;
          x->parent->color = 1;
          rightrotate(x->parent);
          w = x->parent->left;
        }
        if(w->right->color == 0 && w->left->color == 0){
          w->color = 1;
          x = x->parent;
        }
        else{
          if(w->left->color == 0){
            w->right->color = 0;
            w->color =1;
            leftrotate(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color=0;
          w->left->color=0;
          rightrotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }
  void deleteNodeHelper(RBT::Node *x,RBT::Node *y) {//transparent
      RBT::Node* k = x;
      if(x->parent == nullptr  ){//if first element
        root =y; 
      }
      else if (x == x->parent->left){//x = y
        x->parent->left = y;
      }
      else{//if z is a right child
        x->parent->right = y;
      }
      if(y != nullptr){
        y->parent = x->parent;
      }
  }

  int getHeightHelper(RBT::Node *x){//It traverses the entire tree, starting at the reference node
    if(x==nullptr){//if given node is empty
      return 0;
    }
    else{
      int left_height = getHeightHelper(x->left);//calculate all branch recursively
      int right_height = getHeightHelper(x->right);
      if(right_height<left_height  ){
        return(left_height + 1);//return the higher value
      }
      else{return right_height+1;}

    }
  }
  int getHeight() {//sends the root as a reference to calculate the total height of the tree
    RBT::Node *x =this->root;
    int y = getHeightHelper(x);
    return y -1;//reason of minus 1 is root s height equal to zero
  }

  RBT::Node* getMaximum() {//search the rightmost child, for calculate all tree ' s maximum send to root for reference
    RBT::Node *x =this->root;
    while(x->right != NULL){
      x = x->right;
    }
    return x;
  }
  RBT::Node* getMaximumHelper(RBT::Node *x) {//search the rightmost child started reference node
    while(x->right != NULL){
      x = x->right;
    }
    return x;
  }

  RBT::Node* getMinimum() {//search the leftmost child, for calculate all tree ' s minumum send to root for reference
    RBT::Node *x =this->root;
    while(x->left != NULL){
      x = x->left;
    }
    return x;
  }
    RBT::Node* getMinimumHelper(RBT::Node *x) {//search the leftmost child started reference node
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
  int getTotalNodesHelper(RBT::Node *x) {//calculate all nodes recursively starting the reference point
    if(x == NULL){return 0;}
    else{
      int left = getTotalNodesHelper(x->left);
      int right = getTotalNodesHelper(x->right);
      return left + right + 1;
  }}
  



};