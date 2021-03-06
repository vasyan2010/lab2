#include  <stdio.h>
#include  <windows.h>
#include  <conio.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  <string.h>
#include  <iostream>
using namespace std;

bool RED=true;
bool BLACK=false;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int redColor=4;
const int blackColor=1;
const int normalColor=10;

template <typename T>
class RB_Tree{   
	private:
		struct node
		{
			int key;   		
			T value;		
			bool color;		
			node *lft;		
			node *rht;	
			node *parent;		
		};
		node *head; 	
		
		void printNode(node *n,int depth)
		{
		   if (n!=NULL)
		   {
		      	printNode(n->rht, depth+5);
		     	for (int i = 0; i < depth; i++) 
		         	printf(" ");
		    	(n->color==RED)?SetConsoleTextAttribute(hConsole, redColor):SetConsoleTextAttribute(hConsole, blackColor);
		      	printf("%d\n", n->key);
		      	printNode(n->lft, depth+5);
		   }
		}
		
		void printKeys(node *n)
		{
		   if (n!=NULL)
		   {
		      	printKeys(n->rht);
		      	printf("   %d\n", n->key);
		      	printKeys(n->lft);
		   }
		}
		void printValues(node *n)
		{
		   if (n!=NULL)
		   {
		      	printValues(n->rht);
		      	cout<<"   "<<n->value<<endl;
		      	printValues(n->lft);
		   }
		}
		void clearNodes(node *n)
		{
			if (n!=NULL)
		  	{
		      	clearNodes(n->rht);
		      	clearNodes(n->lft);
		      	delete n;
		   }
		}

		bool getColor(node * n)
		{
			if(n!=NULL)
			{
				if(n->color == RED)
					return RED;
			}
			return BLACK;	
		}
	public:
		RB_Tree()			
		{ 
			head=NULL;
		};
		~RB_Tree(){};

		node *grandparent(node *n)  
		{
			if ((n != NULL) && (n->parent != NULL))
				return n->parent->parent;
			else
				return NULL;
		}

		node *uncle(node *n)  		
		{
			node *g = grandparent(n);  
			if (g == NULL)
				return NULL; 		
				
			if (n->parent == g->lft)  
				return g->rht;
			else						
				return g->lft;
		}
	
		node *brother(node *n)
		{
			if (n == n->parent->lft)
				return n->parent->rht;
			else
				return n->parent->lft;
		}
		
		void rotate_left(node *n)
		{
		    node *p = n->rht;
				
			p->parent = n->parent; 	
			if (n->parent != NULL)
			{
		        if (n->parent->lft==n)
		            n->parent->lft = p;
		        else
		            n->parent->rht = p;
		    }	
			else 
				head=p;
				
		    n->rht = p->lft;
		    if (p->lft != NULL)
		        p->lft->parent = n;
			
		    n->parent = p;
		    p->lft = n;
		}
	
		void rotate_right(node *n)
		{
		    node *p = n->lft;
			
		    p->parent = n->parent;
		    if (n->parent != NULL) 
			{
		        if (n->parent->lft==n)
		            n->parent->lft = p;
		        else
		           	n->parent->rht = p;
		   }		
			else 
				head=p;
				
		    n->lft = p->rht;
		    if (p->rht != NULL)
		        p->rht->parent = n;
			
		    n->parent = p;
		    p->rht = n;
		}
		
		void checkNode(node *n)
		{
			cout<<"==========================\n";
			cout<<"\tkey "<<n->key<<"\n";
			cout<<"\tvalue "<<n->value<<"\n";
			cout<<"\tcolor ";
		 	(getColor(n)==RED)?cout<<"RED\n":cout<<"BLACK\n";
			cout<<"\tlft ";
			(n->lft==NULL)?cout<<"NULL\n":cout<<"found\n";
			cout<<"\trht ";
			(n->rht==NULL)?cout<<"NULL\n":cout<<"found\n";
			cout<<"\tparent ";
			(n->parent==NULL)?cout<<"NULL\n":cout<<"found\n";
			(n==head)?cout<<"\troot\n":cout<<"\tnot root\n";
			cout<<"==========================\n";
		}
		
		void printTree()
		{
			SetConsoleTextAttribute(hConsole, blackColor);
			printNode(head, 0);
			SetConsoleTextAttribute(hConsole, normalColor);
		}
		
		void insert_case1(node *n)
		{
			if (n->parent == NULL)
				n->color = BLACK;
			else
				insert_case2(n);
		}
		
		
		void insert_case2(node *n)
		{
			if (getColor(n->parent)!= BLACK)
				insert_case3(n);
		}
		
