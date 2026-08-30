#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

const int COLUMNS = 8, ROWS = 8, REGISTERS = 7;

struct VirtualMachine
{
    short PC;
    bool OF, UF, CF, ZF;
};

void initFlags(VirtualMachine &vm)
{
    vm.PC = 0;
    vm.OF = false;
    vm.UF = false;
    vm.CF = false;
    vm.ZF = false;
}

void initMemory(string memory[ROWS][COLUMNS])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            memory[i][j] = "00";
        }
    }
}

void initRegisters(string r[REGISTERS])
{
    for (int i = 0; i < 7; i++)
    {
        r[i] = "00";
    }
}

void openFile(ifstream &input)
{

    input.open("a.txt");

    if (input.fail())
    {
        cout << "File not found" << endl;
        exit(-1);
    }
}

void printAll(string r[REGISTERS], string memory[ROWS][COLUMNS], VirtualMachine vm)
{
    cout << "Registers: ";
    for (int i = 0; i < 7; i++)
    {
        cout << r[i];
        if (i != 6)
        {
            cout << " ";
        }
    }
    cout << "#" << endl;

    cout << "Flags" << setw(5) << ":" << setw(2)
         << vm.OF << setw(2) << setw(2) << vm.UF
         << setw(2) << vm.CF << setw(2) << vm.ZF
         << "#" << endl
         << "PC." << setw(7) << ":" << setw(2) << vm.PC << endl
         << endl;

    cout << "Memory:" << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << memory[i][j] << " ";
        }
        cout << endl;
    }
    cout << "#";
}

bool inputFromUser(string r[REGISTERS], VirtualMachine &vm, const string &registerName)
{
    int inputValue;
    cout << "Enter a value for register " << registerName << ": ";
    cin >> inputValue;

    // Validate input (e.g., check if the input is within the valid range)
    if (inputValue < 0 || inputValue > 255)
    {
        cout << "Invalid input value. Please enter a value between 0 and 255." << endl;
        return false;
    }

    r[registerName[1] - '0'] = to_string(inputValue);

    // Update flags based on specific conditions
    vm.OF = (inputValue > 255);
    vm.UF = (inputValue < 0);
    vm.CF = false;
    vm.ZF = (inputValue == 0);

    return true;
}

void outToConsole(string registerValue)
{
    cout << "Value in the register: " << registerValue << endl;
}

