; Author: NGUYEN VAN THANH
RCC_BASE           EQU 0x40023800
RCC_AHB1ENR_OFFSET EQU 0x30
RCC_AHB1ENR        EQU RCC_AHB1ENR_OFFSET + RCC_BASE

GPIOD_BASE         EQU 0x40020C00 
GPIOD_MODER        EQU GPIOD_BASE + 0x00
GPIOD_OTYPER       EQU GPIOD_BASE + 0x04
GPIOD_OSPEEDR      EQU GPIOD_BASE + 0x08
GPIOD_PUPDR        EQU GPIOD_BASE + 0x0C
GPIOD_ODR          EQU GPIOD_BASE + 0x14

MODER15_OPP        EQU 1<<30  ; Mode output_pushpull
ONESECOND          EQU 1000000

      AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        EXPORT __main

__main
        ; Enable GPIOD Clock
        LDR R0, =RCC_AHB1ENR
        LDR R1, [R0]
        ORR R1, R1, #1<<3    ; RCC->AHB1ENR |= (1<<3)
        STR R1, [R0]

        ; Configure GPIOD Pin 1 as Output
        LDR R0, =GPIOD_MODER
        LDR R1, [R0]
        ORR R1, R1, #1<<2    ; GPIOD->MODER |= (1<<2) for Pin 1
        STR R1, [R0]

        ; Configure GPIOD Pin 1 as Push-Pull
        LDR R0, =GPIOD_OTYPER 
        LDR R1, [R0]
        BIC R1, R1, #1<<1    ; GPIOD->OTYPER &= ~(1<<1)
        STR R1, [R0]

        ; Configure GPIOD Pin 2 as Input
        LDR R0, =GPIOD_MODER
        LDR R1, [R0]
        BIC R1, R1, #3<<4    ; GPIOD->MODER &= ~(3<<4) for Pin 2
        STR R1, [R0]

        ; Configure Pull-Up for GPIOD Pin 2
        LDR R0, =GPIOD_PUPDR 
        LDR R1, [R0]
        BIC R1, R1, #3<<4    ; Clear Pull-Up/Pull-Down bits for Pin 2
        ORR R1, R1, #1<<4    ; Set Pull-Up for Pin 2
        STR R1, [R0]

LOOP
      ; TURN ON
        LDR R0, =GPIOD_ODR
        MOVW R1, #1<<1
        STR R1, [R0]
		
        ; Delay Loop
        LDR R2, =ONESECOND
DELAY
        SUBS R2, R2, #1
        BNE DELAY
	;TURN OFF
		LDR R2,=GPIOD_ODR
		LDR R1,[R0]
		BIC R1,R1,#1<<1
		STR R1,[R2]
		 LDR R2, =ONESECOND
DELAY1
        SUBS R2, R2, #1
        BNE DELAY1
        B LOOP
		ALIGN
        END
