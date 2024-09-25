# STM32F4_Register
#### **Low-Level Register Control for STM32F4 (No HAL)**

### Introduction
Welcome to the **STM32F4_Register** project, a hands-on exploration of **bare-metal programming** on STM32F4 microcontrollers. 
By directly interacting with registers, this project offers a **deeper understanding** of how the STM32F4 microcontroller operates, giving you **maximum control** and allowing for highly **optimized, lightweight code**.

### Why Use Direct Registers?
In many cases, high-level libraries like HAL provide too much abstraction, sacrificing performance and fine-tuned control. This project embraces the **bare-metal** approach:
- **Optimized Performance**: Reduced overhead compared to library-based development.
- **Full Control**: Direct access to the microcontroller's hardware features.
- **Learning Focus**: Perfect for embedded engineers looking to understand STM32 peripherals deeply.

### Project Setup
#### Hardware Requirements
- STM32F4 Microcontroller (Tested on STM32F411)
- ST-Link Programmer for flashing

#### Software Requirements
- **ARM Keil MDK** or **STM32CubeIDE**
- **GNU Arm Embedded Toolchain** for compilation
- **OpenOCD** for flashing and debugging

### How to Use
1. Clone this repository:
   ```bash
   git clone https://github.com/Thanhlearningcode/STM32F4_Register.git
