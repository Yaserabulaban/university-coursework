#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
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

void printRegisters(const string r[REGISTERS])
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
}

void printFlags(const VirtualMachine &vm)
{
    cout << "Flags" << setw(5) << ":" << setw(2)
         << vm.OF << setw(2) << setw(2) << vm.UF
         << setw(2) << vm.CF << setw(2) << vm.ZF
         << "#" << endl;
}

void printPC(const VirtualMachine &vm)
{
    cout << "PC." << setw(7) << ":" << setw(2) << vm.PC << endl
         << endl;
}

void printMemory(const string memory[ROWS][COLUMNS])
{
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

void printAll(const string r[REGISTERS], const VirtualMachine &vm, const string memory[ROWS][COLUMNS])
{
    printRegisters(r);
    printFlags(vm);
    printPC(vm);
    printMemory(memory);
}

void processMOV(const string instruction, const string operand1, const string operand2,
                string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS])
{
    int value;
    if (operand2[0] == 'R' || operand2[0] == 'r')
    {
        // Scenario 2: MOV R1, R0
        value = stoi(r[operand2[1] - '0']);
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
        value = stoi(operand2);
        r[operand1[1] - '0'] = to_string(value);
    }

    // Add your flag updates here
    vm.ZF = (value == 0);
}

void processADD(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
{
    // Implement ADD logic
    // Update flags and registers accordingly
}

void processSUB(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
{
    // Implement SUB logic
    // Update flags and registers accordingly
}

void processMUL(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
{
    // Implement MUL logic
    // Update flags and registers accordingly
}

void processDIV(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
{
    // Implement DIV logic
    // Update flags and registers accordingly
}

void processINC(const string operand1, string r[REGISTERS], VirtualMachine &vm)
{
    // Implement INC logic
    // Update flags and registers accordingly
}

void processDEC(const string operand1, string r[REGISTERS], VirtualMachine &vm)
{
    // Implement DEC logic
    // Update flags and registers accordingly
}

void processROL(const string operand1, string r[REGISTERS])
{
    // Implement ROL logic
    // Update flags and registers accordingly
}

void processROR(const string operand1, string r[REGISTERS])
{
    // Implement ROR logic
    // Update flags and registers accordingly
}

void processSHL(const string operand1, string r[REGISTERS])
{
    // Implement SHL logic
    // Update flags and registers accordingly
}

void processSHR(const string operand1, string r[REGISTERS])
{
    // Implement SHR logic
    // Update flags and registers accordingly
}

void processLOAD(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS])
{
    // Implement LOAD logic
    // Update flags and registers accordingly
}

void processSTORE(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS])
{
    // Implement STORE logic
    // Update flags and registers accordingly
}

void processIN(const string operand1, string r[REGISTERS], VirtualMachine &vm)
{
    // Implement IN logic
    // Update flags and registers accordingly
}

void processOUT(const string operand1, string r[REGISTERS], VirtualMachine &vm)
{
    // Implement OUT logic
    // Update flags and registers accordingly
}

void executeInstruction(const string instruction, const string operand1, const string operand2,
                        string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS])
{
    if (instruction == "MOV")
    {
        processMOV(instruction, operand1, operand2, r, vm, memory);
    }
    else if (instruction == "ADD")
    {
        processADD(operand1, operand2, r, vm);
    }
    else if (instruction == "SUB")
    {
        processSUB(operand1, operand2, r, vm);
    }
    else if (instruction == "MUL")
    {
        processMUL(operand1, operand2, r, vm);
    }
    else if (instruction == "DIV")
    {
        processDIV(operand1, operand2, r, vm);
    }
    else if (instruction == "INC")
    {
        processINC(operand1, r, vm);
    }
    else if (instruction == "DEC")
    {
        processDEC(operand1, r, vm);
    }
    else if (instruction == "ROL")
    {
        processROL(operand1, r);
    }
    else if (instruction == "ROR")
    {
        processROR(operand1, r);
    }
    else if (instruction == "SHL")
    {
        processSHL(operand1, r);
    }
    else if (instruction == "SHR")
    {
        processSHR(operand1, r);
    }
    else if (instruction == "LOAD")
    {
        processLOAD(operand1, operand2, r, vm, memory);
    }
    else if (instruction == "STORE")
    {
        processSTORE(operand1, operand2, r, vm, memory);
    }
    else if (instruction == "IN")
    {
        processIN(operand1, r, vm);
    }
    else if (instruction == "OUT")
    {
        processOUT(operand1, r, vm);
    }
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
            executeInstruction(instruction, operand1, operand2, r, vm, memory);

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

    openFile(input);
    initFlags(vm);
    initRegisters(Registers);
    initMemory(memory);
    readFile(input, Registers, memory, vm);
    printAll(Registers, vm, memory);

    input.close();

    return 0;
}
