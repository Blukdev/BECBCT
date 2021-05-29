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
void down(int vk){
	keybd_event(vk,0,0,0);
}
void up(int vk){
    keybd_event(vk,0,KEYEVENTF_KEYUP,0);
}
void press(int vk){
    down(vk);
    Sleep(50);
    up(vk);
}
void Ctrl_V(){
	keybd_event(VK_CONTROL,0,0,0);
    keybd_event('V',0,0,0);
    Sleep(50);
    keybd_event('V',0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}
bool CopyToClipboard(const char* pszData, const int nDataLen){
    if(::OpenClipboard(NULL)){
        ::EmptyClipboard();
        HGLOBAL clipbuffer;
        char *buffer;
        clipbuffer=::GlobalAlloc(GMEM_DDESHARE,nDataLen+1);
        buffer=(char*)::GlobalLock(clipbuffer);
        strcpy(buffer,pszData);
        ::GlobalUnlock(clipbuffer);
        ::SetClipboardData(CF_TEXT,clipbuffer);
        ::CloseClipboard();
        return true;
    }
    return false;
}
void command(string cmd){
	CopyToClipboard(cmd.c_str(),cmd.size());
	press(84);
	Sleep(50);
	press(111);
	Sleep(50);
	Ctrl_V();
	Sleep(500);
	press(13);
}
void commandblock(string cmd){
	CopyToClipboard(cmd.c_str(),cmd.size());
	press(2);
	Sleep(50);
	press(111);
	Sleep(70);
	Ctrl_V();
	Sleep(500);
	press(27);
	Sleep(100);
	press(27);
}
string ArmorStandNameBuilder(int Num){
    int High = Num/26;
    int Low = Num%26;
    string Name;
    if(High!=0)Name = char(High+64)+char(Low+64);
    else Name = char(Low+64);
    return Name;
}
void FourierSeriesBuilder(TrigonometricFunction TriFunc[],int n){
    string name, namep, SelectorA, SelectorB, Head;
    ofstream ofs;
    ofs.open("in.txt");
    ofs<<n<<endl;
	for(register int i=0;i<n;++i){
	    name = ArmorStandNameBuilder(i);
	    namep = ArmorStandNameBuilder(i+1);
            SelectorA = "@e[type=armor_stand,name=" + name + "]";
    	    SelectorB = "@e[type=armor_stand,name=" + namep + "]";
    	    i==0?Head="[rcb]":Head="[ccb]";
    	    ofs<<Head<<" execute "<<SelectorA<<" ~~~ tp @s ~~~ ~"<<roundt(TriFunc[i].omega)<<"~"<<endl;
    	    ofs<<"[ccb]"<<" execute "<<SelectorA<<" ~~~ tp "<<SelectorB<<" ^^^"<<roundt(TriFunc[i].alpha)<<endl;
	}
    ofs.close();
    //execute <Selector> ~~~ <FuncName> -----
}
#endif
