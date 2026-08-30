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

    void printAll() const
    {
        printRegisters();
        printFlags();
        printPC();
        printMemory();
    }

    bool isRegisterIndexValid(int index)
    {
        return (index >= 0 && index < 7);
    }

    void processMOV(const string instruction, const string operand1, const string operand2,
                    string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS])
    {

        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

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

        vm.ZF = (value == 0);
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

        // Implement ADD logic
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
        vm.CF = (result > 255 || result < 0);
        vm.ZF = (result == 0);

        r[operand1[1] - '0'] = to_string(result);
    }

    void processSUB(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Implement SUB logic
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

        int result = value1 - value2;

        // Update flags and registers accordingly
        vm.OF = (result > 255);
        vm.UF = (result < 0);
        vm.CF = (result > 255 || result < 0);
        vm.ZF = (result == 0);

        r[operand1[1] - '0'] = to_string(result);
    }

    void processMUL(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Implement MUL logic
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

        // Update flags and registers accordingly
        vm.OF = (result > 255);
        vm.UF = (result < 0);
        vm.CF = (result > 255 || result < 0);
        vm.ZF = (result == 0);

        r[operand1[1] - '0'] = to_string(result);
    }

    void processDIV(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Implement DIV logic
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

        // Update flags and registers accordingly
        vm.OF = (quotient > 255);
        vm.UF = (quotient < 0);
        vm.CF = (quotient > 255 || quotient < 0);
        vm.ZF = (quotient == 0);

        r[operand1[1] - '0'] = to_string(quotient);
    }

    void processINC(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }
        // Increment the value
        int value = stoi(r[operand1[1] - '0']) + 1;

        // Update flags and registers accordingly
        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.CF = (value > 255 || value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processDEC(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Implement DEC logic
        // Decrement the value and update flags and registers accordingly
        int value = stoi(r[operand1[1] - '0']) - 1;
        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.CF = (value > 255 || value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processROL(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Implement ROL logic
        // Rotate the bits in the specified register to the left
        int value = stoi(r[operand1[1] - '0']);
        int msb = (value >> 7) & 1;         // Get the most significant bit
        value = ((value << 1) | msb) & 255; // Rotate left

        // Update flags and registers accordingly
        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.CF = (value > 255 || value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processROR(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Implement ROR logic
        // Rotate the bits in the specified register to the right
        int value = stoi(r[operand1[1] - '0']);
        int lsb = value & 1;                       // Get the least significant bit
        value = ((value >> 1) | (lsb << 7)) & 255; // Rotate right

        // Update flags and registers accordingly
        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.CF = (value > 255 || value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processSHL(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Implement SHL logic
        // Shift the bits in the specified register to the left
        int value = stoi(r[operand1[1] - '0']);

        value = (value << 1) & 255; // Shift left

        // Update flags and registers accordingly
        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.CF = (value > 255 || value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processSHR(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Implement SHR logic
        // Shift the bits in the specified register to the right
        int value = stoi(r[operand1[1] - '0']);
        value = (value >> 1) & 255; // Shift right

        // Update flags and registers accordingly
        vm.OF = (value > 255);
        vm.UF = (value < 0);
        vm.CF = (value > 255 || value < 0);
        vm.ZF = (value == 0);

        r[operand1[1] - '0'] = to_string(value);
    }

    void processLOAD(const string operand1, const string operand2, string r[REGISTERS], VirtualMachine &vm, string memory[ROWS][COLUMNS])
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }
        // Implement LOAD logic

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
        else if ((operand1[0] == 'R' || operand1[0] == 'r') && (operand2[0] == '[' && operand2[operand2.size() - 1] == ']'))
        {
            // Scenario 2: LOAD R1, [R2]

            // Extract the memory address from the register
            int memoryAddress = stoi(r[operand2[1] - '0']);

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

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Implement STORE logic
        if ((operand1[0] == 'R' || operand1[0] == 'r') && !(operand2[0] == '[' && operand2[operand2.size() - 1] == ']'))
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
        else if ((operand1[0] == 'R' || operand1[0] == 'r') && (operand2[0] == '[' && operand2[operand2.size() - 1] == ']'))
        {
            // Scenario 2: STORE R1, [R2]
            int value = stoi(r[operand1[1] - '0']);

            // Extract the memory address from the register
            int memoryAddress = stoi(r[operand2[1] - '0']);

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
        else
        {
            cout << "Invalid STORE format: " << operand1 << ", " << operand2 << endl;
        }
    }

    void processIN(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Check if the user provided input (e.g., value 9)
        int userInput;
        cout << "Enter a value (e.g., 9): ";
        cin >> userInput;
        cin.ignore(80, '\n');

        // Update the specified register with user input
        r[operand1[1] - '0'] = to_string(userInput);

        // Update flags accordingly
        vm.OF = (userInput > 255);
        vm.UF = (userInput < 0);
        vm.CF = (userInput > 255 || userInput < 0);
        vm.ZF = (userInput == 0);
    }

    void processOUT(const string operand1, string r[REGISTERS], VirtualMachine &vm)
    {
        int destIndex = operand1[1] - '0';
        int srcIndex;

        // Check if the destination register index is valid
        if (!isRegisterIndexValid(destIndex))
        {
            cout << "Error: Invalid destination register index." << endl;
            return;
        }

        // Check if OUT instruction has been read
        if (vm.PC >= 0)
        {
            // Display the output message with the content of the specified register
            cout << "OUT R" << operand1[1] - '0' << ": " << r[operand1[1] - '0'] << endl;
        }
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
            processOUT(operand1, r, vm);
        }
    }

    void readFile(ifstream &input)
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

                executeInstruction(instruction, operand1, operand2, Registers, *this, Memory);

                // Updating the Program Counter flag After executing an instruction
                PC++;
                if (OF)
                {
                    CF = true;
                }
                else if (UF)
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

        ifstream input(fileName);
        if (input.fail())
        {
            cout << "File not found" << endl;
            exit(-1);
        }

        vm.readFile(input);

        input.close();
    }

    void printToFile() const
    {
        ofstream outputFile("output.txt");

        // Check if the file is successfully opened
        if (!outputFile.is_open())
        {
            cout << "Error opening the output file." << endl;
            return;
        }

        // Redirect output to the file
        streambuf *coutbuf = cout.rdbuf();              // Save the current cout buffer
        cout.rdbuf(outputFile.rdbuf());                 // Redirect cout to outputFile

        // Print the output to the file
        printAll();

        // Restore the original cout buffer
        cout.rdbuf(coutbuf);

        // Close the output file
        outputFile.close();
    }
};

int main()
{
    ifstream input;
    VirtualMachine vm;
    vm.openFile(vm);
    vm.printAll();
    vm.printToFile();

    return 0;
}