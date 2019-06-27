#include <iostream>
#include <queue>
#include <webCrawlerC++/curl.h>
#include <fstream>
#include <vector>
using namespace std;



std::string data; //will hold the url's contents
 size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
 {
 //callback must have this declaration
 //buf is a pointer to the data that curl has for us
 //size*nmemb is the size of the buffer
 for (int c = 0; c<size*nmemb; c++)
 {
 data.push_back(buf[c]);
 }
 return size*nmemb; //tell curl how many bytes we handled
 }

 ofstream outUrl("Fjalor.txt");//skedari qe do te mbaje linqet

 queue<string> linqet;//radha qe do merret me procesimin e linqeve

 vector<string> templink;//vektori per krahasime se mos kemi perseritje

 int Nivele=2;
 int numriLinqevePerNivel=0;

 void procesolink(string);
 bool trajtuar(string str);

int main()
 {
 string s;
 int niveliim;

 cout<<"Jep linkun:"<<endl;

 cin>>s;
 cout<<"Jep nivelin e thellesise"<<endl;
 cin>>niveliim;
 s="http://"+s+"/";//kthehet linku ne formen standarte http://www.example.com/

 templink.push_back(s);

 procesolink(s);


 cout<<"Po procesohet ! Ju lutem prisni...."<<endl;
 while(Nivele<=niveliim)
 {

 int temp=numriLinqevePerNivel;
 numriLinqevePerNivel=0;
 for(int i=0; i<temp; i++ )
 {
 procesolink(linqet.front());
 linqet.pop();

 }
 Nivele++;

 }



 //shfaqen pa perseritje linqet

 for(int i=0; i<templink.size(); i++)
 cout <<templink.at(i)<<endl;





 return 0;
 }


 void procesolink(string s)
 {

 ofstream out("permbajtjaHTML.txt");
 int nr=0;

 //metodat e librarise Curl
 CURL* curl;
 curl_global_init(CURL_GLOBAL_ALL);
 curl = curl_easy_init();
 curl_easy_setopt(curl, CURLOPT_URL, s.data());
 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
 curl_easy_perform(curl);
 out<<endl<<data<<endl;
 curl_easy_cleanup(curl);
 curl_global_cleanup();
 out.close();
 //leximi i content te webfaqes
 ifstream in;

 in.open("permbajtjaHTML.txt");

 string url;

 while(!in.eof())
 {
 getline(in,url,' ');
 for ( string line; (getline(in,line)); )
 {

 if ((line.find("a href=") != string::npos) &&(line.find("\"" )
!= string::npos))//algoritmi per marrjen e linqeve
 {
 const size_t start_pos = line.find("href");
 string temp = line.substr(start_pos+6);
 const size_t stop_pos = temp.find("\"");
 string result = temp.substr(0, stop_pos);

 outUrl<<result<<endl;
 if(!trajtuar(result)) //krahasimi per shmangjen e cikleve te pafundme
 {

 linqet.push(result);
 templink.push_back(result);//futja ne nje vektor per  krahasimet e mepasshme
 nr++;
 }

 }
}


 numriLinqevePerNivel+=nr;

 in.close();


 data.clear();//fshihen te dhenat e content te webfaqes se pare


 }


 }

 bool trajtuar(string str)
 {


 for(int i=0; i<templink.size(); i++)
 {
 if(str==templink.at(i))
 return true;
 }

 return false;
 }

