# ⚙️ bar_metal – Bare-Metal Interrupt Latency Example

This folder contains the **bare-metal implementation** of the interrupt latency measurement experiment for the **i.MX RT1052** microcontroller.

This project serves as the baseline in the **technical lab report** to measure the performance of interrupts in a minimal configuration—**without RTOS or HAL overhead**.

---

## 🧪 Purpose in the Report

This code is used in Section **3.1 – Bare Metal (GPT2)** of the report. It configures the **GPT2_COMPARE3** timer to trigger periodic interrupts and toggles a GPIO pin (`GPIO1_IO19`) inside the ISR. This allows precise latency measurement using an oscilloscope connected to:

- **TP11** – to monitor the GPT2 event  
- **J22 Pin 8** – to monitor the ISR response (GPIO toggle)

The measurements of time `t₁` and `t₂` are converted to clock cycles to evaluate interrupt latency.

---

## 🗂️ Project Structure

Key folders and files:

| Path / File                         | Description                                      |
|------------------------------------|--------------------------------------------------|
| `source/`                          | Contains the main application source code        |
| `board/`                           | Board-level initialization (clocks, pins, etc.)  |
| `drivers/`                         | CMSIS-style drivers for peripherals              |
| `component/`                       | Support modules like debug console               |
| `MIMXRT1052_INT_lesson.mex`        | Project configuration via MCUXpresso Config Tools|
| `Debug/` and `Release/`            | Build output folders                             |
| `MIMXRT1052_INT_lesson.*`          | Launch/debug and project metadata files          |

---

## 🔧 Main File: `source/MIMXRT1052_INT_lesson.c`

This is the main source file used in the report. It includes:

- `GPT2_IRQHandler()`  
  → Toggles the debug GPIO pin inside the ISR.  
- GPT timer setup using GPT2_COMPARE3 in toggle mode.  
- Configuration of GPIO1_IO19 as output for latency tracking.  

You can place a **breakpoint** in `GPT2_IRQHandler()` and use the **Disassembly View** in MCUXpresso to analyze the exact number of cycles executed.

---

## 🧩 Configuration via Macro

The project includes the macro:

```c
#define ISR_GPIO_HAL_COMPARATION 0
```

This allows switching between two interrupt handling strategies:

- **Low-level implementation** (`ISR_GPIO_HAL_COMPARATION == 0`)  
  → Direct register manipulation inside the ISR (faster, leaner).

- **HAL-based implementation** (`ISR_GPIO_HAL_COMPARATION > 0`)  
  → Uses `HAL_GpioInterruptHandle()` to simulate multi-pin processing and callback logic (more realistic, but slower due to overhead).

### To change the behavior:

1. Open `source/MIMXRT1052_INT_lesson.c`  
2. Modify the macro value to `0` or `1`  
3. Rebuild and reflash the firmware

---

## 🚀 How to Use

1. Open **MCUXpresso IDE**
2. Import this project folder using:  
   `File > Import > Existing Projects into Workspace`
3. Connect your **MIMXRT1050-EVKB** board
4. Build and flash the project
5. Connect the oscilloscope:  
   - Channel 1 → TP11 (GPT event)  
   - Channel 2 → J22 Pin 8 (GPIO response)
6. Trigger the oscilloscope and measure latency

**📍 Pin Location on the Board:**  
<p align="center">
  <img src="https://raw.githubusercontent.com/jvmreis/nxp_interrupt_lesson/main/documents/i.MX%20RT1050%20Evaluation%20Kit-pins.png" width="50%">
</p>
---

## 📌 Notes

- System clock is set to **600 MHz**
- GPIOs use **Fast Slew Rate** for improved timing precision
- Refer to Section **3.1** of the lab report for detailed methodology

---

## 📄 License

This code is provided for **academic and research purposes only**
