# BECBCT
- Bedrock Edition Command Block's Convenient Commands Import Tools.

 <img src="./icon.png" width = "300" height = "300" alt="icon" align=center />
 
# Why we establish this project?
- It is very troublesome to set so many command blocks, and the opreation of `.function` file is inconvenience, so that we established this project.
# Input standard:
    Num of commands
    [type of command block] command
    ......
    //Num of command should be an positive integer.
    //command block types contains: rcb(repeating_command_block), ccb(chain_command_block), ncb(command_block).
# Some basic functions:
```cpp
void FourierSeriesBuilder(TrigonometricFunction TriFunc[],int n){}
//TrigonometricFunction is a struct in 'becbct.h'.
//This function is used to turn Forier Series into implement of Minecraft BE command, out put to 'in.txt' with input standard.
void InitialPhaseFix(TrigonometricFunction TriFunc[],int n){}
//This function is used to turn Initial Phase Fixing into implement of Minecraft BE command, out put to 'in.txt' with input standard.
```
# About FourierSeriesBuilder()&InitialPhaseFix()
- These two function will generate a series of commands to generate epicycles which can draw a closed curve.
- There are some keywords.
- `.omega` of `struct TrigonometricFunction` is angular frequency of TrigonometricFunction.
- `.alpha` of `struct TrigonometricFunction` is amplitude of TrigonometricFunction.
- `.fai` of `struct TrigonometricFunction` is initial phase of TrigonometricFunction.
# Edit position:
   You can set the generated coordinates in Main.cpp as follows: 
   ```cpp
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
   ```
