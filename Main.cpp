#include "becbct.h"
using namespace std;
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
	Sleep(150);
	press(111);
	Sleep(300);
	Ctrl_V();
	Sleep(650);
	press(27);
	Sleep(100);
	press(27);
}
struct settings{
	int x;
	int y;
	int z;
}sets,setb,sete,setfix;
void init(){
	//set main list pos
	sets.x=1;
	sets.y=4;
	sets.z=1;
	//set summon list pos
	setb.x=1;
	setb.y=4;
	setb.z=3;
	//set entity pos
	sete.x=10;
	sete.y=4;
	sete.z=10;
	//set initial pos
	setfix.x=1;
	setfix.y=4;
	setfix.z=5;
}
TrigonometricFunction TF[10000];
void Getdata(int &n){
	ifstream datain("set.txt");
	datain>>n;
	for(int i=0;i<n;++i)datain>>TF[i].omega>>TF[i].alpha>>TF[i].fai;
	datain.close();
}
int main(){
	init();
	int n,types,cb,fixs;
	Getdata(n);
	FourierSeriesBuilder(TF,n);
	InitialPhaseFix(TF,n);
	cout<<"start!"<<endl; 
	ifstream fin("in.txt");
	fin>>types;
	cb=types/2+1;
	string commands[types+5],commandblocks[types+5];
	for(int i=1;i<=types;i++){
		fin>>commandblocks[i];
		getline(fin,commands[i]);
		commands[i].erase(0,1);
	}
	fin.close();
	ifstream fixin("initial.txt");
	fixin>>fixs;
	string fixcommands[types+5],fixcommandblocks[types+5];
	for(int i=1;i<=fixs;i++){
		fixin>>fixcommandblocks[i];
		getline(fixin,fixcommands[i]);
		fixcommands[i].erase(0,1);
	}
	fixin.close();
	Sleep(3000);
	for(int i=1;i<=cb;i++){
		string type;
		if(i==1)type="command_block";
		else type="chain_command_block";
		command("setblock "+to_string(setb.x-i+1)+" "+to_string(setb.y)+" "+to_string(setb.z)+" "+type+" 4");
		Sleep(500);
	}
	Sleep(400);
	for(int i=1;i<=cb;i++){
		command("tp @s "+to_string(setb.x-i+1)+" "+to_string(setb.y+1)+" "+to_string(setb.z)+" -90 90");
		Sleep(500);
		commandblock("summon armor_stand "+ArmorStandNameBuilder(i-1)+" "+to_string(sete.x)+" "+to_string(sete.y)+" "+to_string(sete.z));
		Sleep(800);
	}
	Sleep(400);
	for(int i=1;i<=types;i++){
		string type;
		if(commandblocks[i]=="[rcb]")type="repeating_command_block";
		else if(commandblocks[i]=="[ccb]")type="chain_command_block";
		else type="command_block";
		command("setblock "+to_string(sets.x-i+1)+" "+to_string(sets.y)+" "+to_string(sets.z)+" "+type+" 4");
		Sleep(500);
	}
	Sleep(400);
	for(int i=1;i<=types;i++){
		command("tp @s "+to_string(sets.x-i+1)+" "+to_string(sets.y+1)+" "+to_string(sets.z)+" -90 90");
		Sleep(500);
		commandblock(commands[i]);
		Sleep(800);
	}
	Sleep(400);
	for(int i=1;i<=fixs;i++){
		string type;
		if(fixcommandblocks[i]=="[rcb]")type="repeating_command_block";
		else if(fixcommandblocks[i]=="[ccb]")type="chain_command_block";
		else type="command_block";
		command("setblock "+to_string(setfix.x-i+1)+" "+to_string(setfix.y)+" "+to_string(setfix.z)+" "+type+" 4");
		Sleep(500);
	}
	Sleep(400);
	for(int i=1;i<=fixs;i++){
		command("tp @s "+to_string(setfix.x-i+1)+" "+to_string(setfix.y+1)+" "+to_string(setfix.z)+" -90 90");
		Sleep(500);
		commandblock(fixcommands[i]);
		Sleep(800);
	}
}
