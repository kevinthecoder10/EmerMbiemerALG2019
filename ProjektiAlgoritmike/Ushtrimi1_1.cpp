#include <conio.h>
#include <iostream>
#include <fstream>
#include <time.h>


using namespace std;

struct Node{//fillimisht ndertojme strukturen e nyjes
	string word;//ajo do te mbaje nje fjale
	Node* next;//dhe nje shenjues per elementin pasardhes
};
bool exist(Node* head, string w){//funksioni ne fjale ben kerkimin nese nje fjale gjendet ne liste apo jo
	Node* tmp = head;//shenojme ne koken e listes
	while(tmp != NULL){//iteracioni ben bredhjen ne liste gjersa ajo eshte e ndryshme nga null
		if(tmp->word == w){//nese gjendet fjala e marre si parameter kthen true
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}
Node* add(Node* head, string w) {//funksion per te shtuar ne liste
	if(exist(head,w)){//nese elementi ekziston 
		return head;//kthejme listen
	}
	else{//ne te kundert bejme shtimin e saj perpara
		Node* tmp = new Node;//krijojme nyjen e re
		tmp->word = w;//fjala qe do mbaje eshte fjala qe merret si parameter
		tmp->next = head;//pasardhesi eshte koka
		head = tmp;//koke bejme nyjen e saposhtuar
		return head;
	}
}
void print(Node* head){//funksioni i printimit i cili ka nje logjike te thjeshte
	Node* tmp = head;//shenojme ne krye
	int i = 1;//variabel per rankimin e fjaleve
	while(tmp != NULL){//derisa ky iteracion te perfundoje do te printojme te gjithe elementet e listes
		cout<<i<<" "<<tmp->word<<endl;
		tmp = tmp->next;
		i++;
	}
}


int main(int argc, char * argv[]) {
	ifstream in;
	clock_t start,end;
	Node* head = new Node;
	int count = 0;// counti na sherben per te specifikuar nese lista eshte bosh
	start = clock();
	in.open("Fjalori1000000.txt");//behet hapja e skedarit
	while(!in.eof()){
		string str;
		in>>str;
		//cout<<str<<endl;
		if(count == 0){
			head->word = str;
			head->next = NULL;
			count++;//tashme rrisim countin kemi futur nje fjale dhe lista seshte bosh
		}
		else {
			head = add(head,str);
		}

	}
	print(head);
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout<<"Fjalori yne ka keto fjale: "<<endl;
	cout<<"Koha e ekzekutimit eshte :"<<time_taken<<" s"<<endl;
	getchar();

	return 0;
}
