#include <iostream>
using namespace std;

struct VirtualMachine {
    short PC;
    char R[7];
    bool OF;
};

void initVM(VirtualMachine& vm) {
    vm.PC = 0;
    vm.OF = false;
    for (int i = 0; i < 7; i++)
        vm.R[i] = 0;
}

void execInstructions(VirtualMachine& vm) {
    // MOV  R0, 17
    vm.R[0] = 17;
    vm.PC++;

    // MOV  R3, 9
    vm.R[3] = 9;
    vm.PC++;

    //ADD  R3, R0
    vm.R[0] = vm.R[0] + vm.R[3];
}

void printVM(const VirtualMachine& vm) {
    cout << "PC= " << vm.PC << endl;
    cout << "OF= " << vm.OF << endl;
    for (int i = 0; i < 7; i++)
        cout << "R" << i << "=" << int(vm.R[i]) << " ";
    cout << endl;
}

// pass struct by value
// any cnage to vm in this function is a change
// to the copy not the original vm in the main 
// function
void passAcopy(VirtualMachine vm) {
    vm.PC = 100;
}

int main()
{
    VirtualMachine vm;
    initVM(vm);
    execInstructions(vm);
    cout << "--------" << endl;
    printVM(vm);
    cout << "--------" << endl;

    // demo pass by value
    passAcopy(vm);
    printVM(vm);

    return 0;
}