# 🧵 `free_rtos` – Interrupt Latency with FreeRTOS (i.MX RT1052)

This folder contains the **FreeRTOS-based implementation** of the interrupt latency experiment for the **NXP i.MX RT1052** microcontroller.

This project complements the **technical lab report** by demonstrating the impact of **context switching latency** introduced by an RTOS kernel.

---

## 🧪 Purpose in the Report

This code is used in Section **3.3 – FreeRTOS with Semaphore** of the report.  
Instead of toggling the GPIO pin directly inside the ISR, the ISR **releases a semaphore**, and a **high-priority task** performs the GPIO toggle. This design simulates a **typical multitasking environment**.

### Timing flow:

- ISR triggered by **GPT2_COMPARE3**
- Semaphore is released (`xSemaphoreGiveFromISR`)
- Task is unblocked and scheduled
- Task toggles `GPIO1_IO19` → Measured on the oscilloscope

---

## 🗂️ Project Structure

| Path / File                            | Description                                           |
|----------------------------------------|-------------------------------------------------------|
| `source/`                              | Application source files including ISR and tasks     |
| `freertos/`                            | FreeRTOS kernel source and configuration              |
| `board/`, `startup/`, `drivers/`       | MCU and board-specific initialization                 |
| `component/`                           | Middleware and utility modules (e.g. debug console)   |
| `evkbimxrt1050_freertos_sem.mex`       | MCUXpresso Config Tools configuration file            |
| `Debug/`                               | Build output folder                                   |
| `evkbimxrt1050_freertos_sem.*`         | Project metadata, debug launch files, etc.            |

---

## 🔧 Main File: `source/MIMXRT1052_INT_lesson.c`

This file contains the key logic for the experiment:

```c
void GPT2_IRQHandler(void)
{
    GPT2->SR = GPT_OC3_FLAG;  // Clear GPT interrupt flag
    xSemaphoreGiveFromISR(xSemaphore_consumer, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    __DSB();  // Ensure memory write completion
}
```

- The ISR only signals a task (non-blocking)
- The task `producer_task` toggles the debug GPIO (`GPIO1_IO19`)
- The ISR–task transition time reflects **RTOS context switch latency**

---

## 🚀 How to Use

1. Open **MCUXpresso IDE**
2. Import this project:  
   `File > Import > Existing Projects into Workspace`
3. Build the project
4. Flash to the **MIMXRT1050-EVKB** board
5. Connect the oscilloscope:  
   - **Channel 1** → TP11 (GPT2 event trigger)  
   - **Channel 2** → J22 Pin 8 (GPIO toggled by task)
6. Trigger on channel 1 and measure the time delay until channel 2 rises


**📍 Pin Location on the Board:**  
<p align="center">
  <img src="https://raw.githubusercontent.com/jvmreis/nxp_interrupt_lesson/main/documents/i.MX%20RT1050%20Evaluation%20Kit-pins.png" width="50%">
</p>

---

## 🧩 Latency Analysis

- The delay between ISR and task execution reveals the **cost of context switching**
- Section **3.3** of the lab report explains how `t₁`, `t₂`, and `t₃` are measured and converted to clock cycles
- Typical observed delay: ~1100 cycles for FreeRTOS with semaphore

---

## 📌 Notes

- Clock: **600 MHz**
- GPT2_COMPARE3 generates periodic interrupts
- Task is created with **highest priority** to minimize interference
- Ideal for analyzing **real-time behavior with preemptive multitasking**

---

## 📄 License

This project is provided for **educational and research purposes only**
