RCC_BASE     EQU 0x40023800
GPIOC_BASE   EQU 0x40020800
TIM3_BASE    EQU 0x40000400
; GPIOC6 
       AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        EXPORT TIM3_Init
        EXPORT PWM6

TIM3_Init
	LDR R0,=RCC_BASE + 0x40 ; APB1ENR
	LDR R1,[R0]
	ORR R1,R1,#1<<1 ; TIM 3 EN
	STR R1,[R0] 
	
	LDR R0,=RCC_BASE + 0x30 ; AHB1ENR
	LDR R1,[R0]
	ORR R1,R1,#1<<2 ; RCC GPIOC EN
	STR R1,[R0]
	; GPIOC6 CHANNEL 1
	LDR R0,=GPIOC_BASE + 0x00 ; MODER
	LDR R1,[R0]
	BIC R1,R1,#3<<12
	ORR R1,R1,#2<<12 ; AF MODE
	STR R1,[R0]
	
	LDR R0,=GPIOC_BASE + 0x20 ; AFL
	LDR R1,[R0]
	ORR R1,R1,#2<<24 ; AF02 MAPPING
	STR R1,[R0]
	
    LDR R0, =TIM3_BASE + 0x2C
    MOVW R1, #999 ; Set auto-reload register to 999
    STR R1, [R0]
		
    LDR R0, =TIM3_BASE + 0x28
    MOVW R1, #15 ; prescaler to 15
    STR R1, [R0]

    LDR R0, =TIM3_BASE + 0x34 ; Set CCR1 to 0
    MOV R1, #0
    STR R1, [R0]

    LDR R0, =TIM3_BASE + 0x18
    LDR R1, [R0]
    BIC R1, R1, #2 << 0 ; Configure CC1 as output
    STR R1, [R0]

    LDR R0, =TIM3_BASE + 0x18
    LDR R1, [R0]
    ORR R1, R1, #6 << 4 ; PWM mode 1
    STR R1, [R0]

    LDR R0, =TIM3_BASE + 0x20 ; CCER
    ORR R1,R1,#1<<0 ; Enable capture
    STR R1, [R0]

    LDR R0, =TIM3_BASE + 0x00
    LDR R1, [R0]
    ORR R1, R1, #1 << 0 ; Enable counter
    STR R1, [R0]

    BX LR

PWM6
    PUSH {R4, LR}         
    LDR R4, =TIM3_BASE + 0x34 ; Load Address from CCR1
    STR R0, [R4]          
    POP {R4, LR}           
    BX LR

    ALIGN
        END
