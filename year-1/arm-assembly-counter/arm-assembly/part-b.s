         ;       Q2B

         ;       Data initialization: 10 random numbers (4 bytes each) starting from address 0x2000h.
         ;       These numbers will be randomly changed to test the correctness of your program

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

         ;       Beginning of code for Q2B
         ;       Initialize variables
         mov     r9, #0 ; Initialize r9 to 0 (will accumulate the sum of numbers)
         mov     r10, #0x2000 ; Initialize r10 to point to the start address (0x2000)
         mov     r0, #10 ; Initialize counter for 10 numbers

sum_loop 
         ldr     r11, [r10], #4 ; Load the current number from memory and post-increment r10
         add     r9, r9, r11 ; Accumulate the sum in r9
         subs    r0, r0, #1 ; Decrement counter
         bne     sum_loop ; Repeat until all 10 numbers are summed

         ;       Calculate the exact division by 10 using bit shifting and addition
         mov     r0, r9 ; Move the sum to r0

         ;       Divide by 10 using bit shifts and adds (method to divide r0 by 10)
         mov     r1, r0, lsr #1 ; r1 = r0 / 2
         mov     r2, r0, lsr #2 ; r2 = r0 / 4
         add     r1, r1, r2 ; r1 = r1 + r2 = r0/2 + r0/4
         mov     r2, r1, lsr #4 ; r2 = r1 / 16 = (r0/2 + r0/4) / 16
         add     r1, r1, r2 ; r1 = r1 + r2
         mov     r2, r1, lsr #8 ; r2 = r1 / 256
         add     r1, r1, r2 ; r1 = r1 + r2
         mov     r2, r1, lsr #16 ; r2 = r1 / 65536
         add     r0, r1, r2 ; r0 = r1 + r2
         mov     r0, r0, lsr #3 ; r0 = r0 / 8

         ;       At this point, r0 contains the exact average
         ;       Store the average at memory address 0x2150
         ldr     r8, =0x2150 ; Load the address 0x2150 into r8
         str     r0, [r8] ; Store the average value at address 0x2150

         ;       End of program
