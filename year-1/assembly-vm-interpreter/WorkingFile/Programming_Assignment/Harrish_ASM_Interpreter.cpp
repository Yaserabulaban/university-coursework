#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
using namespace std;

struct flags
{
  int PC = 0;
  bool OF = false,
       UF = false,
       ZF = false,
       CF = false;  
};
struct registry
{
    signed int RAM[7];
    signed int memory[64];  
};

registry reg;

flags flag;
ifstream infile;


void fileReader(string file, vector<string> &commands);
void ResetFlags(flags flag);
void Display(registry &reg, flags flag);

void OUT(registry reg, signed int index[2]);
void IN(registry &reg, signed int index[2], bool &userInput);
void MOV(registry &reg, signed int index[2],signed int number, bool addressing_required, bool number_required);
void ADD(registry &reg, signed int index[2], signed int number, bool number_required);
void SUB(registry &reg, signed int index[2], signed int number, bool number_required);
void MUL(registry &reg, signed int index[2], signed int number, bool number_required);
void DIV(registry &reg, signed int index[2], signed int number, bool number_required);
void INC(registry &reg, signed int index[2]);
void ROL(registry &reg, signed int index[2], signed int number);
void ROR(registry &reg, signed int index[2], signed int number);
void SHL(registry &reg, signed int index[2], signed int number);
void SHR(registry &reg, signed int index[2], signed int number);
void LOAD(registry &reg, signed int index[2], signed int number, bool addressing_required);

void flagchecker(registry reg, signed int number, signed int index[2], flags &flag, bool arithmetic, bool userInput, vector<string> commands, int i);
void comma_check(bool &comma_check, vector<string> &commands, int j, vector<string> &elements, bool &addressing_required);
void translator(vector<string> commands, int j, signed int index[2], signed int &number, bool &addressing_required, bool &number_required);
void commandExecutor(registry &reg, vector<string> commands, int i);
void output(vector<string> commands, flags flag);



int main()
{
    system("cls");
    vector<string> commands;
    fileReader("a.txt", commands);
    output(commands, flag);

return 0;
}


void fileReader(string file, vector<string> &commands)
{
    infile.open(file);
    
    string command;
    while (infile >> command)
    {        
        commands.push_back(command);
    }   
    
    infile.close();
}
void ResetFlags(flags flag)
{
    flag.OF = false;
    flag.CF = false;
    flag.UF = false;
    flag.ZF = false;
}
void Display(registry &reg, flags flag)
{
    cout << "Flags:"  <<  setw(5) <<  "PC"     << setw(5) << "UF"     << setw(5) << "OF"     << setw(5) << "ZF"     << setw(5) << "CF"     << endl
         << "Output:" <<  setw(4) <<  flag.PC << setw(5) << flag.UF << setw(5) << flag.OF << setw(5) << flag.ZF << setw(5) << flag.CF << endl; 
    
    cout << endl << "Data registers:"<< endl;
    int i = 0;
    while (i < 7)
    {cout << reg.RAM[i] << "  "; i++;}
    cout << endl;

    int j = 0;
    while (j < 64)
    {
        if (j % 8 == 0)
        {
            cout << endl;
        }
        cout << reg.memory[j] << "  ";
        j++;
    }
    cout <<  endl;
    
    string next;
    cout << "Press any key to continue to next line of assembly code within the file." << endl;
    cin >> next;
}


