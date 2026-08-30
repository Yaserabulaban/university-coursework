            ;data   initialization. 10 random no (4 byte each stored starting from address 0x2000h).
            ;       These numbers will be randomly changed to test the correctness of your program
            ;       Yaser E H Abulaban, 1221305612
            ;       Wan Hani Ilyana Binti Wan Izhan, 1211111738
            ;       ⁠Nur Iman Binti Mohd Shahrel Faizal, 1211111293
            ;       Hani Insyirah binti Edrin Nazri, 1211112129

            ;       Input Data 1
            mov     r0,#0x11000000
            mov     r1,#0x00110000
            mov     r2,#0x00001100
            mov     r3,#0x00000011
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            mov     r8,#0x2000
            str     r0, [r8]

            ;       Input Data 2 - move r0,#0x22223333
            mov     r0,#0x22000000
            mov     r1,#0x00220000
            mov     r2,#0x00003300
            mov     r3,#0x00000033
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            str     r0, [r8,#4]

            ;       Input Data 3 - move r0,#0x31111111
            mov     r0,#0x31000000
            mov     r1,#0x00110000
            mov     r2,#0x00001100
            mov     r3,#0x00000011
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            str     r0, [r8,#8]

            ;       Input Data 4 - move r0,#0x42223333
            mov     r0,#0x42000000
            mov     r1,#0x00220000
            mov     r2,#0x00003300
            mov     r3,#0x00000033
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            str     r0, [r8,#12]

            ;       Input Data 5 - move r0,#0x51111111
            mov     r0,#0x51000000
            mov     r1,#0x00110000
            mov     r2,#0x00001100
            mov     r3,#0x00000011
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            str     r0, [r8,#8]
            str     r0, [r8,#16]

            ;       Input Data 6 - move r0,#0x62223333
            mov     r0,#0x62000000
            mov     r1,#0x00220000
            mov     r2,#0x00003300
            mov     r3,#0x00000033
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            str     r0, [r8,#12]
            str     r0, [r8,#20]

            ;       Input Data 7 - move r0,#0x71111111
            mov     r0,#0x71000000
            mov     r1,#0x00110000
            mov     r2,#0x00001100
            mov     r3,#0x00000011
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            str     r0, [r8,#24]

            ;       Input Data 8 - move r0,#0x82223333
            mov     r0,#0x82000000
            mov     r1,#0x00220000
            mov     r2,#0x00003300
            mov     r3,#0x00000033
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            str     r0, [r8,#28]

            ;       Input Data 9 - move r0,#0x91111111
            mov     r0,#0x91000000
            mov     r1,#0x00110000
            mov     r2,#0x00001100
            mov     r3,#0x00000011
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            str     r0, [r8,#32]

            ;       Input Data 10 - move r0,#0xA2223333
            mov     r0,#0xA2000000
            mov     r1,#0x00220000
            mov     r2,#0x00003300
            mov     r3,#0x00000033
            add     r0, r0, r1
            add     r0, r0, r2
            add     r0, r0, r3
            str     r0, [r8,#36]


            ;       Beginning of code for Q2A
            MOV     R8, #0x2000 ; Base address of data
            LDR     R0, [R8] ; Load the first value
            MOV     R1, R0 ; Assume first value is the smallest


            MOV     R9, #10 ; Number of elements
            MOV     R2, #4 ; Offset increment
            MOV     R3, #1 ; Loop counter

FIND_MIN    
            ADD     R8, R8, R2 ; Move to next data location
            LDR     R0, [R8] ; Load the next value
            CMP     R0, R1 ; Compare with current smallest
            BGE     SKIP_UPDATE ; If greater or equal, skip update
            MOV     R1, R0 ; Update smallest value

SKIP_UPDATE 
            ADD     R3, R3, #1 ; Increment loop counter
            CMP     R3, R9 ; Compare with number of elements
            BLT     FIND_MIN ; Loop if not done


            MOV     R8, #0x2100 ; Result address
            STR     R1, [R8] ; Store the smallest value

            end