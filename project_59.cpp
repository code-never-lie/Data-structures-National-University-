
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

int lineno=1;
struct data{
	int key;
	string value;
	int line_no;
};
class Node {

data d1; 
Node *left;
Node *right;
int height;
public:
    Node(int data1,string data2, Node *left=0, Node *right=0, int height=1) {
    	{
         ofstream outfile;
         outfile.open("mcdata1.txt",ios::app);
         d1.key=data1;
         d1.line_no=lineno++;
         d1.value=data2;
       
         outfile<<d1.key<<endl;
         outfile<<d1.value<<endl;
         outfile<<d1.line_no<<endl;
         
         outfile.close();
         }
        
        Node::left = left;
        Node::right = right;
        Node::height = height;
    }

    void printdata() ;
    int getkey();
    void setkey(int key);
    

    

    Node *getLeft() const;

    void setLeft(Node *left);

    Node *getRight() const;

    void setRight(Node *right);

    int getHeight() const;

    void setHeight(int height);
    string getvalue();
    int getline_no();
};

//----------------------------------------------------------------------------


void Node::printdata()  {

		 cout<<"\n\nkey     : "<<d1.key<<endl;
         cout<<"VALUE      : "<<d1.value<<endl;
         cout<<"line no : "<<d1.line_no<<endl;}
    
         
         
    

int Node::getkey(){
        int num=d1.key;
        return num;
         
         }
string Node::getvalue(){
        string value=d1.value;
        return value;
         
         } 
int Node::getline_no(){
        int num=d1.line_no;
        return num;
         
         }		         
void Node::setkey(int key){
        d1.key=key;
        
         
         }	

Node *Node::getLeft() const {
    return left;
}

void Node::setLeft(Node *left) {
    Node::left = left;
}

Node *Node::getRight() const {
    return right;
}

void Node::setRight(Node *right) {
    Node::right = right;
}

int Node::getHeight() const {
    return height;
}

void Node::setHeight(int height) {
    Node::height = height;
}
//----------------------------------------------------------------------------
class Tree {
private:
    int Height(Node *node);
    int Max(int a, int b); 
    int getBalance(Node *node);
    Node *rightRotate(Node *node);
    Node* leftRotate(Node *node);
    Node* performBalance(int key, Node *node);
public:
    Node* Insert(data &d1, Node *node);
    void inOrder(Node *node);
    Node* Delete(int key,Node *node);
    Node* Maximum(Node *node);
    Node *Minimum(Node *node);
    void Search(int key,Node *node);
    Node *remov(Node *node1,Node *node2,Tree *t1);
    void del(int key1);

};

//------------------------------------------------------------------


int Tree::Height(Node *node) {
    if(node==NULL)
        return 0;
    return node->getHeight();
}

int Tree::Max(int a, int b) {
    return a>b ? a : b;
}

int Tree::getBalance(Node *node) {
    if(node==NULL)
        return 0;
    return Height(node->getLeft()) - Height(node->getRight());
}

Node *Tree::rightRotate(Node *node) {
    Node* left = node->getLeft();
    Node* lRight = left->getRight();
    left->setRight(node);
    node->setLeft(lRight);
    node->setHeight(Max(Height(node->getRight()),Height(node->getLeft()))+1);
    left->setHeight(Max(Height(left->getRight()),Height(left->getLeft()))+1) ;
    return left;
}

Node *Tree::leftRotate(Node *node) {
    Node* right = node->getRight();
   Node* rLeft = right->getLeft();
    right->setLeft(node);
    node->setRight(rLeft);
    node->setHeight(Max(Height(node->getRight()),Height(node->getLeft()))+1);
    right->setHeight(Max(Height(right->getRight()),Height(right->getLeft()))+1);
    return right;
}

Node *Tree::performBalance(int key, Node *node) {
   int balance = getBalance(node);

    if(balance > 1 && node->getkey() > key) // left left case
    {
        return rightRotate(node);
    }
    if (balance < -1 && node->getkey() < key) //right right case
    {
        return leftRotate(node);
    }
    if(balance > 1 && node->getkey() < key) // left right case
    {
        node->setLeft(leftRotate(node->getLeft()));
        return rightRotate(node);
    }
    if (balance < -1 && node->getkey() > key) //rotate right left
    {
        node->setRight(rightRotate(node->getRight()));
        return leftRotate(node);
    }
    return node;
}

Node *Tree::Insert(data &d1, Node *node) {
    if(node == NULL)
        return new Node(d1.key,d1.value);
    else if(d1.key > node->getkey())
        node->setRight(Insert(d1, node->getRight()));
    else if (d1.key < node->getkey())
        node->setLeft(Insert(d1, node->getLeft()));
    else
        return node;
    node->setHeight(Max(Height(node->getLeft()), Height(node->getRight())) + 1);
     
    return performBalance(d1.key, node);
}

