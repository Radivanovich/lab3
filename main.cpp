#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node
{
    int value;
    Node*left,*right;
};

class Tree
{
    private:
        Node *root;
        void copy_tree(Node *&root_new, Node *root_old);
        void del_tree(Node *wer);
        void push(Node *&wer,int data);
        void show_left(Node *wer);
        void show_right(Node *wer);
        Node *check(Node *wer,int key);
    public:
        Tree();
        Tree(int t);
        Tree (const Tree &ob);
        ~Tree();
        void push(int data);
        void show_left();
        void show_right();
        Node *check(int key);
        bool is_empty();
        Tree& operator = (const Tree &ob);
};

Tree& Tree::operator = (const Tree &ob)
{
    if(this==&ob)
        return *this;
    del_tree(root);
    copy_tree(root,ob.root);
    return *this;
}

Tree::Tree (const Tree &ob)
{
    if (ob.root==0)
        root=0;
    else
    {
        root=new Node;
        root->value = ob.root->value;
        root->left = 0;
        root->right = 0;
        copy_tree(root, ob.root);
    }
}

void Tree::copy_tree(Node *&root_new, Node *root_old)
{
    if (root_old->left!=0)
    {
        push(root_new, (root_old->left)->value);
        copy_tree(root_new, root_old->left);
    }
    if (root_old->right!=0)
    {
        push(root_new, (root_old->right)->value);
        copy_tree(root_new, root_old->right);
    }
}
Node * Tree::check(int key)
{
    if(root==0)
        return 0;
    else
    {
        if(key<root->value)

            return check(root->left,key);
        else
        {
            if(key>root->value)
                return check(root->right,key);
            else
                return root;
        }
    }
}

Node * Tree::check(Node *wer,int key)
{
    if(wer==0)
        return 0;
    else
        if(key<wer->value)
            return check(wer->left,key);
        else
            if(key>wer->value)
                return check(wer->right,key);
            else
                return wer;
}

Tree::Tree(int t)
{
    root=0;
    for(int i=0; i<t; i++)
    {
        int k=rand()%100;
        if(check(root,k)==0)
            push(root,k);
        else
            t++;
    }
}

Tree::Tree()
{
    root=0;
}

Tree::~Tree()
{
    del_tree(root);
}

void Tree::del_tree(Node *wer)
{
    if(wer==0)
        return;
    else
        if((wer->left==0)&&(wer->right==0))
        {
            if(wer->left!=0)
                del_tree(wer->left);
            if(wer->right!=0)
                del_tree(wer->right);
            delete wer;
        }
}
void Tree::push(Node *&wer,int data)
{
    if(wer==0)
    {
        wer=new Node;
        wer->value=data;
        wer->left=0;
        wer->right=0;
    }
    else
    {
        if(data<wer->value)
            push(wer->left,data);
        else
            if(data>wer->value)
                push(wer->right,data);
    }
}

void Tree::push(int data)
{
    if(root==0)
    {
        root=new Node;
        root->value=data;
        root->left=0;
        root->right=0;
    }
    else
    {
        if(data<root->value)
            push(root->left,data);
        else
            if(data>root->value)
                push(root->right,data);
    }
}

void Tree::show_left()
{
    if(root!=0)
    {
        show_left(root->left);
        cout<<root->value<<" ";
        show_left(root->right);
    }
}

void Tree::show_left(Node *root)
{
    if(root!=0)
    {
        show_left(root->left);
        cout<<root->value<<" ";
        show_left(root->right);
    }
}

void Tree::show_right(Node *root)
{
    if(root!=0)
    {
        show_right(root->right);
        cout<<root->value<<" ";
        show_right(root->left);
    }
}

void Tree::show_right()
{
    if(root!=0)
    {
        show_right(root->right);
        cout<<root->value<<" ";
        show_right(root->left);
    }
}

bool Tree::is_empty()
{
    if(root==0)
        return true;
    else
        return false;
}

int main()
{
    int w=0,kol_vo,choice;
    Tree tr;
    cout<<"Input a size of sequence: ";
    cin>>kol_vo;
    cout<<"Manual input(1) or random(any value)?"<<endl;
    cin>>choice;
    int data;
    if (choice==1)
    {
        for(int i=0; i<kol_vo; ++i)
        {
            cout<<"Enter value ";
            cin>>data;
            if(tr.check(data)!=0)
                cout<<"value already in sequence"<<endl;
            else
                tr.push(data);
        }
    }
    else
    {
        for(int i=0; i<kol_vo; i++)
        {
            int data=rand()%100;
            if(tr.check(data)==0)
                tr.push(data);
            else
                kol_vo++;
        }
    }
    do
    {
        cout<<"select the required operation:"<<endl;
        cout<<" 1 - show sequence by left"<<endl;
        cout<<" 2 - show sequence by right"<<endl;
        cout<<" 3 - is in sequence"<<endl;
        cout<<" 4 - exit"<<endl<<endl;
        cin>>w;
        switch(w)
        {
        case 1:
            if(tr.is_empty()==true)
                cout<<"Sequence empty";
            else
            {
                tr.show_left();
            }
            cout<<endl<<endl;
            break;
        case 2:
            if(tr.is_empty()==true)
                cout<<"Sequence empty";
            else
            {
                tr.show_right();
            }
            cout<<endl<<endl;
            break;
        case 3:
        {
            if(tr.is_empty()==true)
                cout<<"Sequence empty";
            else
            {
                Node *u;
                int key;
                cout<<"enter value to check: ";
                cin>>key;
                if((u=tr.check(key))!=0)
                {
                    cout<<"Founded"<<endl<<endl;
                }
                else cout<<"Nothing";
            }
            break;
        }
        case 4:
            break;
        }
    }
    while(w!=4);
}
