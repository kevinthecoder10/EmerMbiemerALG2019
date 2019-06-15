#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

int index = 1;
struct Node {//krijome strukturen per nyjen
    string word;//do te mbaj nje fjale
    Node *left;//shenjues per majtas
    Node *right;//shenjues per birin e djathte
};

bool exist(Node *root, string newW) {
    if(root==NULL) {//kushti nese pema eshte bosh
        return false;
    }
    if(root->word==newW) {//kerkojme fillimisht nese fjala ndodhet ne rrenjen e pemes
        return true;
    }
    if(newW<root->word) {//kusht i cili kontrollon nese fjala eshte ne rend me te ulet alfabetik
        return exist(root->left,newW);//therritje e metodes rekrusive
    } else {
        return exist(root->right,newW);//ne rast se fjala eshte ne rend alfabetik me te madh
    }
}
Node *newNode(string w) {//funksion i cili ben krijimin e nje kulmi te ri
    Node *temp = new Node;
    temp->word = w;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Node *add(Node *root, string w) {//funksion per shtimin e kulmit te ri
    if(root==NULL)//rasti nese pema eshte bosh
        return newNode(w);

    if(exist(root,w))//therrasim funskion exist, nese fjala ekziston
        return root;//kthejme pemen

    if(w<root->word) {//nese fjala eshte ne rend alfabetik me te ulet se rrenja
        root->left = add(root->left,w);//e shtojme ne te majte nepermjet therritjes se metodes rekursive
    } else {
        root->right = add(root->right,w);//nese fjala eshte ne rend alfabetik me te madh
    }
    return root;
}
void print(Node *root)//printimi i pemes i cili behet sipas menyres nenpeme e majte, rrenje, nenpeme e djathte
{
    if (root != NULL)
    {
        print(root->left);
		cout<<index<<" "<<root->word<<endl;
		index++;
        print(root->right);
    }
}
int main(int argc, char * argv[]) {
	ifstream in;
	clock_t start, end;
	Node* head = new Node;
	int c = 0;
	in.open("Fjalori1000.txt");
	start = clock();
	while(!in.eof()){
		string str;
		in>>str;
		if(c == 0){
			head->word = str;
			head->left = NULL;
			head->right = NULL;
			c++;
		}
		else {
			head = add(head,str);
		}

	}
	print(head);
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout<<"Fjalori yne ka keto fjale: "<<endl;
	cout<<"Koha e ekzekutimit eshte "<<time_taken<<" s"<<endl;
	getchar();

	return 0;
}