void Tree::inOrder(Node *node) {
    if(node!=NULL)
    {
        inOrder(node->getLeft());
        cout<<"\n\n*************Record****************\n\n";
        node->printdata();
        inOrder(node->getRight());
    }
}
 Node *Tree::remov(Node *node1,Node *node2,Tree *t1) {
    if(node1!=NULL)
    {  data d2;
        inOrder(node1->getLeft());
        d2.key=node1->getkey();
        d2.line_no=node1->getline_no();
        d2.value=node1->getvalue();
        node2=t1->Insert(d2,node2);
        inOrder(node1->getRight());
    }
    return node2;
}
Node *Tree::Delete(int key1, Node *node) {
    if(node==NULL)
        return NULL;
    if(key1 > node->getkey())
        node->setRight(Delete(key1, node->getRight()));
    else if (key1 < node->getkey())
        node->setLeft( Delete(key1, node->getLeft()));
    else
    {
        if(node->getRight()==NULL and node->getLeft()==NULL)
        {
            delete node;
            return NULL;
        }
        else if(node->getLeft()==NULL)
        {
            Node * temp = node->getRight();
            delete node;
            return temp;
        }
        else if(node->getRight()==NULL)
        {
            Node * temp = node->getLeft();
            delete node;
            return temp;
        } else
        {
            int data = Maximum(node->getLeft())->getkey();
            node->setkey(data);
            node->setLeft(Delete(data,node->getLeft()));
        }
    }
    return performBalance(key1, node);
}
void Tree::del(int key1)
{
data d1;	
ifstream d;
    d.open("mcdata1.txt");
    ofstream e;
    e.open("new.txt");
    d >> d1.key;
    d >> d1.value;
    d >> d1.line_no;
    while(!d.eof())
    {
      if(d1.key!=key1)
	  {
	  	e << d1.key;
	  	e << endl;
	  	e << d1.value;
	  	e << endl;
	  	e << d1.line_no;
	  	e << endl;
		} 
   d >> d1.key;
    d >> d1.value;
    d >> d1.line_no; 
    }
    e.close();
    d.close();
    remove("mcdata1.txt");
    rename("new.txt","mcdata1.txt");	
}

Node *Tree::Maximum(Node *node) {
    while (node->getRight()!=NULL)
    {
        node = node->getRight();
    }
    return node;
}

Node *Tree::Minimum(Node *node) {
    while (node->getLeft()!=NULL)
    {
        node = node->getLeft();
    }
    return node;
}




//-------------------------------------------------------------------


class Node1
{
	int Id;
	int machno;
	Node *root;
	Node1 *Next;
public:
	int getId() const
	{
		return Id;
	}

	void setmachno(int machno)
	{
		Node1::machno = machno;
	}
	int getmachno() const
	{
		return machno;
	}

	void setId(int id)
	{
		Node1::Id = id;
	}
     Node *getroot() const
	{
		return root;
	}

	void setroot(Node *n)
	{
		root = n;
	}
	

	Node1 *getNext() const
	{
		return Next;
	}

