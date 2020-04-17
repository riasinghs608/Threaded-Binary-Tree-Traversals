#include<iostream>
#include<string.h>
using namespace std;

class tnode
{
	public:
	int data;
	int lthread,rthread;
	tnode *left,*right;
};

class tree:public tnode
{
	public:
		tnode *root,*head;
		tree()
		{
			root=NULL;
			head=new tnode();
			head->lthread=head->rthread=0;
			head->left=head->right=NULL;
		}
		void create();
		void inorder();	
		void preorder();
		void postorder();	
		tnode* search(tnode *temp);
};

void tree::create()
{
	tnode *temp,*newnode;
	int n,flag;
	char ch='y',c;
	
	while(ch=='y'||ch=='Y')
	{
		cout<<"\nEnter data to be inserted: ";
		cin>>n;
		
		newnode=new tnode();
		newnode->data=n;
		newnode->lthread=newnode->rthread=0;
		newnode->left=newnode->right=NULL;
		
		flag=1;
		if(root==NULL)
		{
			root=newnode;
			root->left=root->right=head;
		}
		
		else
		{
			temp=root;
			while(flag==1)
			{
				if(n<temp->data)
				{
					if(temp->lthread==0)
					{
						newnode->lthread=newnode->rthread=0;
						newnode->left=temp->left;
						newnode->right=temp;
						temp->left=newnode;
						temp->lthread=1;
						flag=0;
					}
					else
					{
						temp=temp->left;
						flag=1;
					}
					
				}
				
				else
				{
					if(temp->rthread==0)
					{
						newnode->lthread=newnode->rthread=0;
						newnode->right=temp->right;
						newnode->left=temp;
						temp->right=newnode;
						temp->rthread=1;
						flag=0;
					}
					else
					{
						temp=temp->right;
						flag=1;
					}
				}
				
			}	
		}
		cout<<"Add more nodes(Y/N): ";
		cin>>ch;
	}
}

void tree::preorder()
{
	tnode *temp=root;
	cout<<"\nPREORDER TRAVERSAL";
	
	while(temp!=head)
	{
		while(temp->lthread==1)
		{
			cout<<" "<<temp->data;
			temp=temp->left;
		}
		
		if(temp->lthread==0 && temp->rthread==0)
		{
			cout<<" "<<temp->data;
		}
			
		while(temp->rthread==0 && temp!=head)
		{
			temp=temp->right;
			
		}
		
		if(temp==head)
			return;
		
		temp=temp->right;
		if(temp->lthread==1 || temp->rthread==1)
		{
			cout<<" "<<temp->data;
		}	
	}
}

void tree::postorder()
{
	tnode *temp=root;
	tnode *parent;
	int nextaction=1;
	int count=0,count1=0;
	while(1)
	{
		switch(nextaction)
		{
			case 1:
				while(temp->lthread==1)
					temp=temp->left;
				cout<<" "<<temp->data;
				temp=temp->right;
				parent=temp->right;
				nextaction=2;
				break;
			
			case 2:
				while(temp->rthread==1)
					temp=temp->right;				
				cout<<" "<<temp->data;
				temp=temp->left;				
				parent=temp->left;
				nextaction=3;
				break;
			
			case 3:
				cout<<" "<<temp->data;
				parent=search(temp);
				//cout<<"parent data: "<<parent->data;
				if(parent->data==root->data)
					count=count+1;
					
				if(parent->data==root->data && count==2)
				{
					cout<<" "<<parent->data;
					return;
				}
				//cout<<"1. temp->data:"<<temp->data;
				if(temp->data==root->left->data && count==1)
				{
					temp=parent;
					nextaction=4;	
					count1++;
				}
				
				if(count1==1 && parent->data!=root->data)
				{
					temp=parent;
					count1=0;
					nextaction=3;
				}
				
				if(temp->data==parent->left->data)
				{
					temp=parent;
					nextaction=2;	
					count1++;			
				}
				
				if(temp->data==root->left->data && count==1)
				{
					temp=parent;
					nextaction=4;	
					count1++;
				}
					
				else if(temp->data==parent->right->data)
				{
					temp=parent;
					nextaction=1;
					count1++;
				}
				//cout<<"count: "<<count;
				//cout<<"count1: "<<count1;
				break;
				
			case 4:
				if(temp->data==root->data)
					temp=temp->right;
				while(temp->lthread==1)
					temp=temp->left;				
				cout<<" "<<temp->data;
				temp=temp->right;				
				nextaction=2;
				break;
		}
	}
}

tnode* tree::search(tnode *temp)
{
	tnode *temp1=root;
	while(temp1!=head)
	{
		if(temp1->left->data==temp->data || temp1->right->data==temp->data)
		{
			//cout<<" temp1->data: "<<temp1->left->data;
			//cout<<" temp1->data1: "<<temp1->right->data;
			return temp1;
			break;
		}
		
		else if(temp->data<temp1->data)
		{
			//cout<<" search 1 ";
			temp1=temp1->left;
		}
		else if(temp->data>temp->data)
		{
			//cout<<" search 2 ";
			temp1=temp1->right;
		}
		
		
	}
}


void tree::inorder()
{
	tnode *temp=root;
	cout<<"\nINORDER TRAVERSAL";
	
	while(temp!=head)
	{
		while(temp->lthread==1)
			temp=temp->left;
		cout<<" "<<temp->data;
		
		while(temp->rthread==0 && temp!=head)
		{
			temp=temp->right;
			if(temp->data!=head->data)
			{
				cout<<" "<<temp->data;
			}
		}
		
		if(temp==head)
			return;
		
		temp=temp->right;
		
	}
}

int main()
{
	int c,n;
	char ch='y';
	tree t;
	while(ch!='n'||ch!='N')
	{
		cout<<"Enter \n 1.CREATION OF TREE \n 2.INORDER TRAVERSAL \n 3.PREORDER TRAVERSAL \n 4.POSTORDER TRAVERSAL ";
		cin>>c;
		switch(c)
		{
			case 1:
				t.create();
				break;
			
			case 2:
				t.inorder();
				break;	
			
			case 3: 
				t.preorder();
				break;
			
			case 4: 
				t.postorder();
				break;

		}
		cout<<"\nDo you want to continue(Y/N): ";
		cin>>ch;
	}
	return 0;
}
