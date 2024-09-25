RCC_BASE         EQU 0x40023800
RCC_AHB1ENR      EQU RCC_BASE + 0x30    
GPIOC_BASE       EQU 0x40020800
GPIOC_MODER      EQU GPIOC_BASE + 0x00
GPIOC_OTYPER     EQU GPIOC_BASE + 0x04
GPIOC_PUPDR      EQU GPIOC_BASE + 0x0C
GPIOC_ODR        EQU GPIOC_BASE + 0x14
GPIOC_IDR        EQU GPIOC_BASE + 0x10  

        AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        EXPORT __main

__main
; RCC GPIOC ENABLE
        LDR R0, =RCC_AHB1ENR
        LDR R1, [R0]
        ORR R1, R1, #1 << 2  ; Enable GPIOC clock (bit 2 for GPIOC)
        STR R1, [R0]

; GPIOC PIN7 OUTPUT
        LDR R0, =GPIOC_MODER
        LDR R1, [R0]
        BIC R1, R1, #3 << 14 ; Clear mode for pin 7
        ORR R1, R1, #1 << 14 ; Set pin 7 as output
        STR R1, [R0]

; GPIOC PIN13 INPUT
        LDR R0, =GPIOC_MODER
        LDR R1, [R0]
        BIC R1, R1, #3 << 26 ; Clear mode for pin 13
        STR R1, [R0]         ; Set pin 13 as input

        LDR R0, =GPIOC_PUPDR
        LDR R1, [R0]
        BIC R1, R1, #3 << 26 ; Clear pull-up/pull-down for pin 13
        ORR R1, R1, #1 << 26 ; Enable pull-up for pin 13
        STR R1, [R0]

        
LOOP
        LDR R0, =GPIOC_IDR   
        LDR R1, [R0]        ; Read value from GPIOC_IDR
        TST R1, #1 << 13    ; Test if bit 13 (PC13) is set
        BEQ LED_ON        
        B LED_OFF           

LED_ON
        LDR R0, =GPIOC_ODR  
        LDR R1, [R0]        
        ORR R1, R1, #1 << 7 ; Set bit 7 (PC7) to turn on LED
        STR R1, [R0]        ; Write back to GPIOC_ODR
        B LOOP             

LED_OFF
        LDR R0, =GPIOC_ODR  
        LDR R1, [R0]       
        BIC R1, R1, #1 << 7 ; Clear bit 7 (PC7) to turn off LED
        STR R1, [R0]        ; Write back to GPIOC_ODR
        B LOOP              


                   
        END