	void setNext(Node1 *n)
	{
		Next = n;
	}
	Node1(int id,int mc)
	{
		setId(id);
		setmachno(mc);
		setNext(NULL);
		setroot(NULL);
	}
	
	
};
class Machinelist
{
	Node1 *head;
	Node1 *tail;
public:
	Machinelist() {
		head = tail = NULL;
	}
	void Add(int id,int mc)
	{
		
		Node1 *forward = head;
		Node1 *prvs = 0;
		Node1 *temp = new Node1(id,mc);

		if (head == NULL)
		{
			head = tail = temp;
		}
		else if (id < head->getId())
		{
			temp->setNext(head);
			tail->setNext(temp);
			head = temp;
		}
		else if (id > tail->getId())
		{
			tail->setNext(temp);
			temp->setNext(head);
			tail = temp;
		}
		else
		{

			while (temp->getId() < id)
			{
				prvs = forward;
				forward = forward->getNext();
			}
			prvs->setNext(temp);
		}
	}
	 	Node1 *suc(int key)
	{
	
		
		Node1 *temp= head;
		Node1 *temp1;
		while((key>temp->getId())&&(temp!=NULL))
		{
			temp=temp->getNext();
		 } 
		 if(key!=temp->getId())
		 {
		  temp1=head;	
		 }
		 else
		 { temp1=temp;}
		 return temp1;
	    
	}
	 int routing_table(int key1,int key2,int bit)
	{
		int in=0,p=0,q=key1,re=0;
		Node1 *temp2;
		in=pow(2,bit);
		for(int i=1;((i<=bit)&&(p!=key2));i++)
		{
		  int s=(key1+(pow(2,(i-1))));
			temp2=suc((s)%(in));
			p=temp2->getId();
			cout<<"We go from "<<q<<" "<<p<<endl;
			q=p;
			
		}
		if(p!=key2)
		{
		re=routing_table(p, key2, bit);
		return re;
		}
		else
		{
		  return temp2->getmachno();
		}
		
	}
	void rot_table(int key,int bit)
	{
	   int in=pow(2,bit);
	   int p=0;
		Node1 *temp2;
	for(int i=1;(i<=bit);i++)
		{
		  int s=(key+(pow(2,(i-1))));
			temp2=suc((s)%(in));
			p=temp2->getId();
			cout<<"We go from "<<key<<" "<<p<<endl;
			
			
		}
		
	}
	
   

	
};
class DHT{
public:
int ids,no,res,fla;
Machinelist m1;
Tree t1[50];
Node *n1[50];
int it=1;
	
DHT()
{cout<<"tell us how much size of identifier space you want "<<endl;
cin>>ids;
cout<<"tell us how many no of machine you want "<<endl;
cin>>no;
res=pow(2,ids);

int j=1,k=0;
for(;it<=no;it++)
{
cout<<"if you manully want to assign id to machine then enter 1"<<endl;
cout<<"if you want automatically to assign id to machine then enter 2"<<endl;
cin>>fla;	
if(fla==1)
{
	int j1;
	cout<<"enter id which you want to assign machine no "<<it<<"in a range from"<<k<<" to "<<res-1<<endl;
	cin>>j1;
	m1.Add(j1,it);
	
	
}
else if(fla==2)
{
	
	m1.Add(j,it);
	k=res/no;
	j=j+k;
}

	
}
for(int i=0;i<no;i++)
{
	n1[i]= NULL;
}
}	
	
void manu()
{
int value;	
loop:	
cout<<"enter 1 if you want to insert data in machine"<<endl;	
cout<<"enter 2 if you want to remove data in machine"<<endl;
cout<<"enter 3 if you want to print routing table of machine"<<endl;
cout<<"enter 4 if you want to print avl tree"<<endl;	
cout<<"enter 5 if you want to remove machine"<<endl;
cout<<"enter 6 if you want to add new machine"<<endl;
cout<<"enter 7 if you want to exit"<<endl;	
cin>>value;
if(value==1)
{
   int k1,k2,b1,a1;
   
   data d1;
   Node1 *root;
   cout<<"tell us from which machine you want to enter data"<<endl;
   cin>>k1;
   cout<<"tell us in which machine you want to enter data"<<endl;
   cin>>k2;
   cout<<"tell us how many bit of your identifer space"<<endl;
   cin>>b1;
   int mce=m1.routing_table(k1,k2,b1);
   
   cout<<"enter the key and value which you want to insert"<<endl;
   cin>>d1.key;
   cin>>d1.value;
   int a=mce-1;

   n1[a]=t1[a].Insert(d1,n1[a]);  
   	
	
	goto loop;
	
}	
else if(value==2)	
{
 int k1,k2,b1,a1;
   
   int key1;
   Node1 *root;
   cout<<"tell us from which machine you want to delete data"<<endl;
   cin>>k1;
   cout<<"tell us in which machine you want to delete data"<<endl;
   cin>>k2;
   cout<<"tell us how many bit of your identifer space"<<endl;
   cin>>b1;
   int mce=m1.routing_table(k1,k2,b1);
   
   cout<<"enter the key which you want to delete"<<endl;
   cin>>key1;
   
   int a=mce-1;
   n1[a]=t1[a].Delete(key1,n1[a]); 
   t1[a].del(key1); 
   	
	
	goto loop; 	
	
	
	
}	
else if(value==3)	
{
    int key1,bit;
   cout<<"enter the machine id which fingertable you want to print"<<endl;
   cin>>key1;
   cout<<"tell us how many bit of your identifer space"<<endl;
   cin>>bit;
     m1.rot_table(key1,bit);
     
   	
	
	goto loop; 	
	
	
	
}	
else if(value==4)	
{
 
   int key1,b1;
   cout<<"enter the machine key  which  avl you want to print "<<endl;
   cin>>key1;
   cout<<"tell us how many bit of your identifer space"<<endl;
   cin>>b1;
   int mce=m1.routing_table(1,key1,b1);
   int a=mce-1;
   t1[a].inOrder(n1[a]);  
   	
	
	goto loop; 	
	
	
	
}	
else if(value==5)	
{
 
   int key1,b1;
   cout<<"enter the machine key  which you want to delete "<<endl;
   cin>>key1;
   cout<<"tell us how many bit of your identifer space"<<endl;
   cin>>b1;
   int mce=m1.routing_table(1,key1,b1);
   int a=mce-1;
   Tree *t2=&t1[mce];
   n1[mce]=t1[a].remov(n1[a],n1[mce],t2);
   	
   	n1[a]=NULL;
	
	goto loop; 	
	
	
	
}
else if(value==6)	
{
 
   int key1,b1;
   cout<<"enter the machine key  which you want to add  "<<endl;
   cin>>key1;
   cout<<"tell us how many bit of your identifer space"<<endl;
   cin>>b1;
   cout<<it<<endl;
   m1.Add(key1,it);
   
	
	n1[it-1]=NULL;
	it++;
	goto loop; 	
	
	
	
}			
else if(value==7)	
{
 
  
   cout<<"Thankz you are now leaving "<<endl;
   
	
	
	
	
	
}	
	
}	
	
	
	
	
};
int main()
{

	DHT d1;
	d1.manu();
	
}

