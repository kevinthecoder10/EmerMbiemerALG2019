 #include <iostream>
 #include <string>
 #include <fstream>
 #define MAX_SIZE 9
 using namespace std;

 struct element
 {
 string fjale;
 struct element *next;
 };

 struct element *tabele[MAX_SIZE]= {NULL};

 void shtoNeTabHash(string);
 int HASH(string);
 bool gjendet(string);
 bool gjendetNeListe(string,element *);
 void afishoListe(element *l);
 void afishoTabeleHash();




 int main()
{

ifstream inData;



 string str;

 inData.open("Fjalori1000000.txt");

 while(inData>>str)
 {


 if(str.at(0)=='.'||str.at(0)==',')
 str=str.substr(1,str.length());

 else

 if(str.at(str.length()-1)=='.'||str.at(str.length()-1)==',')
 str=str.substr(0,str.length()-1);

 if(!gjendet(str))
 {

 shtoNeTabHash(str);

 }



 }




 inData.close();


 afishoTabeleHash();

 return 0;
 }




 int HASH(string fjala)
 {

 int gjatesi=fjala.length();
 int shuma=0;
 for(int i=0; i<gjatesi; i++)
 shuma=shuma+(int)fjala.at(i);

 return shuma%MAX_SIZE;
 }

 void shtoNeTabHash(string fjala)
 {

 int poz=HASH(fjala);


 element *tmp=new element;
 tmp->fjale=fjala;
 tmp->next=tabele[poz];
 tabele[poz]=tmp;

 }
 bool gjendet(string fjala)
 {

 int poz=HASH(fjala);

 return gjendetNeListe(fjala,tabele[poz]);

 }

 bool gjendetNeListe(string fjala,element *l)
 {

 while(l)
 {
 if(l->fjale==fjala)
 return true;
 l=l->next;
 }
 return false;
 }

 void afishoListe(element *l)
 {

 while(l)
 {

 cout<<l->fjale<<endl;
 l=l->next;
 }
 }
 void afishoTabeleHash()
 {

 for(int i=0; i<MAX_SIZE; i++)
 {
 cout<<"liste "<<i+1<<" *****************************"<<endl;

 afishoListe(tabele[i]);
 }
}

