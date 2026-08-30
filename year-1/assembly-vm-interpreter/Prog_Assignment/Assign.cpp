#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

class VirtualMachine {
private:
    vector<char> registers;  // R0, R1, ..., R6
    char programCounter;
    char overflowFlag;
    char underflowFlag;
    char carryFlag;
    char zeroFlag;
    vector<char> memory;

public:
    VirtualMachine() : registers(7, 0), programCounter(0),
                       overflowFlag(0), underflowFlag(0),
                       carryFlag(0), zeroFlag(0), memory(64, 0) {}

    void executeInstruction(const string& instruction);

    void updateFlags(int result);

    void displayState() const {
        cout << "Registers: ";
        for (char reg : registers) {
            cout << setw(2) << static_cast<int>(reg) << " ";
        }
        cout << "#" << endl;

        cout << "Flags: " << static_cast<int>(overflowFlag) << " "
             << static_cast<int>(underflowFlag) << " "
             << static_cast<int>(carryFlag) << " "
             << static_cast<int>(zeroFlag) << "#" << endl;

        cout << "PC: " << static_cast<int>(programCounter) << endl;

        cout << "Memory:" << endl;
        for (int i = 0; i < memory.size(); ++i) {
            cout << setw(2) << static_cast<int>(memory[i]) << " ";
            if ((i + 1) % 8 == 0) {
                cout << endl;
            }
        }
        cout << "#" << endl;
    }

    void loadProgram(const string& filename) {
        ifstream file(filename);
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                executeInstruction(line);
                // You might want to increment the program counter here
            }
            file.close();
        } else {
            cout << "Unable to open file: " << filename << endl;
        }
    }

    // ADD function
    void add(char regSrc, char regDst) {
        int result = registers[regDst] + registers[regSrc];
        registers[regDst] = static_cast<char>(result);
        updateFlags(result);
    }

    // SUB function
    void sub(char regSrc, char regDst) {
        int result = registers[regDst] - registers[regSrc];
        registers[regDst] = static_cast<char>(result);
        updateFlags(result);
    }

    // MUL function
    void mul(char regSrc, char regDst) {
        int result = registers[regDst] * registers[regSrc];
        registers[regDst] = static_cast<char>(result);
        updateFlags(result);
    }

    // DIV function
    void div(char regSrc, char regDst) {
        if (registers[regSrc] != 0) {
            int result = registers[regDst] / registers[regSrc];
            registers[regDst] = static_cast<char>(result);
            updateFlags(result);
        } else {
            cout << "Error: Division by zero." << endl;
        }
    }

    // INC function
    void inc(char regDst) {
        int result = registers[regDst] + 1;
        registers[regDst] = static_cast<char>(result);
        updateFlags(result);
    }

    // DEC function
    void dec(char regDst) {
        int result = registers[regDst] - 1;
        registers[regDst] = static_cast<char>(result);
        updateFlags(result);
    }

    // ROL function
    void rol(char regDst, int count) {
        // Rotate left
        registers[regDst] = (registers[regDst] << count) | (registers[regDst] >> (8 - count));
    }

    // ROR function
    void ror(char regDst, int count) {
        // Rotate right
        registers[regDst] = (registers[regDst] >> count) | (registers[regDst] << (8 - count));
    }

    // SHL function
    void shl(char regDst, int count) {
        // Shift left
        registers[regDst] <<= count;
    }

    // SHR function
    void shr(char regDst, int count) {
        // Shift right
        registers[regDst] >>= count;
    }

    // LOAD function
    void load(char regDst, char addr) {
        registers[regDst] = memory[addr];
    }

    // LOAD function with register-indirect addressing
    void load(char regDst, char* addrReg) {
        registers[regDst] = memory[*addrReg];
    }

    // STORE function
    void store(char regSrc, char addr) {
        memory[addr] = registers[regSrc];
    }

    // STORE function with register-indirect addressing
    void store(char regSrc, char* addrReg) {
        memory[*addrReg] = registers[regSrc];
    }
};

void VirtualMachine::executeInstruction(const string& instruction) {
    istringstream iss(instruction);
    string opcode;
    iss >> opcode;

    if (opcode == "ADD") {
        char regSrc, regDst;
        iss >> regSrc >> regDst;
        add(regSrc - '0', regDst - '0');
    } else if (opcode == "SUB") {
        char regSrc, regDst;
        iss >> regSrc >> regDst;
        sub(regSrc - '0', regDst - '0');
    } else if (opcode == "MUL") {
        char regSrc, regDst;
        iss >> regSrc >> regDst;
        mul(regSrc - '0', regDst - '0');
    } else if (opcode == "DIV") {
        char regSrc, regDst;
        iss >> regSrc >> regDst;
        div(regSrc - '0', regDst - '0');
    } else if (opcode == "INC") {
        char regDst;
        iss >> regDst;
        inc(regDst - '0');
    } else if (opcode == "DEC") {
        char regDst;
        iss >> regDst;
        dec(regDst - '0');
    } else if (opcode == "ROL") {
        char regDst;
        int count;
        iss >> regDst >> count;
        rol(regDst - '0', count);
    } else if (opcode == "ROR") {
        char regDst;
        int count;
        iss >> regDst >> count;
        ror(regDst - '0', count);
    } else if (opcode == "SHL") {
        char regDst;
        int count;
        iss >> regDst >> count;
        shl(regDst - '0', count);
    } else if (opcode == "SHR") {
        char regDst;
        int count;
        iss >> regDst >> count;
        shr(regDst - '0', count);
    } else if (opcode == "LOAD") {
        char regDst, addr;
        iss >> regDst >> addr;
        load(regDst - '0', addr);
    } else if (opcode == "LOAD") {
        char regDst, addrReg;
        iss >> regDst >> addrReg;
        load(regDst - '0', &registers[addrReg - '0']);
    } else if (opcode == "STORE") {
        char regSrc, addr;
        iss >> regSrc >> addr;
        store(regSrc - '0', addr);
    } else if (opcode == "STORE") {
        char regSrc, addrReg;
        iss >> regSrc >> addrReg;
        store(regSrc - '0', &registers[addrReg - '0']);
    } else {
        cout << "Error: Unknown instruction - " << opcode << endl;
    }
}

void VirtualMachine::updateFlags(int result) {
    overflowFlag = (result > 127) ? 1 : 0;
    underflowFlag = (result < -128) ? 1 : 0;
    carryFlag = (result > 127 || result < -128) ? 1 : 0;
    zeroFlag = (result == 0) ? 1 : 0;
}

int main() {
    VirtualMachine vm;

    // Load the program from a file
    vm.loadProgram("instructions.asm");

    // Display the final state of the virtual machine
    vm.displayState();

    return 0;
}
