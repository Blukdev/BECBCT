#ifndef BECBCT_H
#define BECBCT_H
#include<cmath>
#include<cstdio>
#include<string>
#include<conio.h>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<windows.h>
#define roundt(x) round(x*100)/100.0
using namespace std;
struct TrigonometricFunction{
    float alpha;
    float omega;
    float fai;
};
string ArmorStandNameBuilder(int Num){
    int High=Num/58;
    int Low=Num%58;
    string Name;
    if(High!=0){
    	Name="";
    	Name+=char(High+65);
		  Name+=char(Low+65);
	  }
    else Name=char(Low+65);
    return Name;
}
void FourierSeriesBuilder(TrigonometricFunction TriFunc[],int n){
    string name,namep,SelectorA,SelectorB,Head;
    ofstream ofs;
    ofs.open("in.txt");
    ofs<<n*2<<endl;
	  for(register int i=0;i<n;++i){
	      name=ArmorStandNameBuilder(i);
	      namep=ArmorStandNameBuilder(i+1);
        SelectorA="@e[type=armor_stand,name=\""+name+"\"]";
    	  SelectorB="@e[type=armor_stand,name=\""+namep+"\"]";
    	  i==0?Head="[rcb]":Head="[ccb]";
    	  ofs<<Head<<" execute "<<SelectorA<<" ~~~ tp @s ~~~ ~"<<roundt((-1)*TriFunc[i].omega)<<"~"<<endl;
    	  ofs<<"[ccb]"<<" execute "<<SelectorA<<" ~~~ tp "<<SelectorB<<" ^^^"<<roundt(TriFunc[i].alpha)<<endl;
	  }
    ofs.close();
}
void InitialPhaseFix(TrigonometricFunction TriFunc[],int n){
    string name,Selector,Head;
    ofstream ofs;
    ofs.open("initial.txt");
    ofs<<n*2<<endl;
	  for(register int i=0;i<n;++i){
	    name=ArmorStandNameBuilder(i);
      Selector="@e[type=armor_stand,name=\""+name+"\"]";
      i==0?Head="[ncb]":Head="[ccb]";
      ofs<<Head<<" execute "<<Selector<<" ~~~ tp @s ~~~ 0 0"<<endl;
      TriFunc[i].fai-=round(TriFunc[i].fai/2/3.14159265358979)*2*3.14159265358979;
      ofs<<"[ccb]"<<" execute "<<Selector<<" ~~~ tp @s ~~~ ~"<<roundt(((-1)*TriFunc[i].fai*180/3.14159265358979))<<"~"<<endl;
	  }
    ofs.close();
}
#endif