		void insert_case3(node *n)
		{
			node *uncle_n = uncle(n);
			node *grandparent_n=grandparent(n);
		
			if (getColor(uncle_n)) 
			{
				n->parent->color = BLACK;
				uncle_n->color = BLACK;
				grandparent_n->color = RED;
				insert_case1(grandparent_n);
			} 
			else 
			{
				insert_case4(n);
			}
		}
		
		
		void insert_case4(node *n)
		{
			node *grandparent_n = grandparent(n);
		
			if ((n == n->parent->rht) && (n->parent == grandparent_n->lft)) {
				rotate_left(n->parent);
			n = n->lft;
			} 
			else 
				if ((n == n->parent->lft) && (n->parent == grandparent_n->rht)) {
					rotate_right(n->parent);
				n = n->rht;
			}
			insert_case5(n);
		}
		
		
		void insert_case5(node *n)
		{
			node *grandparent_n = grandparent(n);
		
			n->parent->color = BLACK;
			grandparent_n->color = RED;
			if ((n == n->parent->lft) && (n->parent == grandparent_n->lft))
			{
				rotate_right(grandparent_n);
			} 
			else 
			{ 
				rotate_left(grandparent_n);
			}
		}
		/* 1 */
		void insert(int addKey,T addValue)
		{
			cout<<"Add item with key "<<addKey<<" and value "<<addValue<<" into a tree\n";
			
			node *addingNode;   
			addingNode = new node;
			addingNode->key=addKey;
			addingNode->value=addValue;
			addingNode->color=RED;
			addingNode->lft=NULL;
			addingNode->rht=NULL;
			addingNode->parent=NULL;
		
			if (head!=NULL)
			{
				node *searchPlace = head;
				while (searchPlace!=NULL)
				{
					if (addKey<searchPlace->key) 
					{
						if (searchPlace->lft==NULL)
						{
							addingNode->parent=searchPlace;
							searchPlace->lft=addingNode;
							break;
						}

							
						searchPlace=searchPlace->lft;		
					}					
					else
					{
						if (searchPlace->rht==NULL)	
						{
							addingNode->parent=searchPlace;
							searchPlace->rht=addingNode;
							break;
						}
							
						searchPlace=searchPlace->rht;
					}
				}
			}
			else 
				head=addingNode;
			//������������
			insert_case1(addingNode);
		}
		/* 5 */
		void get_keys()
		{
			cout<<"=== Keys ==="<<endl;
			printKeys(head);
			cout<<"============"<<endl;
		}
		/* 6 */
		void get_values()
		{
			cout<<"=== Values ==="<<endl;
			printValues(head);
			cout<<"=============="<<endl;
		}
		/* 3 */
		void find (int findKey)
		{
			cout<<"search node by key "<<findKey<<endl;
			if (head!=NULL)
			{
				node *searchNode = head;
				while (searchNode!=NULL)
				{
					if (findKey<searchNode->key) 
						searchNode=searchNode->lft;			
					else
						if (findKey>searchNode->key) 
							searchNode=searchNode->rht;
						else
							break;
				}
				if	(searchNode!=NULL)
					checkNode(searchNode);
				else
					cout<<"Item not found\n";
			}
			else 
				cout<<"Tree is empty\n";
		}
		
		/* 4 */
		void clear()
		{
			cout<<"Clearing the list"<<endl;
			clearNodes(head);
			head=NULL;
		}
		
		void delete_case1(node *n)
		{
			if (n->parent!= NULL)
				delete_case2(n);
		}
		
		void delete_case2(node *n)
		{
			node *brother_n = brother(n);
			if (getColor(brother_n) == RED) 
			{
				n->parent->color = RED;
				brother_n->color = BLACK;
				if (n == n->parent->lft)
					rotate_left(n->parent);
				else
					rotate_right(n->parent);
			} 
			delete_case3(n);
		}
		
		void delete_case3(node *n)
		{	
			node *brother_n = brother(n);
		
			if ((getColor(n->parent) == BLACK) &&
				(getColor(brother_n) == BLACK) &&
			    (getColor(brother_n->lft) == BLACK) &&
			    (getColor(brother_n->rht) == BLACK)) 
			{
				brother_n->color = RED;
				delete_case1(n->parent);
			} 
			else
				delete_case4(n);
		}
		
		void delete_case4(node *n)
		{
			node *brother_n = brother(n);
		
			if ((getColor(n->parent) == RED) &&
			    (getColor(brother_n) == BLACK) &&
			    (getColor(brother_n->lft) == BLACK) &&
			    (getColor(brother_n->rht) == BLACK)) {
				brother_n->color = RED;
				n->parent->color = BLACK;
			} else
				delete_case5(n);
		}
		
