#include <iostream>
using namespace std;


int main () {

    int word_11 = 33; // Load immediate 11 = load 11, load direct 11 = 33, load indirect 11 = 44
    int word_33 = 44;
    int word_44 = 99;
    int word_99 = 88;
    int register_B = 33;


    return 0;
}


/*
𝑍 = [𝑊 + (𝑃 𝑥 𝑄)] / (𝑌 + 𝑋). Available instructions are given below:
a. Registers: A, B and C
b. Instructions: MOV R1,#DATA; MOV R1, R2; ADD R1, R2; SUB R1,R2; MUL R1,R2 and DIV R1,R2

MOV A, W =>   A = W
MOV B, P =>   B = P
MOV C, Q =>   C = Q
MUL B, C =>   B = P * Q
ADD A, B =>   A = W + (P * Q)
MOV B, Y =>   B = Y
MOV C, X =>   C = X
ADD B, C =>   B = Y + X
DIV A, B =>  A =[W + (P * Q) / (Y + X)]



a. Given the following register and memory values, what values do the following ARM instructions load into R0? 
   Assume instructions are not related.

Address 1020 contains 0x40
Address 2030 contains 0x50
R0 contains 0x0020
R1 contains 0x0030
R2 contains 0x1000
R3 contains 0x0020

i) MOV R0, #0x20 => R0 = #0x20
ii) ADD R0, R1, R3 => R0 = 0x0050 
iii) MOV R0, R2, => R0 = 0x1000
iv) LDR R0, [R2, #0x20] => R0 = 0x40

SUB R3, R3, R3

50 - 50 => R3 = 0

AND R3, R3, 0

R3 = 50
R3 = 0

*/