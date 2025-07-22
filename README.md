# A Comparison of the Arm and RISC-V Architectures on the RP2350 Microcontroller

## Abstract
This thesis compares the M-33 implementation of the Arm ISA with the Hazard3
implementation of the RISC-V ISA on the RP2350 microcontroller chip. It details why this chip, containing two different cores, presents unique opportunities to
learn about their implementation. The two implementations are compared. Custom benchmarks were developed, and existing benchmarks were ported to the Pico
platform to collect performance, power consumption, and binary data about both
core implementations. Our results show that, although ARM benefits from specialized hardware, both implementations perform similarly on real-world benchmarks,
depending on the task. A copy of this thesis is available via the [Lafayette College Digital Repository](https://ldr.lafayette.edu/concern/student_works/cv43nz485)

This repository contains the source code for the thesis. It also contains Python scripts used for data collection, and the PCB design files for the testing board.

## Instructions for Building Pico Benchmarks

### Requirements

- [Pico SDK](https://github.com/raspberrypi/pico-sdk)
- A RISC-V toolchain [(Like CoreV)](https://embecosm.com/downloads/tool-chain-downloads/#core-v-top-of-tree-compilers)

### Building the Benchmarks
To build the benchmarks, you will need to set up the Pico SDK and the RISC-V toolchain. Then follow these steps:
- Clone the repository: `git clone https://github.com/leslier7/thesis.git`
- Navigate to the benchmark directory that you want to build, e.g., `cd thesis/floatmark`
- Make a build directory and navigate into it: `mkdir build-arm && cd build-arm` or `mkdir build-riscv && cd build-riscv`
- Run CMake to configure the build:
  - For Arm: `cmake .. -DPICO_PLATFORM=rp2350 -DARCH=arm`
  - For RISC-V: `cmake .. -DPICO_PLATFORM=rp2350-riscv -DARCH=risc`
- Then build the benchmark with: `make`
- Do this for each benchmark you want to build.

### Running the Benchmarks
- Upload the resulting `.uf2` files to the Pico 2 board by dragging and dropping them onto the board when it is in bootloader mode (hold the BOOTSEL button while plugging in the MicroUSB cable).
- The benchmark will automatically run when the board is powered on. It will output the results to the serial port, which can be read using a terminal program or the provided Python scripts.
  - The TestingPCB has a USB-C port for connecting a serial adapter to a computer 

## Instructions for Running the Scripts

### Requirements
- Python 3.x with the following packages:
  - `numpy`
  - `serial`
  - `csv`
- A Nordic Semi Power Profiler II power measurement device (if measuring power consumption)

### Running the UART Script
- Connect the USB-C port on the testing board to your computer.
- Run the script: `python UartScript.py file_name.csv port_name`
  - Replace `file_name.csv` with the desired output file name (it can be a path).
  - Replace `port_name` with the serial port name (e.g., `/dev/ttyUSB0` on Linux).
- Plug the Micro-USB cable into the Pico 2 board to power it on.
- Unplug and replug the Micro-USB cable to reset the board 10 times to fully test each benchmark.
  - If using the PPK2 to measure the power consumption, toggle the power source in the software 10 times instead.

### Collecting Power Measurements
- Follow the instructions in `Section 4.3.2.4` of the thesis to set up the PPK2 and collect power measurements.

### Running the Power Measurement Script
- Make sure that you have exported the data from the PPK2 software to a CSV file following the instructions in section 4.3.2.4 of the thesis.
- Run the script: `python ChargeScript.py folder_path`
  - Replace `folder_path` with the top level folder containing the CSV files exported from the PPK2 software. It will process all CSV files in all subfolders and put the outputs of each folder in an `Outputs` folder.

## Instructions for the PCB Design Files
The PCB design files are located in the `TestingPCB` directory. They were created using KiCad8. To view or modify them, you will need to install KiCad and open the `.kicad_pro` project file.