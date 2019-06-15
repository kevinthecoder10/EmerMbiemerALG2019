#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>

using namespace std;

int i = 1;
struct Node {//krijimi i struktures per pemen e balancuar, e njejte si BST
    string word;
    Node *left;
    Node *right;
    int height;//na duhet dhe nje variabel per te matur lartesine e kulmit, pasi duhet te kontrollojme vazhdimisht nese pema qendron e balancuar apo jo pas shtimit te ndonje kulmi
};
int returnmax(int x, int y) {//funksion per gjetjen e maksimumit ndermjet dy gjatesive
    if(x>y)
        return x;
    return y;
}

int height(Node *tmp) {//funksion qe na kthen gjatesine e kulmit
    if(tmp==NULL)
        return 0;
    return tmp->height;
}
bool exist(Node *root, string w) {//funksion per kerkimin e ndonje fjale, e njejte si te BST
    if(root==NULL) {
        return false;
    }
    if(root->word==w) {
        return true;
    }
    if(w>root->word) {
        return exist(root->left,w);
    } else {
        return exist(root->right,w);
    }
}
Node *rightRotate(Node *y)//kryerja e rrotullimit per te bere pemen e balancuar nese ajo nuk eshte nga e djathta
{
    Node *x = y->left;
    Node *T2 = x->right;

    //realizimi i rrotullimit
    x->right = y;
    y->left = T2;

    // riperditesim i gjatesise
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;


    return x;
}
Node *leftRotate(Node *x)//kryerja e rrotullimi per nga e majta
{
    Node *y = x->right;
    Node *T2 = y->left;

    // realizimi i rrotullimit
    y->left = x;
    x->right = T2;

    //perditesimi i gjatesise
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}
int getBalance(Node *tmp)//kthene balancen pra ndryshesen e gjatesive te nenpemes se majte me ate te djathe e cila duhet te jete ta pakten 1
{
    if (tmp == NULL)
        return 0;
    return height(tmp->left) - height(tmp->right);
}
Node *newNode(string w) {//funksion qe ben krijimin e kulmit te ri
    Node *temp = new Node;
    temp->word = w;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

Node *add(Node *root, string w) {//funksioni qe shton nje kulm te ri
    //pjesa e pare njejte si te BST
	if(root==NULL)
        return newNode(w);

    if(exist(root,w))
        return root;

    if(w<root->word) {
        root->left = add(root->left,w);
    } else {
        root->right = add(root->right,w);
    }
    root->height = 1 + max(height(root->left),height(root->right));
	//marrim balancen
    int balance = getBalance(root);
	//Majtas Majtas
    if (balance > 1 && w < root->left->word)
        return rightRotate(root);

    // Djathtas Djathtas
    if (balance < -1 && w > root->right->word)
        return leftRotate(root);

    // Majtas Djathtas
    if (balance > 1 && w > root->left->word)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Djathtas Majtas
    if (balance < -1 && w < root->right->word)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void print(Node *root)//funksioni i printimit
{
    if (root != NULL)
    {
        print(root->left);
		cout<<i<<" "<<root->word<<endl;
		i++;
        print(root->right);
    }
}

int main(int argc, char * argv[]) {
	ifstream in;
	Node* head = new Node;
	int count = 0;
	clock_t start, end;
	start = clock();
	in.open("Fjalori1000000.txt");
	while(!in.eof()){
		string str;
		in>>str;
		if(count == 0){
			head = add(NULL,str);
			count++;
		}
		else {
			head = add(head,str);
		}

	}
	in.close();
	print(head);
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout<<"Fjalori yne ka keto fjale: "<<endl;
	cout<<"Koha e ekzekutimit te programit tone eshte: "<<time_taken<<" s"<<endl;
	getchar();

	return 0;
}
