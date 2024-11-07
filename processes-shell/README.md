# Processes Shell

## Overview

In this project, I built a simple Unix shell. I followed all the specification that were outlined in [OSTEP Processes Shell](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/processes-shell). Additionally, I have passed all the test cases. I also have added more commands. For instance,

- **cat**: Concatenates and displays file contents.
- **history**: Displays a list of previously entered commands.

## How to Run the Shell

### 1. Download or Clone the Repository

You can either download the ZIP file from the repository or clone it using Git.

#### Option 1: Clone the Repository
If you have Git installed, you can clone the repository by running:
```bash
git clone <repository-url>
cd Unix-Shell/processes-shell
```

#### Option 2: Download ZIP
If you don’t have Git, download the ZIP file from the repository webpage:
1. Go to the repository on GitHub.
2. Click on **Code** > **Download ZIP**.
3. Extract the downloaded ZIP file, navigate into the `Unix Shell` directory, then enter the `processes-shell` directory.

### 2. Build the Shell
Make sure you are in the `processes-shell` directory, then run:
```bash
make
```

### 3. Run the Shell
After building, you can start the shell by running:
```bash
./wish
```

### 4. Using the Shell
- Enter commands as you would in a standard shell.
- Type `exit` or press `Ctrl+D` to quit the shell.

### 5. Run Tests
To execute tests (if the `test-wish.sh` script is provided and executable), use:
```bash
make test
```

### 6. Clean Up
To remove the executable and any object files, run:
```bash
make clean
```
