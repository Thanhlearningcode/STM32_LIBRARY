; Author: Nguyen Van Thanh

RCC_BASE     EQU 0x40023800
GPIOA_BASE   EQU 0x40020000
SPI1_BASE    EQU 0x40013000

	AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT SPI1_Init

SPI1_Init
	; Enable GPIOA Clock (RCC AHB1ENR)
	LDR R0, =RCC_BASE + 0x30  ; Load address of AHB1ENR
	LDR R1, [R0]               ; Read the current value of AHB1ENR
	ORR R1, R1, #1             ; Set the bit for GPIOA 
	STR R1, [R0]               ; Write back to enable GPIOA clock

	; Enable SPI1 Clock (RCC APB2ENR)
	LDR R0, =RCC_BASE + 0x44   ; Load address of APB2ENR
	LDR R1, [R0]               ; Read the current value of APB2ENR
	ORR R1, R1, #1 << 12       ; Set the bit for SPI1 
	STR R1, [R0]               ; Write back to enable SPI1 clock

	; SPI1 CR1 Configuration
	LDR R0, =SPI1_BASE + 0x00  ; Load address of SPI1 CR1

	; Configure SPI1 in master mode, 8-bit data, full-duplex, CPOL = 0, CPHA = 0
	LDR R1, [R0]
	
	BIC R1, R1, #(1 << 11)     ; Set to 8-bit data format
	BIC R1, R1, #(1 << 10)     ; Full duplex (Transmit and receive)
	ORR R1, R1, #(1 << 9)      ; Software slave management enabled
	ORR R1, R1, #(1 << 8)      ; Internal slave select
	BIC R1, R1, #(1 << 7)      ; MSB first
	ORR R1, R1, #(1 << 3)      ; Baud rate control: Fpclk/4
	ORR R1, R1, #(1 << 2)      ; Master mode configuration
	ORR R1, R1, #0x3           ; CPOL = 0, CPHA = 0 (standard SPI mode)
	
	STR R1, [R0]               ; Write configuration back to SPI1 CR1

	; Enable SPI1
	LDR R1, [R0]
	ORR R1, R1, #(1 << 6)      ; Set SPE (SPI Enable) bit to enable SPI
	STR R1, [R0]               ; Write back to SPI1 CR1 to enable SPI
	
	BX LR                      ; Return from function

	ALIGN
	END
