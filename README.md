## 🛠️ Tools Used

- 🧠 **MCU**: i.MX RT1050 (EVKB Board)  
- 🧰 **IDE**: **[MCUXpresso IDE v24.12](https://www.nxp.com/design/software/development-tools/mcuxpresso-ide:MCUXpresso-IDE)**
- 🧪 **Oscilloscope**: Agilent Infiniium DSA90254A (20 GSa/s)  
- ⚡ **Hardware Setup**: GPT2 timer + GPIO toggling for latency analysis  

---

## 🚦 Experiments

### 1. Bare Metal Mode
Measures direct ISR response time using GPT2_COMPARE3.

### 2. External GPIO Interrupt
Compares:
- Direct ISR handling
- HAL-based ISR with pin comparison and callback

### 3. FreeRTOS
Uses a high-priority task released by a semaphore from the ISR.

---

### Cloning the Repository
To clone the repository, use the following command:

```bash
git clone https://github.com/jvmreis/nxp_interrupt_lesson.git
```
---
## 📂 Folder Structure

| Path / File                        | Description                                                   |
|------------------------------------|---------------------------------------------------------------|
| `bar_metal/`                       | Bare-metal implementation using GPT2 and GPIO toggle          |
| `free_rtos/`                       | FreeRTOS implementation with semaphore-based context switch   |
| `docs/`                            | Documentation folder containing lab report and diagrams       |
| `.gitattributes`                   | Git attributes file                                           |
| `.gitignore`                       | Git ignore file                                               |

## 📷 How to Enable Disassembly Debugging

In MCUXpresso:

1. Go to **Window > Show View > Other**
2. Search for **Disassembly**
3. Select and open the **Disassembly** view

---

## 📖 Documentation

A full technical lab report is available in PDF and Markdown formats, including:
- Diagrams
- Scope screenshots
- Cycle calculations
- Setup instructions
- **[nxp AN1278 application note](https://www.nxp.com/docs/en/application-note/AN12078.pdf)**
---

## 📌 License

This project is for educational and research purposes only. No commercial license granted.

---

Contributions and feedback are welcome! ⭐


