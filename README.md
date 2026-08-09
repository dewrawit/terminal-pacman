# Terminal Pac-Man

A terminal-based Pac-Man game written in **C++23**.

This project is a recreation of the classic Pac-Man gameplay, implemented from scratch as a way to practice object-oriented programming, polymorphism, game-state management, AI, and C++ software design.

The game runs entirely in the terminal using ASCII characters and ANSI escape codes for color.

## Features

* Classic Pac-Man style maze
* Pac-Man movement and pellet collection
* Normal and power pellets
* Lives and respawn system
* Global timer affecting ghost mode (Scatter-mode, Chase-mode)
* Four unique ghosts:

  * **Blinky** — directly targets Pac-Man
  * **Pinky** — targets a position ahead of Pac-Man
  * **Inky** — uses a vector-based targeting algorithm
  * **Clyde** — switches between chasing Pac-Man and scattering
* Persistent high-score leaderboard

## Limitations

* The game is **turn-based** rather than real-time.
* Ghost movement and Pac-Man movement occur one turn at a time.

## Requirements

* **C++23 compatible compiler**
* Linux: `g++`
* Windows: `g++` through a MinGW/MSYS2 environment

## Compilation

### Linux

Open a terminal and navigate to the project directory:

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion core/*.cpp ghosts/*.cpp -o main
```

Then run:

```bash
./main
```

### Windows

Open a MinGW/MSYS2 terminal and navigate to the project directory.

Compile with:

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion core/*.cpp ghosts/*.cpp -o main.exe
```

Then run:

```bash
./main.exe
```

## Controls

| Key | Action     |
| --- | ---------- |
| `W` | Move Up    |
| `A` | Move Left  |
| `S` | Move Down  |
| `D` | Move Right |

## About the Project

Terminal Pac-Man is my second major C++ project.

The project was developed incrementally, with a focus on learning software architecture rather than simply making the game work. During development, the architecture was refactored when design decisions caused problems, particularly around separating the static board terrain from dynamic entities and rendering.

The project also served as practical experience with:

* Object-oriented programming
* Inheritance and polymorphism
* Smart pointers
* Game state management
* State machines
* Basic game AI
* Collision handling
* File I/O and persistent data
* Git and GitHub
* Debugging and refactoring

## Status

**Complete — v1.0**