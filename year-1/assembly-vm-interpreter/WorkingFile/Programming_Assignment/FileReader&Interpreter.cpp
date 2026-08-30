#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class interpreter_elements
{
private:
    struct registry
    {
        signed int RAM[7] = {0}; // Initialize all elements to 0
        signed int memory[64] = {0}; // Initialize all elements to 0
    };

    struct flags 
    {
        int PC = 0;
        bool OF = false;
        bool UF = false;
        bool ZF = false;
        bool CF = false;
    };



public:
    registry reg; // This is the definition of the registry which will be used to store the data registers and memory.
    flags flag; // This is the definition of the flags which will be used to store the flags.
};
interpreter_elements registry;

class operations //This is the class used to group the operations together.
{
public:
    void MOV(bool addressing_required, unsigned int location[2])
    {
        if (addressing_required)
            registry.reg.RAM[location[1]] = registry.reg.memory[registry.reg.memory[location[0]]];
        
        else 
            registry.reg.RAM[location[1]] = registry.reg.RAM[location[0]];
    }
    void ADD() {}
    void SUB() {}
    void MUL() {}
    void DIV() {}
    void IN() {}
    void OUT() {}
    void STORE() {}
    void LOAD() {}
};
operations operation_element;

class FileReaderandInterpreter //This is the class which will be used to read the file and interpret the commands.
{
private:
    ifstream infile;

public:
    vector<string> fileReader(string file)
    {
        infile.open(file);
        vector<string> commands;

        string command;
        while (infile >> command)
        {
            commands.push_back(command); //The operation here each command line in the file into two parts sequentially. For example, MOV R1,R2. Within commands, it is commands[0] = "MOV and commands[1] = "R1,R2". Assuming there were no commands before this one.
        }

        infile.close();
    return commands;
    }
    /*
        This function reads a file and stores it into a vector called commands.
            It will store each line of the file into two parts, the operation and the elements.
                The size of this "commands" is 2 times the number of commands in the file.
    */
    void command_elements_cleaner(vector <string> commands, vector<string> &stringed_elements, int j, bool &comma, bool &addressing_required)
    {
            int k = 0;
            while (k < commands[j].size())
            {
                if (commands[j][k] == ',')
                {
                    commands[j].erase(k, 1); // Removes the comma for every i + 1 term in commands if it is required.
                    comma = true;
                }
                else if (commands[j][k] == '[' || commands[j][k] == ']')
                {
                    addressing_required = true;
                }
                else
                {
                    ++k;
                }
                istringstream iss(commands[j]);

                string temp;
                while (iss >> temp)
                {
                    stringed_elements.push_back(temp);
                }
                j++;
            }
    }
    /*
        This function separates the i + 1 elements of commands into a vector called stringed_elements.
            It also determines whether addressing ([memory address]) is required so that STORE, LOAD, MOV can be used.
                It also determines whether the command requires one or two data registers through the use of a flag called comma.
    */
    unsigned int element_determinant(vector<string> stringed_elements, unsigned int location[2], bool comma)
    {
        if (!comma) 
        {
            if (stringed_elements[0] == "R0") { location[0] = 0; }
            else if (stringed_elements[0] == "R1") { location[0] = 1; }
            else if (stringed_elements[0] == "R2") { location[0] = 2; }
            else if (stringed_elements[0] == "R3") { location[0] = 3; }
            else if (stringed_elements[0] == "R4") { location[0] = 4; }
            else if (stringed_elements[0] == "R5") { location[0] = 5; }
            else if (stringed_elements[0] == "R6") { location[0] = 6; }
            location[1] = -1;
        }
        
        else if (comma) 
        {
            int m = 0;
            while (m < 2) 
            {
                if (stringed_elements[m] == "R0") { location[m] = 0; }
                else if (stringed_elements[m] == "R1") { location[m] = 1; }
                else if (stringed_elements[m] == "R2") { location[m] = 2; }
                else if (stringed_elements[m] == "R3") { location[m] = 3; }
                else if (stringed_elements[m] == "R4") { location[m] = 4; }
                else if (stringed_elements[m] == "R6") { location[m] = 6; }
                else 
                {
                    istringstream iss(stringed_elements[m]);
                    iss >> location[m];
                }
                m++; 
            }
        }
    }
    /*
        This is a function which determines where the commands occur in the data register.
        
        In the general case where elements[0] is a data register and elements[1] is a data register,
        the data registers will be stored as int in location[0] and location[1] respectively.

            The data register will be accessed by calling reg.RAM[location[0]] or reg.RAM[location[1]].

        In the case there is only one data registry required by the command, it will be in location[0].

        If there is a stringed number (that is a number in a string form, such as "2" as opposed to 2),
        in this case there are numbers required by the command, this will be reflected in elements as a string,
        this function will interpret elements and will store the number into the corresponding location it was found in the array "location" as an unsigned integer.
        This will be accessed by calling number.
    */
    void operation(bool addressing_required, vector<string> commands, unsigned int location[2], int i)
    {
        if (commands[i] == "MOV") { operation_element.MOV(addressing_required, location); }
        else if (commands[i] == "ADD") { operation_element.ADD(location); }
        else if (commands[i] == "SUB") { operation_element.SUB(location); }
        else if (commands[i] == "MUL") { operation_element.MUL(location); }
        else if (commands[i] == "DIV") { operation_element.DIV(location); }
        else if (commands[i] == "AND") { operation_element.AND(location); }
        else if (commands[i] == "INC") { operation_element.INC(location); }
        else if (commands[i] == "DEC") { operation_element.DEC(location); }
        else if (commands[i] == "STORE") { operation_element.STORE(addressing_required, location); }
        else if (commands[i] == "LOAD") { operation_element.LOAD(addressing_required, location); }
        else { cout << "Error: Invalid command." << endl; }
    }
    /*
        The operations are defined in a class called operations. This function will call the operations from the class operations.
        
        This is where the operations are carried out. All the operations possible (MOV, ADD, SUB, etc.) will be carried out here.
            The operation done will depend on the i th command in commands.

        The operation determined will then use location to determine which data registers to use,
            "number" to determine the number to use if there's a number required as opposed to another data register

    */

};

int main()
{
    FileReaderandInterpreter file_reading;

    string file = "commands.asm"; //chosen file to be read.
    vector <string> file_commands = file_reading.fileReader(file); //Converts contents of the file into a vector called file_commands.
    
    unsigned int number;
    
    int i = 0;
    while (i < (file_commands.size() / 2) )
    {
        bool addressing_required = false;
        bool number_required = false;
        bool comma = false;

        vector<string> elements;
        int operation;
        unsigned int location[2];
        int number = 0;

        file_reading.command_elements_cleaner(file_commands, elements, i + 1, comma, addressing_required);
        //This function will determine the elements from the i + 1 location in commands, determie comma existence & addressing requirement.
        
        file_reading.element_determinant(elements, location, comma);
        //This function will determine the location of the elements in the data register or the number required by the command.

        file_reading.operation(addressing_required, file_commands, location, i);
        //This function will carry out the operation determined by the i th command in commands, the locations and elements as determined
        //by the previous functions.

        i = i + 2;
    }


    return 0;
}
