# C++ Snake (SFML)

A classic Snake game built from scratch in C++ using the Simple and Fast Multimedia Library (SFML). 

## Technical Details
- **Architecture:** Standard 3-phase game loop (Event Polling, State Update, Rendering).
- **State Management:** Continuous movement driven by state vectors, with segmented body propagation.
- **Coordinate Math:** Implemented modulo arithmetic for seamless screen-wrap boundary mechanics.
- **Rendering:** Locked 20x20 mathematical grid overlaid on an 800x600 window.

## How to Run (Linux/WSL)
Requires SFML libraries to be installed.
```bash
g++ main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
./main

<img width="815" height="636" alt="image" src="https://github.com/user-attachments/assets/17850dd7-39cd-491c-a484-ed9eb0714b19" />
