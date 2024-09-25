#include "Flash.h"

/* Flash base address and size, assuming defined in platform_types.h */
#define FLASH_BASE_ADDRESS  0x08000000U
#define FLASH_SIZE          0x00100000U  // 1MB Flash

/* Magic numbers */
#define FLASH_KEY1          0x45670123U
#define FLASH_KEY2          0xCDEF89ABU
#define FLASH_PG_BIT        (1U << 0)
#define FLASH_PER_BIT       (1U << 1)
#define FLASH_START_BIT     (1U << 6)
#define FLASH_BUSY_BIT      (1U << 0)
#define FLASH_LOCK_BIT      (1U << 7)

/**
 * @brief Reads data from flash memory
 * @param address Starting address to read from
 * @param size Number of bytes to read
 * @param data Pointer to store the read data
 */
void Fls_ReadMemory(uint32 address, uint32 size, uint8* data)
{
    /* Ensure address is within valid flash memory range */
    if((address < FLASH_BASE_ADDRESS) || (address > (FLASH_BASE_ADDRESS + FLASH_SIZE)))
    {
        return; // Invalid address, return without doing anything
    }
    
    /* If size is a multiple of 4, read in 32-bit chunks */
    if(size % 4 == 0)
    {
        size /= 4;
        for(uint32 i = 0; i < size; i++)
        {
            *((uint32*)data + i) = *((volatile uint32*)address + i);
        }
    }
    else
    {
        /* Read byte-by-byte if size is not aligned to 32-bit */
        for(uint32 i = 0; i < size; i++)
        {
            *(data + i) = *((volatile uint8*)address + i);
        }
    }
}

/**
 * @brief Unlocks flash memory for writing or erasing
 */
void Fls_Unlock(void)
{
    if(FLASH->CR & FLASH_LOCK_BIT) // If Flash is locked
    {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

/**
 * @brief Writes data to flash memory
 * @param address Starting address in flash memory
 * @param size Size of the data (in bytes)
 * @param data Pointer to the data to be written
 */
void Fls_WriteMemory(uint32 address, uint32 size, const uint8* data)
{
    if(size % 2 != 0) return; // Flash can only write in 16-bit words

    /* Wait if flash is busy */
    while(FLASH->SR & FLASH_BUSY_BIT)
    {
        /* Wait loop */
    }

    /* Unlock flash if it is locked */
    Fls_Unlock();

    /* Enable programming mode */
    FLASH->CR |= FLASH_PG_BIT;

    /* Write data to flash */
    size /= 2; // Convert size to 16-bit words
    for(uint32 i = 0; i < size; i++)
    {
        *((volatile uint16*)address + i) = *((uint16*)data + i);
    }

    /* Wait until flash programming is complete */
    while(FLASH->SR & FLASH_BUSY_BIT)
    {
        /* Wait loop */
    }

    /* Disable programming mode */
    FLASH->CR &= ~FLASH_PG_BIT;
}

/**
 * @brief Erases a sector of flash memory
 * @param address Address within the sector to erase
 */
void Fls_EraseMemory(uint32 address)
{
    /* Wait if flash is busy */
    while(FLASH->SR & FLASH_BUSY_BIT)
    {
        /* Wait loop */
    }

    /* Unlock flash if it is locked */
    Fls_Unlock();

    /* Enable erase mode */
    FLASH->CR |= FLASH_PER_BIT;

    /* Specify the address to erase */
    FLASH->AR = address;

    /* Start the erase operation */
    FLASH->CR |= FLASH_START_BIT;

    /* Wait until the erase is complete */
    while(FLASH->SR & FLASH_BUSY_BIT)
    {
        /* Wait loop */
    }

    /* Disable erase mode */
    FLASH->CR &= ~FLASH_START_BIT;
    FLASH->CR &= ~FLASH_PER_BIT;
}
