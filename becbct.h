#ifndef BECBCT_H
#define BECBCT_H
#define roundt(x) round(x*100)/100.0
#include<windows.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<cmath>
#include<fstream>
#include<iomanip>
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
void Mouse_Move(int x,int y)
{
	double fScreenWidth=::GetSystemMetrics(SM_CXSCREEN)-1;
	double fScreenHeight=::GetSystemMetrics(SM_CYSCREEN)-1;
	double fx=x*(65535.0f/fScreenWidth);
	double fy=y*(65535.0f/fScreenHeight);
	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE,fx,fy,0,0);
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
    if(High!=0)Name = char(High+64)+char(Low);
    else Name = char(Low);
    return Name;
}
void FourierSeriesBuilder(TrigonometricFunction TriFunc[],int i){
    string name = ArmorStandNameBuilder(i), namep = ArmorStandNameBuilder(i++);
    string SelectorA = "@e[type=armor_stand,name=" + name + "]";
    string SelectorB = "@e[type=armor_stand,name=" + namep + "]";
    string Head;
    i==0?Head="[rcb]":Head="[ccb]";
    ofstream ofs;
    ofs.open("in.txt");
    ofs<<Head<<" execute "<<SelectorA<<" ~~~ tp @s ~~~ ~"<<roundt(TriFunc[i].omega)<<"~"<<endl;
    ofs<<"[ccb]"<<" execute "<<SelectorA<<" ~~~ tp "<<SelectorB<<" ^^^"<<roundt(TriFunc[i].omega)<<endl;
    //execute <Selector> ~~~ <FuncName> -----
}
#endif
