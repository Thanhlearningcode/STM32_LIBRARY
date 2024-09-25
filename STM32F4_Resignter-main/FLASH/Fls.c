#include "Fls.h"

/* Define macros for magic numbers */
#define FLASH_LOCKED_BIT       (1U << 31)
#define FLASH_READY_BIT        (1U << 16)
#define FLASH_PG_BIT           (1U << 0)
#define FLASH_PER_BIT          (1U << 1)
#define FLASH_START_BIT        (1U << 16)

/**
 * @brief Unlocks the flash memory for programming or erasing.
 */
void Fls_UnlockFunction(void)
{
    if ((FLASH->CR & FLASH_LOCKED_BIT) != 0U) // If Flash is locked
    {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

/**
 * @brief Programs a single byte to the flash memory.
 * @param addr: Address in flash memory to be programmed.
 * @param data: The byte to be written to the flash.
 */
void Fls_ProgrammingFunction(uint32 addr, uint8 data)
{
    /* Wait until flash is ready */
    while ((FLASH->SR & FLASH_READY_BIT) != 0U)
    {
        /* Wait loop */
    }

    /* If Flash is locked, unlock it */
    Fls_UnlockFunction();

    /* Enable programming mode */
    FLASH->CR |= FLASH_PG_BIT;

    /* Program the byte into flash */
    *((volatile uint8*)addr) = data;

    /* Wait for flash programming to complete */
    while ((FLASH->SR & FLASH_READY_BIT) != 0U)
    {
        /* Wait loop */
    }

    /* Disable programming mode */
    FLASH->CR &= ~FLASH_PG_BIT;
}

/**
 * @brief Erases a sector of the flash memory.
 * @param Sector: The sector number to erase.
 */
void Fls_EraseFunction(uint8 Sector)
{
    /* Wait until flash is ready */
    while ((FLASH->SR & FLASH_READY_BIT) != 0U)
    {
        /* Wait loop */
    }

    /* If Flash is locked, unlock it */
    Fls_UnlockFunction();

    /* Select the sector to erase */
    FLASH->CR &= ~(0xFU << 3);            
    FLASH->CR |= ((uint32)Sector << 3) | FLASH_PER_BIT;

    /* Start the erase operation */
    FLASH->CR |= FLASH_START_BIT;

    /* Wait until erase completes */
    while ((FLASH->SR & FLASH_READY_BIT) != 0U)
    {
        /* Wait loop */
    }

    /* Disable the sector erase bit */
    FLASH->CR &= ~FLASH_PER_BIT;
}

/**
 * @brief Reads a single byte from the flash memory.
 * @param addr: Address in flash memory to be read.
 * @return The byte read from flash.
 */
uint8 Fls_ReadFunction(uint32 addr)
{
    return *((volatile uint8*)addr);  // Read byte from Flash
}

/**
 * @brief Programs multiple bytes into flash memory.
 * @param addr: Starting address in flash memory.
 * @param data: Pointer to the data to be written.
 * @param size: Number of bytes to write.
 */
void Fls_ProgrammingMultiByte(uint32 addr, uint8* data, uint32 size)
{
    for (uint32 i = 0; i < size; i++)
    {
        Fls_ProgrammingFunction(addr + i, data[i]);
    }
}
