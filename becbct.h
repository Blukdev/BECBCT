#ifndef BECBCT_H
#define BECBCT_H
#define roundt(x) round(x*100)/100.0
#include<windows.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<cmath>
#include<fstream>
#include <iomanip>
#include<cmath>
using namespace std;
struct TrigonometricFunction{
    float alpha;
    float omega;
};
string ArmorStandNameBuilder(int Num){
    int High=Num/26;
    int Low=Num%26;
    string Name;
    if(High!=0){
    	Name="";
    	Name+=char(High+64);
	Name+=char(Low+64);
    }
    else Name=char(Low+64);
    return Name;
}
void FourierSeriesBuilder(TrigonometricFunction TriFunc[],int n){
    string name,namep,SelectorA,SelectorB,Head;
    ofstream ofs;
    ofs.open("in.txt");
    ofs<<n<<endl;
	for(register int i=0;i<n;++i){
	    name=ArmorStandNameBuilder(i);
	    namep=ArmorStandNameBuilder(i+1);
            SelectorA="@e[type=armor_stand,name="+name+"]";
    	    SelectorB="@e[type=armor_stand,name="+namep+"]";
    	    i==0?Head="[rcb]":Head="[ccb]";
    	    ofs<<Head<<" execute "<<SelectorA<<" ~~~ tp @s ~~~ ~"<<roundt(TriFunc[i].omega)<<"~"<<endl;
    	    ofs<<"[ccb]"<<" execute "<<SelectorA<<" ~~~ tp "<<SelectorB<<" ^^^"<<roundt(TriFunc[i].alpha)<<endl;
	}
    ofs.close();
}
#endif
