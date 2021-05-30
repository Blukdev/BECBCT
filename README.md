# BECBCT
- Bedrock Edition Command Block's Convenient Commands Import Tools.

 <img src="./icon.png" width = "300" height = "300" alt="icon" align=center />
 
# Why we establish this project?
- It is very troublesome to set so many command blocks, and the opreation of .function file is inconvenience, so that we established this project.
# Input standard:
    Num of commands
    [type of command block] command
    ......
    //Num of command should be an positive integer.
    //command block types contains: rcb(repeating_command_block), ccb(chain_command_block), ncb(command_block).
# Some basic functions:
    void FourierSeriesBuilder(TrigonometricFunction TriFunc[],int n)
    //TrigonometricFunction is a struct in 'becbct.h'.
    //This function is used to turn Forier Series into implement of Minecraft BE command, out put to 'in.txt' with input standard.
    void InitialPhaseFix(TrigonometricFunction TriFunc[],int n)
    //This function is used to turn Initial Phase Fixing into implement of Minecraft BE command, out put to 'in.txt' with input standard.
