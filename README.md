# Unix Shell




In this project, I built a simple UNIX shell. I followed all the specifications outlined in the [OSTEP Processes Shell](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/processes-shell). I have also added more commands, such as:

- **cat**: Concatenates and displays file contents.
- **history**: Displays a list of previously entered commands.  

The program have passed all the test cases. 


## How to Run the Shell

### 1. Download or Clone the Repository

You can either download the ZIP file from the repository or clone it using Git.

#### Option 1: Clone the Repository
```bash
git clone https://github.com/trinhnguyen1810/Unix-Shell.git
cd Unix-Shell/processes-shell
```

#### Option 2: Download ZIP
 Extract the downloaded ZIP file, navigate into the `Unix-Shell` directory, then enter the `processes-shell` directory.

### 2. Build the Shell
Once you have the repository set up locally, make sure you are in the `Unix-Shell/processes-shell` directory, then run the `make` command to build the shell:
```bash
make
```
This will compile all the necessary source files and generate the executable `wish`.

### 3. Run the Shell
After building the shell, you can start the shell by running:
```bash
./wish
```
This will open an interactive shell where you can start typing commands.

### 4. Using the Shell
- You can enter commands as you would in a standard Unix shell.
- For instance, you can run `cat` to display file contents, or use `history` to see the list of previous commands.
- To exit the shell, type `exit` or press `Ctrl+D`.

### 5. Run Tests
If the `test-wish.sh` script is provided and executable, you can run it to verify the functionality of your shell:
```bash
make test
```
This will execute the test cases and display the results.

### 6. Clean Up
To remove the executable and any object files generated during the build process, run:
```bash
make clean
```
This will ensure your project directory is clean and free of unnecessary files.