void flagchecker(registry reg, signed int number, signed int index[2], flags &flag, bool arithmetic, bool userInput, vector<string> commands, int i)
{
    if (!userInput)
    {
        if ((reg.RAM[index[1]] > 255) || (reg.RAM[index[0]] > 255))
            flag.OF = true;

        else if ((reg.RAM[index[1]] < 0) || (reg.RAM[index[0]] < 0))
            flag.UF = true;

        else if (arithmetic)
        {
            if ((reg.RAM[index[1]] == 0 || reg.RAM[index[0]] == 0))
                flag.ZF = true;

            else if (((reg.RAM[index[1]] | reg.RAM[index[0]]) < 0) || ((reg.RAM[index[1]] | reg.RAM[index[0]]) > 255))
                flag.CF = true;
        }
    }
}
void comma_check(bool &comma_check, vector<string> &commands, int j, vector<string> &elements, bool &addressing_required)
{
    comma_check = false;
    addressing_required = false;

    int k = 0;
    while (k < commands[j].size())
    {
        if (commands[j][k] == ',')
        {   
            comma_check = true;
            commands[j][k] = ' ';
        }

        else if (commands[j][k] == '[' || commands[j][k] == ']')
            addressing_required = true;
        k++;
    }
    istringstream iss(commands[j]);
            
    string element;
    while (iss >> element)
    {
        elements.push_back(element);
    }
}
void translator(vector<string> commands, int j, signed int index[2], signed int &number, bool &addressing_required, bool &number_required)
{
    vector <string> elements;
    bool comma;
    j++;
    addressing_required = false;
    number_required = false;
    comma_check(comma, commands, j, elements, addressing_required);

    if (!comma)//for all operations involving only one data register
    {
        if (elements[0] == "R0") index[0] = 0;
        else if (elements[0] == "R1") index[0] = 1;
        else if (elements[0] == "R2") index[0] = 2;
        else if (elements[0] == "R3") index[0] = 3;
        else if (elements[0] == "R4") index[0] = 4;
        else if (elements[0] == "R5") index[0] = 5;
        else if (elements[0] == "R6") index[0] = 6;
        
        index[1] = -1;
    }
    
    else if (comma)
    {
        int m = 0;
        while (m < 2)
        {
            if (elements[m] == "R0") index[m] = 0;
            else if (elements[m] == "R1") index[m] = 1;
            else if (elements[m] == "R2") index[m] = 2;
            else if (elements[m] == "R3") index[m] = 3;
            else if (elements[m] == "R4") index[m] = 4;
            else if (elements[m] == "R5") index[m] = 5;
            else if (elements[m] == "R6") index[m] = 6;
            else
            {
                number_required = true;
                istringstream iss(elements[m]);
                iss >> number;
            }
            m++;
        }
    }
}

