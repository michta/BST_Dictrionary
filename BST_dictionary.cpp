#include<iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

typedef struct node{
struct node *pRt,*pLf;
string sWord,sMeaning;
}NODE;

class cQueue{
 NODE *pQ[20000];
 int iF,iR;
public:
 cQueue(){
  	iF=iR=-1;
    }
 void fInsert(NODE*);
 NODE* fDelete();
 int fIsempty();
};

void cQueue::fInsert(NODE *pT){
 pQ[iR++]=pT;
}

NODE* cQueue::fDelete(){
 return(pQ[iF++]);
}

int cQueue::fIsempty(){
 if(iF==iR)
 return 1;
 return 0;
}

class cDictionary{
public:
    NODE* fCreate();
    void fAdd(NODE*);
    void fDisplay(NODE*);
    void find_translate(NODE*, std::string);
};

NODE* cDictionary::fCreate(){
    NODE *pRoot,*pNn,*pCn,*pParent;
    char cCh;
    pRoot=NULL;
    do{
        pNn = new NODE;
        pNn -> pLf = pNn -> pRt = NULL;
        cout<<"Enter word: ";
        cin>>pNn->sWord;
        cout<<"Enter meaning: ";
        cin>>pNn->sMeaning;

        if(pRoot == NULL)
        pRoot=pNn;
        else{
            pCn=pRoot;
            while(pCn){
                pParent=pCn;
                if(pCn->sWord<pNn->sWord)
                pCn=pCn->pRt;
                else
                pCn=pCn->pLf;
            }
            if(pParent->sWord<pNn->sWord)
            pParent->pRt=pNn;
            else
            pParent->pLf=pNn;
        }
        cout<<"do you want to continue(y/n) : ";
         cin>>cCh;

    }while(cCh=='y'||cCh=='Y');
return pRoot;
}

void cDictionary::fAdd(NODE *pRoot){

	std::ifstream polish;
	std::ifstream english;

	std::string word_pol="", word_eng ="";

	polish.open("pl.csv");
	english.open("eng.csv");
    int counter = 10000;

    NODE *pCn,*pNn,*pParent;
  //  pNn -> pLf = pNn -> pRt = NULL;
	
    while(counter){

    getline(polish, word_pol);
    getline(english,word_eng);
    counter--;
    std::cout << counter << "\n";
    pNn = new NODE;
   
    pNn->sWord = word_pol;
    pNn->sMeaning = word_eng;
     
    pCn=pRoot;

    while(pCn){

        pParent=pCn;
        if(pCn->sWord < pNn->sWord)
            pCn=pCn->pRt;
        else
            pCn=pCn->pLf;
    }
    if(pParent->sWord<pNn->sWord)
    pParent->pRt=pNn;
    else
    pParent->pLf=pNn;
    cout<<"Word is added Succesfully to the Dictionary\n";
    }
	polish.close();
	english.close();
}

void cDictionary::fDisplay(NODE *pPtr){
    if(pPtr){
        fDisplay(pPtr->pLf);
        cout<<pPtr -> sWord<< " -> " <<pPtr -> sMeaning << "\n";
        fDisplay(pPtr->pRt);
    }
}

void cDictionary::find_translate(NODE *ptr, std::string word){
      if(ptr){
        find_translate(ptr->pLf, word);

         if(ptr->sWord == word){
             std::cout << ptr->sWord << " -> " << ptr->sMeaning <<"\n";
         }
         if(ptr->sMeaning == word){
              std::cout << ptr->sMeaning << " -> " << ptr->sWord <<"\n";
         }
         find_translate(ptr->pRt, word);
    }
}

int main(){

    clock_t start;
    double duration{0};

    NODE *pRoot;
    string sW;
    cDictionary oObj;
    char cCh;
    int iCh;
   
    do{
        cout<<"1. Create dictionary\n";
        cout<<"2. Add new word to the dictionary\n";
        cout<<"3. Display dictionary \n";
        cout<<"4. Translator \n";
    
	   cin>>iCh;
        switch(iCh)
        {
        case 1:
            pRoot = oObj.fCreate();
            break;
        case 2:
            oObj.fAdd(pRoot);
            break;
        case 3:
            oObj.fDisplay(pRoot);
            break;
        
        case 4:{ 
            std::string word;
            std::cin >> word;
            start = clock();
            oObj.find_translate(pRoot, word);
            duration = (clock() - start) / (double)CLOCKS_PER_SEC;
            std::cout << "CZAS: " << duration << "\n";
        }break;
        }
        std::cout << "\n press 1 for main and 2 to exit ";
        std::cin >> cCh;
    }while(cCh=='1');
}