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
	Sleep(70);
	press(111);
	Sleep(300);
	Ctrl_V();
	Sleep(700);
	press(27);
	Sleep(100);
	press(27);
}
int main(){
	TrigonometricFunction TF[10000];
	int n;
	cin>>n;
	for(int i=0;i<n;++i)cin>>TF[i].omega>>TF[i].alpha;
	FourierSeriesBuilder(TF,n);
	cout<<"start!"<<endl; 
	freopen("in.txt","r",stdin);
	int types,cb;
	cin>>types;
	cb=types/2+1;
	string commands[types+5];
	string commandblocks[types+5];
	for(int i=1;i<=types;i++){
		cin>>commandblocks[i];
		getchar();
		getline(cin,commands[i]);
	}
	Sleep(3000);
	for(int i=1;i<=cb;i++){
		string type;
		if(i==1)type="command_block";
		else type="chain_command_block";
		command("setblock "+to_string(2-i)+" 4 2 "+type+" 4");
		Sleep(500);
	}
	Sleep(400);
	for(int i=1;i<=cb;i++){
		command("tp @s "+to_string(2-i)+" 5 2 -90 90");
		Sleep(500);
		commandblock("summon armor_stand "+ArmorStandNameBuilder(i-1)+" 10 10 10");
		Sleep(800);
	}
	Sleep(400);
	for(int i=1;i<=types;i++){
		string type;
		if(commandblocks[i]=="[rcb]")type="repeating_command_block";
		else if(commandblocks[i]=="[ccb]")type="chain_command_block";
		else type="command_block";
		command("setblock "+to_string(2-i)+" 4 1 "+type+" 4");
		Sleep(500);
	}
	Sleep(400);
	for(int i=1;i<=types;i++){
		command("tp @s "+to_string(2-i)+" 5 1 -90 90");
		Sleep(500);
		commandblock(commands[i]);
		Sleep(800);
	}
	fclose(stdin);
}
