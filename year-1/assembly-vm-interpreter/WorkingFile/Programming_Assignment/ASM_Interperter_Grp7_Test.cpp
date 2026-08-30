#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

const int COLUMNS = 8, ROWS = 8, REGISTERS = 7;

class VirtualMachine
{
private:
    short PC;
    bool OF, UF, CF, ZF;
    string Registers[REGISTERS];
    string Memory[ROWS][COLUMNS];

public:
    VirtualMachine()
    {
        initFlags();
        initRegisters();
        initMemory();
    }

    void initFlags()
    {
        PC = 0;
        OF = false;
        UF = false;
        CF = false;
        ZF = false;
    }

    void initMemory()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Memory[i][j] = "00";
            }
        }
    }

    void initRegisters()
    {
        for (int i = 0; i < 7; i++)
        {
            Registers[i] = "00";
        }
    }

    void printRegisters() const
    {
        cout << "Registers: ";
        for (int i = 0; i < 7; i++)
        {
            cout << Registers[i];
            if (i != 6)
            {
                cout << " ";
            }
        }
        cout << "#" << endl;
    }

    void printFlags() const
    {
        cout << "Flags" << setw(5) << ":" << setw(2)
             << OF << setw(2) << setw(2) << UF
             << setw(2) << CF << setw(2) << ZF
             << "#" << endl;
    }

    void printPC() const
    {
        cout << "PC." << setw(7) << ":" << setw(2) << PC << endl
             << endl;
    }

    void printMemory() const
    {
        cout << "Memory:" << endl;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << Memory[i][j] << " ";
            }
            cout << endl;
        }
        cout << "#";
    }

    void printAlltoTerminal() const
    {
        printRegisters();
        printFlags();
        printPC();
        printMemory();
    }

    void printAlltoFile(ofstream &outputFile)
    {
        outputFile << "Registers: ";
        for (int i = 0; i < 7; i++)
        {
            outputFile << Registers[i];
            if (i != 6)
            {
                outputFile << " ";
            }
        }
        outputFile << "#" << endl;

        outputFile << "Flags" << setw(5) << ":" << setw(2)
                   << OF << setw(2) << setw(2) << UF
                   << setw(2) << CF << setw(2) << ZF
                   << "#" << endl;

        outputFile << "PC." << setw(7) << ":" << setw(2) << PC << endl
                   << endl;

        outputFile << "Memory:" << endl;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                outputFile << Memory[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile << "#";
    }

    bool isRegisterIndexValid(int index)
    {
        return (index >= 0 && index < 7);
    }

    void processMOV(const string instruction, const string operand1, const string operand2,
                    string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS])
    {

        int srcIndex;
        int value;

        if (operand1[0] != '[' && (operand2[0] == 'r' || operand2[0] == 'R'))
        {
            // Scenario 2: MOV R0, R1
            value = stoi(r[operand1[1] - '0']);
            r[operand2[1] - '0'] = to_string(value);
        }
        else if (operand1[0] == '[')
        {
            // Scenario 3: MOV [R1], R3
            int memoryAddress = stoi(r[(operand1[2] - '0')]);
            cout << "Memory Address = " << memoryAddress << endl;

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

        vm.ZF = (value == 0);
        vm.OF = (value > 255);
        vm.UF = (value < 0);
    }

    void processADD(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        int value1 = stoi(r[operand1[1] - '0']);
        int value2;

        if (operand2[0] == 'R' || operand2[0] == 'r')
        {
            // ADD R1, R2
            value2 = stoi(r[operand2[1] - '0']);
        }
        else
        {
            // ADD R1, 10
            value2 = stoi(operand2);
        }

        int result = value1 + value2;

        // Update flags and registers accordingly
        vm.OF = (result > 255);
        vm.UF = (result < 0);
        vm.ZF = (result == 0);

        r[operand1[1] - '0'] = to_string(result);
    }

    void processSUB(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        int value1 = stoi(r[operand1[1] - '0']);
        int value2;

        if (operand2[0] == 'R' || operand2[0] == 'r')
        {
            // SUB R1, R2
            value2 = stoi(r[operand2[1] - '0']);
        }
        else
        {
            // SUB R1, 10
            value2 = stoi(operand2);
        }

        int result = value2 - value1;

        vm.OF = (result > 255);
        vm.UF = (result < 0);
        vm.ZF = (result == 0);

        r[operand1[1] - '0'] = to_string(result);
    }

    void processMUL(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        int value1 = stoi(r[operand1[1] - '0']);
        int value2;

        if (operand2[0] == 'R' || operand2[0] == 'r')
        {
            // MUL R1, R2
            value2 = stoi(r[operand2[1] - '0']);
        }
        else
        {
            // MUL R1, 10
            value2 = stoi(operand2);
        }

        int result = value1 * value2;

        vm.OF = (result > 255);
        vm.UF = (result < 0);
        vm.ZF = (result == 0);

        r[operand1[1] - '0'] = to_string(result);
    }

    void processDIV(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        int dividend = stoi(r[operand1[1] - '0']);
        int divisor;

        if (operand2[0] == 'R' || operand2[0] == 'r')
        {
            // DIV R1, R2
            divisor = stoi(r[operand2[1] - '0']);

            // Check for division by zero
            if (divisor == 0)
            {
                cout << "Error: Division by zero." << endl;
                exit(-1);
            }
        }
        else
        {
            // DIV R1, 10
            divisor = stoi(operand2);

            // Check for division by zero
            if (divisor == 0)
            {
                cout << "Error: Division by zero." << endl;
                exit(-1);
            }
        }

        int quotient = dividend / divisor;

        vm.OF = (quotient > 255);
        vm.UF = (quotient < 0);
        vm.ZF = (quotient == 0);

        r[operand1[1] - '0'] = to_string(quotient);
    }

    void processINC(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        int value = stoi(r[operand1[1] - '0']) + 1;

        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processDEC(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        int value = stoi(r[operand1[1] - '0']) - 1;
        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processROL(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Rotate the bits in the specified register to the left
        int value = stoi(r[operand1[1] - '0']);
        int msb = (value >> 7) & 1;         // Get the most significant bit
        value = ((value << 1) | msb) & 255; // Rotate left

        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processROR(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Rotate the bits in the specified register to the right
        int value = stoi(r[operand1[1] - '0']);
        int lsb = value & 1;                       // Get the least significant bit
        value = ((value >> 1) | (lsb << 7)) & 255; // Rotate right

        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processSHL(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Shift the bits in the specified register to the left
        int value = stoi(r[operand1[1] - '0']);

        value = (value << 1) & 255; // Shift left

        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processSHR(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Shift the bits in the specified register to the right
        int value = stoi(r[operand1[1] - '0']);
        value = (value >> 1) & 255; // Shift right

        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processLOAD(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS])
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }
        if ((operand1[0] == 'R' || operand1[0] == 'r') && !(operand2[0] == '[' && operand2[operand2.size() - 1] == ']'))
        {
            // Scenario 1: LOAD R1, 10
            // Extract the memory address from operand2
            int memoryAddress = stoi(operand2);

            // Check if the memory address is within bounds
            if (memoryAddress >= 0 && memoryAddress < 64)
            {
                int value = stoi(memory[memoryAddress / COLUMNS][memoryAddress % COLUMNS]);
                r[operand1[1] - '0'] = to_string(value);
            }
            else
            {
                cout << "Invalid memory address: " << memoryAddress << endl;
            }
        }
        else if ((operand1[0] == 'R' || operand1[0] == 'r') && (operand2[0] == '['))
        {
            // Scenario 2: LOAD R1, [R2]
            // Extract the memory address from the register
            int memoryAddress = stoi(r[operand2[2] - '0']);

            // Check if the memory address is within bounds
            if (memoryAddress >= 0 && memoryAddress < 64)
            {
                int value = stoi(memory[memoryAddress / COLUMNS][memoryAddress % COLUMNS]);
                r[operand1[1] - '0'] = to_string(value);
            }
            else
            {
                cout << "Invalid memory address: " << memoryAddress << endl;
            }
        }
        else
        {
            cout << "Invalid LOAD format: " << operand1 << ", " << operand2 << endl;
        }
    }

    void processSTORE(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS])
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        if ((operand1[0] == 'R' || operand1[0] == 'r') && !(operand2[0] == '['))
        {
            // Scenario 1: STORE R1, 10
            int value = stoi(r[operand1[1] - '0']);

            // Extract the memory address from operand2
            int memoryAddress = stoi(operand2);

            // Check if the memory address is within bounds
            if (memoryAddress >= 0 && memoryAddress < 64)
            {
                memory[memoryAddress / COLUMNS][memoryAddress % COLUMNS] = to_string(value);
            }
            else
            {
                cout << "Invalid memory address: " << memoryAddress << endl;
            }
        }
        else if ((operand1[0] == 'R' || operand1[0] == 'r') && (operand2[0] == '['))
        {
            // Scenario 2: STORE R1, [R2]
            int value = stoi(r[operand1[1] - '0']);

            // Extract the memory address from the register
            int memoryAddress = stoi(r[operand2[2] - '0']);

            // Check if the memory address is within bounds
            if (memoryAddress >= 0 && memoryAddress < 64)
            {
                stoi(memory[memoryAddress / COLUMNS][memoryAddress % COLUMNS] = to_string(value));
            }
            else
            {
                cout << "Invalid memory address: " << memoryAddress << endl;
            }
        }
        else
        {
            cout << "Invalid STORE format: " << operand1 << ", " << operand2 << endl;
        }
    }

    void processIN(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Check if the user provided input (e.g., value 9)
        int userInput;
        cout << "Enter a value between 0 and 255: ";
        cin >> userInput;
        cin.ignore(80, '\n');

        // Update the specified register with user input
        r[operand1[1] - '0'] = to_string(userInput);

        vm.OF = (userInput > 255);
        vm.UF = (userInput < 0);
        vm.ZF = (userInput == 0);
    }

    void processOUT(const string operand1, string r[REGISTERS], VirtualMachine &vm, ofstream &outputFile)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }
        else
        {
            // Display the output message with the content of the specified register
            cout << "OUT R" << operand1[1] - '0' << ":" << r[operand1[1] - '0'] << endl;
            outputFile << "OUT R" << operand1[1] - '0' << ":" << r[operand1[1] - '0'] << endl;
        }
    }

    void executeInstruction(const string instruction, const string operand1, const string operand2,
                            string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS], ofstream &outputFile)
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
            processROL(operand1, r, vm);
        }
        else if (instruction == "ROR")
        {
            processROR(operand1, r, vm);
        }
        else if (instruction == "SHL")
        {
            processSHL(operand1, r, vm);
        }
        else if (instruction == "SHR")
        {
            processSHR(operand1, r, vm);
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
            processOUT(operand1, r, vm, outputFile);
        }
    }

    void readFile(ifstream &input, ofstream &outputFile)
    {
        string line;

        while (getline(input, line))
        {
            istringstream iss(line);
            string instruction, operand1, operand2;

            if (iss >> instruction >> operand1)
            {
                // Process each instruction and update the virtual machine state
                if (instruction == "INC" || instruction == "DEC")
                {
                    // For INC and DEC, set operand2 to an empty string
                    operand2 = "";
                }
                else
                {
                    // For other instructions, read the second operand
                    iss >> operand2;
                }

                executeInstruction(instruction, operand1, operand2, Registers, *this, Memory, outputFile);

                // Updating the Program Counter flag After executing an instruction
                PC++;
                if (OF)
                {
                    CF = true;
                }
            }
            else
            {
                cout << "Invalid instruction format: " << line << endl;
                exit(-1);
            }
        }
    }

    void openFile(VirtualMachine &vm)
    {
        string fileName;
        cout << "Enter the name of the file with .asm /.txt extension: ";
        cin >> fileName;

        ofstream output;
        ifstream input(fileName);
        if (input.fail())
        {
            cout << "File not found" << endl;
            exit(-1);
        }

        vm.readFile(input, output);

        input.close();
    }

    void printToFile(VirtualMachine &vm)
    {
        ofstream outputFile("output.txt");

        // Check if the file is successfully opened
        if (!outputFile.is_open())
        {
            cout << "Error opening the output file." << endl;
            return;
        }

        // Print the output to the file
        vm.printAlltoFile(outputFile);

        // Close the output file
        outputFile.close();
    }
};

int main()
{
    ifstream input;
    ofstream output;
    VirtualMachine vm;
    
    vm.openFile(vm);
    vm.printAlltoTerminal();
    vm.printToFile(vm);

    return 0;
}