void OUT(registry reg, signed int index[2])
{
    cout << reg.RAM[index[0]] << endl;
}
void IN(registry &reg, signed int index[2], bool &userInput)
{
    userInput = true;
    signed int number;
    cout << "Please enter a integer:" << endl;
    cin >> reg.RAM[index[0]];
}
void MOV(registry &reg, signed int index[2], signed int number, bool addressing_required, bool number_required)
{
    if (addressing_required)
        reg.RAM[index[1]] = reg.RAM[reg.RAM[index[0]]];
    
    else if (number_required)
        reg.RAM[index[1]] = number;
    
    else
        reg.RAM[index[1]] = reg.RAM[index[0]];
}
void ADD(registry &reg, signed int index[2], signed int number, bool number_required)
{
    if (number_required)
        reg.RAM[index[0]] = reg.RAM[index[0]] + number;
    
    else
        reg.RAM[index[1]] = reg.RAM[index[1]] + reg.RAM[index[0]];
}
void SUB(registry &reg, signed int index[2], signed int number, bool number_required)
{
    if (number_required)
        reg.RAM[index[0]] = reg.RAM[index[0]] - number;
    
    else
        reg.RAM[index[1]] = reg.RAM[index[1]] - reg.RAM[index[0]];
}
void MUL(registry &reg, signed int index[2], signed int number, bool number_required)
{
    if (number_required)
        reg.RAM[index[0]] = reg.RAM[index[0]] * number;
    
    else
        reg.RAM[index[1]] = reg.RAM[index[1]] * reg.RAM[index[0]];
}
void DIV(registry &reg, signed int index[2], signed int number, bool number_required)
{
    if (number_required)
        reg.RAM[index[0]] = reg.RAM[index[0]] / number;
    
    else
        reg.RAM[index[1]] = reg.RAM[index[1]] / reg.RAM[index[0]];
}
void INC(registry &reg, signed int index[2])
{
    reg.RAM[index[0]]++;
}
void DEC(registry &reg, signed int index[2])
{
    reg.RAM[index[0]]--;
}
void ROL(registry &reg, signed int index[2], signed int number)
{
    bitset<8> bits(reg.RAM[index[0]]);
    
    // Rotate left by the specified number of positions
    bits = ((bits << number) | (bits >> (8 - number)));

    // Check if the leftmost bit after rotation is 1 (carry)
    flag.CF = bits.test(7);

    reg.RAM[index[0]] = static_cast<int>(bits.to_ulong());
}
void ROR(registry &reg, signed int index[2], signed int number)
{
    bitset<8> bits(reg.RAM[index[0]]);
    
    // Rotate left by the specified number of positions
    bits = ((bits >> number) | (bits << (8 - number)));

    // Check if the leftmost bit after rotation is 1 (carry)
    flag.CF = bits.test(7);

    reg.RAM[index[0]] = static_cast<int>(bits.to_ulong());
}
void SHL(registry &reg, signed int index[2], signed int number)
{
    bitset<8> bits(reg.RAM[index[0]]);
    
    bits = bits << number;

    reg.RAM[index[0]] = static_cast<int>(bits.to_ulong());
}
void SHR(registry &reg, signed int index[2], signed int number)
{
    bitset<8> bits(reg.RAM[index[0]]);
    
    bits = bits >> number;

    reg.RAM[index[0]] = static_cast<int>(bits.to_ulong());
}
void LOAD(registry &reg, signed int index[2], signed int number, bool addressing_required)
{
    if (addressing_required)
        reg.RAM[index[0]] = reg.memory[reg.RAM[index[1]]];
  
    else
        reg.RAM[index[0]] = reg.memory[number];

}
void STORE(registry &reg, signed int index[2], signed int number, bool addressing_required)
{
    if (addressing_required)
        reg.memory[reg.RAM[index[1]]] = reg.RAM[index[0]];
    
    else 
        reg.memory[number] = reg.RAM[index[0]];
}

void commandExecutor(registry &reg, vector<string> commands, int i)
{
        int index[2];
        signed int number;
        bool addressing_required;
        bool number_required;
        bool userInput;

        translator(commands, i, index, number, addressing_required, number_required);

        if (commands[i] == "IN") IN(reg,index, userInput);
        else if (commands[i] == "OUT") OUT(reg, index);
        else if (commands[i] == "MOV") MOV(reg, index, number, addressing_required, number_required);
        else if (commands[i] == "ADD") ADD(reg, index, number, number_required);
        else if (commands[i] == "SUB") SUB(reg, index, number, number_required);
        else if (commands[i] == "MUL") MUL(reg, index, number, number_required);
        else if (commands[i] == "DIV") DIV(reg, index, number, number_required);
        else if (commands[i] == "INC") INC(reg, index);
        else if (commands[i] == "DEC") DEC(reg,index);
        else if (commands[i] == "ROL") ROL(reg, index, number);
        else if (commands[i] == "ROR") ROR(reg, index, number);
        else if (commands[i] == "SHL") SHL(reg, index, number);
        else if (commands[i] == "SHR") SHR(reg, index, number);
        else if (commands[i] == "LOAD") LOAD(reg, index, number, addressing_required);
        else if (commands[i] == "STORE") STORE(reg,index, number, addressing_required);
        else 
            cout << "Error! No identifiable code." << endl;
        
        bool arithmetic;
        if ((commands[i] == "ADD") || (commands[i] == "SUB") || (commands[i] == "MUL") || (commands[i] == "DIV") || (commands[i] == "INC") || (commands[i] == "DEC"))
            arithmetic = true;

        flagchecker(reg, number, index, flag, arithmetic, userInput, commands, i);
}
void output(vector<string> commands, flags flag)
{
    int i = 0;
    while (flag.PC < (commands.size() / 2))
    {
        flag.PC++;
        ResetFlags(flag);
        commandExecutor(reg, commands, i);
        Display(reg, flag);
        i = i + 2;
    }
}