void readFile(ifstream &input, string r[REGISTERS], string memory[ROWS][COLUMNS], VirtualMachine &vm)
{
    string line;

    while (getline(input, line))
    {
        istringstream iss(line);
        string instruction, operand1, operand2;

        if (iss >> instruction)
        {
            operand2 = "";

            if (instruction == "MOV" || instruction == "ADD" ||
                instruction == "SUB" || instruction == "MUL" ||
                instruction == "DIV" || instruction == "LOAD" || instruction == "STORE")
            {
                if (!(iss >> operand1 >> operand2))
                {
                    cout << "Invalid instruction format: " << line << endl;
                    continue; // Skip processing this line
                }
                else
                {
                    // Instructions with one operand
                    if (!(iss >> operand1))
                    {
                        cout << "Invalid instruction format: " << line << endl;
                        continue; // Skip processing this line
                    }
                }
            }

            // Process each instruction and update the virtual machine state
            if (instruction == "MOV")
            {
                int value;
                if (operand2[0] == 'R') // Operand2 is a register
                    value = stoi(r[operand2[1] - '0']);
                else // Operand2 is a constant
                    value = stoi(operand2);

                // Update destination register (Operand1)
                r[operand1[1] - '0'] = to_string(value);

                // Update flags (For simplicity, assume MOV never affects flags)
                vm.OF = false;
                vm.UF = false;
                vm.ZF = false;
            }

            else if (instruction == "ADD")
            {
                int value1, value2;
                if (operand1[0] == 'R')
                    value1 = stoi(r[operand1[1] - '0']);
                else
                    value1 = stoi(operand1);

                if (operand2[0] == 'R')
                    value2 = stoi(r[operand2[1] - '0']);
                else
                    value2 = stoi(operand2);

                int result = value1 + value2;

                vm.OF = (result > 255);
                vm.UF = (result < 0);
                vm.ZF = result == 0;

                r[operand1[1] - '0'] = to_string(result);
            }
            else if (instruction == "IN")
            {
                // Handle IN instruction
                if (iss >> operand1) // Check for an operand
                {
                    if (operand1[0] == 'R')
                    {
                        bool inputProvided = inputFromUser(r, vm, operand1);
                    }
                    else
                    {
                        cout << "Invalid operand for IN instruction: " << operand1 << endl;
                    }
                }
                else
                {
                    cout << "Error: Missing operand for IN instruction" << endl;
                    exit(-1);
                }
            }
            else if (instruction == "OUT")
            {
                // Handle OUT instruction
                if (iss >> operand1) // Check for an operand
                {
                    if (operand1[0] == 'R')
                    {
                        int regIndex = operand1[1] - '0';
                        outToConsole(r[regIndex]);
                    }
                    else
                    {
                        cout << "Invalid operand for OUT instruction: " << operand1 << endl;
                    }
                }
                else
                {
                    cout << "Error: Missing operand for OUT instruction" << endl;
                    exit(-1);
                }
            }
            else if (instruction == "SUB")
            {
                int value1, value2;
                if (operand1[0] == 'R')
                    value1 = stoi(r[operand1[1] - '0']);
                else
                    value1 = stoi(operand1);

                if (operand2[0] == 'R')
                    value2 = stoi(r[operand2[1] - '0']);
                else
                    value2 = stoi(operand2);

                int result = value1 - value2;

                vm.OF = (result > 255);
                vm.UF = (result < 0);
                vm.ZF = result == 0;

                r[operand1[1] - '0'] = to_string(result);
            }
            else if (instruction == "MUL")
            {
                int value1, value2;
                if (operand1[0] == 'R') // Operand1 is a register
                    value1 = stoi(r[operand1[1] - '0']);
                else // Operand1 is a constant
                    value1 = stoi(operand1);

                if (operand2[0] == 'R') // Operand2 is a register
                    value2 = stoi(r[operand2[1] - '0']);
                else // Operand2 is a constant
                    value2 = stoi(operand2);

                // Perform multiplication
                int result = value1 * value2;

                // Update flags
                vm.OF = (result > 255);
                vm.UF = (result < 0);
                vm.ZF = result == 0;

                // Update destination register (Assuming operand1 is always a register)
                r[operand1[1] - '0'] = to_string(result);
            }

            else if (instruction == "DIV")
            {
                int dividend, divisor;
                if (operand1[0] == 'R') // Operand1 is a register
                    dividend = stoi(r[operand1[1] - '0']);
                else // Operand1 is a constant
                    dividend = stoi(operand1);

                if (operand2[0] == 'R') // Operand2 is a register
                    divisor = stoi(r[operand2[1] - '0']);
                else // Operand2 is a constant
                    divisor = stoi(operand2);

                // Check for division by zero
                if (divisor == 0)
                {
                    cout << "Error: Division by zero" << endl;
                    exit(-1);
                }

                // Perform division
                int quotient = dividend / divisor;
                int remainder = dividend % divisor;

                // Update flags
                vm.OF = (quotient > 255);
                vm.UF = (quotient < 0);
                vm.ZF = quotient == 0;

                // Update destination register (Assuming operand1 is always a register)
                r[operand1[1] - '0'] = to_string(quotient);
            }
            else if (instruction == "INC")
            {
                // Handle INC instruction
                if (operand1[0] == 'R')
                {
                    int regIndex = operand1[1] - '0';
                    int currentValue = stoi(r[regIndex]);
                    int result = currentValue + 1;

                    vm.OF = (result > 255);
                    vm.UF = false; // INC doesn't cause underflow
                    vm.ZF = (result == 0);

                    r[regIndex] = to_string(result);
                }
            }
            else if (instruction == "DEC")
            {
                if (operand1[0] == 'R')
                {
                    int regIndex = operand1[1] - '0';
                    int value = stoi(r[regIndex]);
                    value--;

                    vm.UF = (value < 0);
                    vm.ZF = (value == 0);
                    r[regIndex] = to_string(value);
                }
                else
                {
                    cout << "Invalid operand for DEC instruction: " << operand1 << endl;
                }
            }
            else if (instruction == "ROL")
            {
                if (operand1[0] == 'R')
                {
                    int regIndex = operand1[1] - '0';
                    string regValue = r[regIndex];
                    char msb = regValue[0];

                    // Rotate left
                    regValue = regValue.substr(1) + msb;

                    r[regIndex] = regValue;
                }
                else
                {
                    cout << "Invalid operand for ROL instruction: " << operand1 << endl;
                }
            }
            else if (instruction == "ROR")
            {
                if (operand1[0] == 'R')
                {
                    int regIndex = operand1[1] - '0';
                    string regValue = r[regIndex];
                    char lsb = regValue[regValue.size() - 1];

                    // Rotate right
                    regValue = lsb + regValue.substr(0, regValue.size() - 1);

                    r[regIndex] = regValue;
                }
                else
                {
                    cout << "Invalid operand for ROR instruction: " << operand1 << endl;
                }
            }
            else if (instruction == "SHL")
            {
                if (operand1[0] == 'R')
                {
                    int regIndex = operand1[1] - '0';
                    string regValue = r[regIndex];

                    // Shift left (add a '0' at the rightmost position)
                    regValue += '0';

                    r[regIndex] = regValue;
                }
                else
                {
                    cout << "Invalid operand for SHL instruction: " << operand1 << endl;
                }
            }
            else if (instruction == "SHR")
            {
                if (operand1[0] == 'R')
                {
                    int regIndex = operand1[1] - '0';
                    string regValue = r[regIndex];

                    // Shift right (remove the rightmost bit)
                    regValue = regValue.substr(0, regValue.size() - 1);

                    r[regIndex] = regValue;
                }
                else
                {
                    cout << "Invalid operand for SHR instruction: " << operand1 << endl;
                }
            }
            else if (instruction == "LOAD")
            {
                int regIndex = operand1[1] - '0';
                int memoryAddress = stoi(operand2);

                // Check if the memory address is within bounds
                if (memoryAddress >= 0 && memoryAddress < 64)
                {
                    // Convert the value from memory to an integer before loading into the register
                    int memValue = stoi(memory[memoryAddress / COLUMNS][memoryAddress % COLUMNS]);
                    r[regIndex] = to_string(memValue);

                    // Update flags based on specific conditions
                    vm.OF = (memValue > 255);
                    vm.UF = (memValue < 0);
                    vm.CF = false; // Adjust based on your conditions
                    vm.ZF = (memValue == 0);
                }
                else
                {
                    cout << "Invalid memory address: " << memoryAddress << endl;
                }
            }
            else if (instruction == "STORE")
            {
                int regIndex = operand1[1] - '0';
                int memoryAddress = stoi(operand2);

                // Check if the memory address is within bounds (you might want to add more checks based on your requirements)
                if (memoryAddress >= 0 && memoryAddress < 64)
                {
                    // Convert the value from the register to an integer before storing
                    int regValue = stoi(r[regIndex]);
                    memory[memoryAddress / COLUMNS][memoryAddress % COLUMNS] = to_string(regValue);

                    // Update flags based on specific conditions
                    vm.OF = (regValue > 255);
                    vm.UF = (regValue < 0);
                    vm.CF = false; // Adjust based on your conditions
                    vm.ZF = (regValue == 0);
                }
                else
                {
                    cout << "Invalid memory address: " << memoryAddress << endl;
                }
            }
            // Updating the Program Counter flag After executing an instruction
            vm.PC++;
            if (vm.OF)
            {
                vm.CF = true;
            }
            else if (vm.UF)
            {
                vm.CF = true;
            }
        }
        else
        {
            cout << "Invalid instruction format: " << line << endl;
        }
    }
}

int main()
{
    ifstream input;
    string memory[ROWS][COLUMNS];
    string Registers[REGISTERS];
    VirtualMachine vm;
    string regName;

    openFile(input);
    initFlags(vm);
    initRegisters(Registers);
    initMemory(memory);
    readFile(input, Registers, memory, vm);
    inputFromUser(Registers, vm, regName);
    outToConsole(Registers[0]);
    printAll(Registers, memory, vm);

    input.close();

    return 0;
}