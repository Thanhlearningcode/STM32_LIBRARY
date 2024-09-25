
#ifndef FLASH_H
#define FLASH_H

#include "stm32f10x.h"   
#include "PLATFORM_TYPES.h"

/* Flash Base Address (for STM32F10x) */
#define FLASH_BASE_ADDR      (0x08000000U)

/* Flash Size (32KB for this specific MCU, adjust if needed) */
#define FLASH_SIZE           (0x00008000U)  // 32KB

/* Function Prototypes ------------------------------------------------------------*/
/**
 * \brief Reads data from Flash memory.
 * \param[in] address  Start address in Flash memory
 * \param[in] size     Size of data to read in bytes
 * \param[out] data    Pointer to a buffer where the read data will be stored
 */
void Fls_ReadFlashMemory(uint32_t address, uint32_t size, uint8_t* data);

/**
 * \brief Writes data to Flash memory.
 * \param[in] address  Start address in Flash memory
 * \param[in] size     Size of data to write in bytes (must be aligned properly)
 * \param[in] data     Pointer to the buffer containing data to write
 */
void Fls_WriteFlashMemory(uint32_t address, uint32_t size, const uint8_t* data);

/**
 * \brief Erases a sector of Flash memory.
 * \param[in] address  The address in the Flash sector to erase.
 */
void Fls_EraseFlashMemory(uint32_t address);

/**
 * \brief Unlocks the Flash memory for writing/erasing operations.
 */
void Fls_UnlockSequence(void);

#endif // FLASH_H
