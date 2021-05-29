#include "becbct.h"
using namespace std; 
int main(){
	freopen("in.txt","r",stdin);
	int x=1,y=5,z=1;
	int types;
	cin>>types;
	string commands[types+5];
	string commandblocks[types+5];
	for(int i=1;i<=types;i++){
		cin>>commandblocks[i];
		getchar();
		getline(cin,commands[i]);
	}
	Sleep(3000);
	for(int i=1;i<=types;i++){
		string type;
		if(commandblocks[i]=="[rcb]")type="repeating_command_block";
		else if(commandblocks[i]=="[ccb]")type="chain_command_block";
		else type="command_block";
		command("setblock "+to_string(x-i+1)+" 4 1 "+type+" 4");
		Sleep(500);
	}
	Sleep(400);
	for(int i=1;i<=types;i++){
		command("tp @s "+to_string(x-i+1)+" 5 1 -90 90");
		Sleep(500);
		commandblock(commands[i]);
		Sleep(800);
	}
	fclose(stdin);
}