		void delete_case5(node *n)
		{	
			node *brother_n = brother(n);
		
			if  (getColor(brother_n) == BLACK) 
			{ 
				if ((n == n->parent->lft) && 
				    (getColor(brother_n->rht) == BLACK) &&
				    (getColor(brother_n->lft) == RED)) 
				{ 
					brother_n->color = RED;
					brother_n->lft->color = BLACK;
					rotate_right(brother_n);
				} else if ((n == n->parent->rht) &&
				           (getColor(brother_n->lft) == BLACK) &&
				           (getColor(brother_n->rht) == RED)) 
							{
					brother_n->color = RED;
					brother_n->rht->color = BLACK;
					rotate_left(brother_n);
				}
			}
			delete_case6(n);
		}
		
		void delete_case6(node *n)
		{
			node *brother_n = brother(n);
		
			brother_n->color = n->parent->color;
		    n->parent->color = BLACK;
		
			if (n == n->parent->lft) {
		        brother_n->rht->color = BLACK;
				rotate_left(n->parent);
			} else {
				brother_n->lft->color = BLACK;
				rotate_right(n->parent);
			}
		}
		
		/* 2 */
		void remove(int deleteKey)
		{
			cout<<"Deleting an item with a key "<<deleteKey<<endl;
			node *deletingNode=head;
			while (deletingNode->key!=deleteKey)
			{
				if (deleteKey<deletingNode->key) 
					deletingNode=deletingNode->lft;			
				else
					deletingNode=deletingNode->rht;
			}
			if ((deletingNode->rht!=NULL)&&(deletingNode->lft!=NULL)) 
			{
				node *tmpNode=deletingNode->rht; 
				while (tmpNode->lft!=NULL) 
						tmpNode=tmpNode->lft;					
				deletingNode->key=tmpNode->key;	
				deletingNode->value=tmpNode->value;
				deletingNode=tmpNode;
			}
			
			node *child = deletingNode->rht;
			if (child!=NULL)
			{
				child->parent=deletingNode->parent;
				if(child->parent!=NULL)
					child->parent->lft=child;
					
				if (getColor(deletingNode) == BLACK) 
				{	
					if (getColor(child) == RED)
						child->color = BLACK;
					else
						delete_case1(child);
				}
			
			}
			else
				delete_case1(deletingNode);
				
		
			if (deletingNode == deletingNode->parent->lft)
				deletingNode->parent->lft=NULL;
			if (deletingNode == deletingNode->parent->rht)
				deletingNode->parent->rht=NULL; 
			
			delete deletingNode;
		}
};


int menu()
{
	int Choice;
	cout<<"\t=== Menu ==="<<endl;
	cout<<"1. Adding a new item."<<endl;
	cout<<"2. Delete item."<<endl;
	cout<<"3. Tree output to screen."<<endl;
	cout<<"4. Tree cleaning."<<endl;
	cout<<"5. List keys."<<endl;
	cout<<"6. List Stored Values."<<endl;
	cout<<"7. Find item by key."<<endl;
	cout<<"8. Pattern Tree �1."<<endl;
	cout<<"9. Pattern Tree �2."<<endl;
	cout<<"\n0. Exit."<<endl;
	cin>>Choice;
	return Choice;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleTextAttribute(hConsole, normalColor);
	
	RB_Tree<int> intTree;
	
	int menuChoice;
	int enteredKey;
	int enteredValue;
	bool flagToEnd=0;
    do{
        menuChoice=menu();
        switch (menuChoice)
        {
        case 1:
            {
            	cout<<"Enter key"<<endl;
            	cin>>enteredKey;
            	cout<<"Enter value"<<endl;
            	cin>>enteredValue;
                intTree.insert(enteredKey, enteredValue);
                break;
            }
        case 2:
            {
            	cout<<"Enter key"<<endl;
            	cin>>enteredKey;
                intTree.remove(enteredKey); 
                break;
            }
        case 3:
            {
                intTree.printTree();
                break;
            }
        case 4:
            {
                intTree.clear();
                break;
            }
        case 5:
            {
                intTree.get_keys();
                break;
            }
        case 6:
            {
                intTree.get_values();
                break;
            }
        case 7:
            {
            	cout<<"Enter key"<<endl;
            	cin>>enteredKey;
                intTree.find(enteredKey);
                break;
            }
        case 8:
            {
                intTree.clear();
                intTree.insert(3,83);
    			intTree.insert(2,82);
    			intTree.insert(1,81);
    			intTree.insert(0,80);
                break;
            }
        case 9:
            {
            	intTree.clear();
                intTree.insert(0,90);
			    intTree.insert(1,91); 
			    intTree.insert(2,92); 
			    intTree.insert(3,93); 
			    intTree.insert(4,94); 
			    intTree.insert(5,95); 
			    intTree.insert(6,96); 
			    intTree.insert(7,97); 
			    intTree.insert(8,98); 
			    intTree.insert(9,99);
                break;
            }
        case 0:
            {
                flagToEnd=1;
                break;
            }
        }
        }while(flagToEnd==0);
	
	return 0;
}

