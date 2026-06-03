## Connect 4 (CLI + SFML GUI)

This project implements the Connect 4 game in C++ with two front ends:

- Command-line interface (CLI)
- Graphical interface (GUI) using SFML 2

The game supports:

- Human vs Human
- Human vs Computer
- Computer vs Human
- Computer vs Computer

The AI player uses minimax with optional alpha-beta pruning and configurable search depth.

## Project Layout

- include/: Header files
- src/: Source files for game logic, players, CLI main, and GUI main
- TESTS/: Catch2 test files
- obj/: Build output directory for object files
- makefile: Build and run targets

## Requirements (Linux)

Install the following tools and libraries:

- g++ (C++ compiler)
- make
- SFML 2 development package

On Ubuntu or Debian:

```bash
sudo apt update
sudo apt install -y g++ make libsfml-dev
```

## Build Instructions

Run all commands from the project root directory.

Build CLI executable:

```bash
make connect4_CLI
```

Build GUI executable:

```bash
make connect4_GUI
```

Build both:

```bash
make connect4_CLI connect4_GUI
```

## Run Instructions

Run CLI version:

```bash
make run_CLI
```

Run GUI version:

```bash
make run_GUI
```

You can also run binaries directly after building:

```bash
./connect4_CLI
./connect4_GUI
```

## GUI Usage

Setup flow:

1. Select game mode.
2. Set AI depth and pruning options (when AI is part of the mode).
3. Click Start game.

During a game:

- Settings are locked.
- Click Stop game to end the current game and return to setup.
- Press R to restart the active game.
- Press ESC to close the window.

## Optional: Tests

Build and run tests:

```bash
make run_tests
```

## Clean Build Artifacts

```bash
make clean
```

