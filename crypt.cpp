#include <string.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <vector>


using namespace std;

int main(int argc, char* argv[]){

int k = 0; //ключ
int type = 0; //0 - кодирование, 1 - декодирование
int errorCounter = 0;//счетчик ошибок
string opt;
string newAlph="0"; 
string addopt;
int keyCounter = 0;
for (int i = 1; i<argc; i++) { //обработка опций
    opt.assign(argv[i]);
    addopt.assign(argv[i+1]);
        if ((opt == "-t") && (addopt == "decode")){type = 1;errorCounter=errorCounter+2;}
        if ((opt == "-t") && (addopt == "encode")){errorCounter=errorCounter+2;}
        if (opt == "-t=decode"){errorCounter++;type =1;}
        if (opt == "-t=encode"){errorCounter++;}
        if ((opt == "-h") || (opt == "--help")){system ("Help.txt"); errorCounter++;}
        if ((opt == "-a") && (addopt !="-t")){newAlph = argv[i+1];errorCounter++;i++;}
        if ((atoi(argv[i])>-10) && (atoi(argv[i])< 10)) { k = atoi(argv[i]); errorCounter++;keyCounter=i;break;}
        if (errorCounter==0){cout<<"Wrong options! Try -h\n";return 1;}

        errorCounter--;
}
if ((keyCounter == 0) && (errorCounter != 0)) {
    cout<<"Parameters are incorrectly set!"; system ("Help.txt");
    }
if (k<=0){
    cout<<"Wrong key! Try -h\n";
    return 2;
}
const char *input;
const char *output; 
if ((keyCounter+3) == argc) {input=argv[keyCounter+1];output= argv[keyCounter+2];} //определение source и dest
if ((keyCounter+2) == argc) {input=argv[keyCounter+1];output= argv[keyCounter+1];}

if(type==1){k=k*(-1);} //если декодируем, то ключ будет отрицательный

FILE *in,*out;
   in = fopen(input, "r+");

   if (in == NULL) {cout<<"Input file not found\n"; return 3;}

   vector <char> result; //создаем вектор для занесения туда результата кодирования

    bool alph = (newAlph != "0"); //проверка на использования нового алфавита

   char s;

   while (!feof(in)){
        fread (&s ,sizeof(char) , 1, in);

        int symb=int(s);

        if (feof(in)) break;
        //если символа нет в новом алфавите, то не шифруем его
        if (alph&&newAlph.find(s,0)==-1) {result.push_back(s); continue;} 

        
        if((symb>=65) && (symb<=90)){       //шифруем/дешифруем заглавные латинские буквы
            symb = (char)(65+((symb-65+k+26*type)%26));
        }
        if((symb>=97) && (symb<=122)){      //шифруем/дешифруем строчные латинские буквы
            symb = (char)(97+((symb-97+k+26*type)%26));
        }
        if((symb>=48) && (symb<=57)){       //шифруем/дешифруем цифры
            symb = (char)(48+((symb-48+k+10*type)%10));
        }
        if ((symb<48) || ((symb>57) && (symb<65)) || ((symb>90) && (symb<97)) || (symb>122)){
            symb = (char)(symb);
        }  
        result.push_back(symb);    //все остальные символы не меняем
}
fclose(in);
    int size = (int) result.size();
    out = fopen(output, "wb");
    for (int i =0;i < size; i++) fwrite(&result[i],sizeof(char),1,out);
cout<<"You are awesome!\n";
    
getch();
return 0;
}  
