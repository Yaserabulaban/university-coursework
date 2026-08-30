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

void readFile(ifstream &input, string r[REGISTERS], string memory[ROWS][COLUMNS], VirtualMachine &vm)
{
    string line;

    while (getline(input, line))
    {
        istringstream iss(line);
        string instruction, operand1, operand2;

        if (iss >> instruction >> operand1 >> operand2)
        {
            // Process each instruction and update the virtual machine state
            if (instruction == "MOV")
            {
                int vlaue;
                if (operand2[0] == 'R' || operand2[0] == 'r')
                {
                    // Scenario 2: MOV R1, R0
                    int value = stoi(r[operand2[1] - '0']);
                    r[operand1[1] - '0'] = to_string(value);
                }
                else if (operand1[0] == '[' && operand1[operand1.size() - 1] == ']')
                {
                    // Scenario 3: MOV [R1], R3
                    int memoryAddress = stoi(operand1.substr(2, operand1.size() - 3));
                    // Check if the memory address is within bounds
                    if (memoryAddress >= 0 && memoryAddress < 64)
                    {
                        int memValue = stoi(memory[memoryAddress / COLUMNS][memoryAddress % COLUMNS]);
                        r[operand2[1] - '0'] = to_string(memValue);
                    }
                    else
                    {
                        cout << "Invalid memory address: " << memoryAddress << endl;
                    }
                }
                else
                {
                    // Scenario 1: MOV R0, 10
                    int value = stoi(operand2);
                    r[operand1[1] - '0'] = to_string(value);
                }

                // Add your flag updates here
                vm.ZF = (vlaue == 0);
            }

            else if (instruction == "ADD")
            {
                int value1, value2;
                if (operand1[0] == 'R' || operand1[0] == 'r')
                    value1 = stoi(r[operand1[1] - '0']);
                else
                    value1 = stoi(operand1);

                if (operand2[0] == 'R' || operand2[0] == 'r')
                    value2 = stoi(r[operand2[1] - '0']);
                else
                    value2 = stoi(operand2);

                int result = value1 + value2;

                vm.OF = (result > 255);
                vm.UF = (result < 0);
                vm.ZF = (result == 0);

                r[operand1[1] - '0'] = to_string(result);
            }
            else if (instruction == "SUB")
            {
                int value1, value2;
                if (operand1[0] == 'R' || operand1[0] == 'r')
                    value1 = stoi(r[operand1[1] - '0']);
                else
                    value1 = stoi(operand1);

                if (operand2[0] == 'R' || operand2[0] == 'r')
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
                if (operand1[0] == 'R' || operand1[0] == 'r') // Operand1 is a register
                    value1 = stoi(r[operand1[1] - '0']);
                else // Operand1 is a constant
                    value1 = stoi(operand1);

                if (operand2[0] == 'R' || operand2[0] == 'r') // Operand2 is a register
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
                if (operand1[0] == 'R' || operand1[0] == 'r') // Operand1 is a register
                    dividend = stoi(r[operand1[1] - '0']);
                else // Operand1 is a constant
                    dividend = stoi(operand1);

                if (operand2[0] == 'R' || operand2[0] == 'r') // Operand2 is a register
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
                if (operand1[0] == 'R' || operand1[0] == 'r')
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
                if (operand1[0] == 'R' || operand1[0] == 'r')
                {
                    int regIndex = operand1[1] - '0';
                    int value = stoi(r[regIndex]);
                    value--;

                    vm.UF = (value < 0);
                    vm.ZF = (value == 0);
                    r[regIndex] = to_string(value);
                }
            }
            else if (instruction == "ROL")
            {
                if (operand1[0] == 'R' || operand1[0] == 'r')
                {
                    int regIndex = operand1[1] - '0';
                    string regValue = r[regIndex];
                    char msb = regValue[0];

                    // Rotate left
                    regValue = regValue.substr(1) + msb;

                    r[regIndex] = regValue;
                }
            }
            else if (instruction == "ROR")
            {
                if (operand1[0] == 'R' || operand1[0] == 'r')
                {
                    int regIndex = operand1[1] - '0';
                    string regValue = r[regIndex];
                    char lsb = regValue[regValue.size() - 1];

                    // Rotate right
                    regValue = lsb + regValue.substr(0, regValue.size() - 1);

                    r[regIndex] = regValue;
                }
            }
            else if (instruction == "SHL")
            {
                if (operand1[0] == 'R' || operand1[0] == 'r')
                {
                    int regIndex = operand1[1] - '0';
                    string regValue = r[regIndex];

                    // Shift left (add a '0' at the rightmost position)
                    regValue += '0';

                    r[regIndex] = regValue;
                }
            }
            else if (instruction == "SHR")
            {
                if (operand1[0] == 'R' || operand1[0] == 'r')
                {
                    int regIndex = operand1[1] - '0';
                    string regValue = r[regIndex];

                    // Shift right (remove the rightmost bit)
                    regValue = regValue.substr(0, regValue.size() - 1);

                    r[regIndex] = regValue;
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
                    vm.ZF = (regValue == 0);
                }
                else
                {
                    cout << "Invalid memory address: " << memoryAddress << endl;
                }
            }
            else if (instruction == "IN")
            {
                int regIndex = operand1[1] - '0';
                cout << "Enter a value for register R" << regIndex << ": ";
                cin >> r[regIndex];

                vm.OF = (regIndex > 255);
                vm.UF = (regIndex < 0);
                vm.ZF = (regIndex == 0);
            }
            else if (instruction == "OUT")
            {
                int regIndex = operand1[1] - '0';
                cout << "Value in register R" << regIndex << ": " << r[regIndex] << endl;

                vm.OF = (regIndex > 255);
                vm.UF = (regIndex < 0);
                vm.ZF = (regIndex == 0);
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
    // inputFromUser(Registers, vm, regName);
    // outToConsole(Registers[0]);
    printAll(Registers, memory, vm);

    input.close();

    return 0;
}