# 120 Degree Conduction Six-step Square Wave Drive Mode

This project implements a **six-step square-wave commutation** method to drive a **Surface Permanent Magnet Synchronous Motor (SPMSM)**.  
The motor is controlled using **Hall sensor signals** to generate the drive table for forward (CW) and reverse (CCW) rotation.  


## ⚙️ Hardware Setup

- **Motor**: TECO 56 series 
- **MCU**: TI LAUNCHXL-F28379D 
- **Inverter**: External MOSFET driver board (IRF9540N / IRF540N)  
- **Hall Sensors**: 3-phase digital Hall ICs (S1, S2, S3)  
- **Power Supply**: DC 24 V, up to 10 A


## 🔑 Control Logic

The project uses a **drive table** generated from the Hall sensor signals.  

- Each electrical cycle is divided into **six commutation steps (120° conduction)**.  
- At every step, one phase is driven **High (H)**, one is driven **Low (L)**, and one remains **Floating (X)**.  

### Example: Forward Rotation (CW)

<img width="512" height="384" alt="image" src="https://github.com/user-attachments/assets/1dd2e4cd-571f-49fe-8311-c8ef44f48243" />


| Step | Hall Signal | U | V | W |
|------|-----------------|---|---|---|
| 1    | 001             | X | H | L |
| 2    | 011             | H | X | L |
| 3    | 010             | H | L | X |
| 4    | 110             | X | L | H |
| 5    | 100             | L | X | H |
| 6    | 101             | L | H | X |

### Example: Reverse Rotation (CCW)

<img width="512" height="384" alt="image" src="https://github.com/user-attachments/assets/30ca1a74-363e-44f3-82d9-6ac81d630a60" />


| Step | Hall Signal | U | V | W |
|------|-----------------|---|---|---|
| 1    | 110             | X | L | H |
| 2    | 100             | L | X | H |
| 3    | 101             | L | H | X |
| 4    | 001             | X | H | L |
| 5    | 011             | H | X | L |
| 6    | 010             | H | L | X |

## 🖥️ Code Composer Studio (CCS)

- Default configuration on **program start**:  
  - `direction = 1` → Clockwise (CW) rotation  
  - `brake = 0` → Free running  

- **Control via Expression Window**:  
  - `direction = 0` → Counterclockwise (CCW) rotation  
  - `brake = 1` → Motor brake (stop immediately)  

## Demo



https://github.com/user-attachments/assets/68e10678-4a62-468c-b1b3-9784ab485d10




