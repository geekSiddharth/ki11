# ki11 : A simple shell for Assignment 0

**Name**: Siddharth Yadav  
**Roll Number**: 2016268

## Usage

```
cd 2016268/src
make all
./ki11
```

**Note**: Make sure that while running ki11, `src` must your current directory.  
To delete the executable binaries, use `make clean` in `src` dir

### External Commands 

- ls
    - -a: all, do not ignore entries starting with .
    - -A: almost all,   do not list implied . and .. 
    - -f: do not sort
    
    Error handling:
    - doing ls with a file gives error
    - doing ls with an unknown or an inaccessible directory  gives error
    - `ls ` shows current directory  
    - -A has greater preference than -a. Any option of input will work
    - no error in case of bad arguments 
    
- cat
    - -E : number all output lines
    - -n : display $ at beginning of each line
    
    Error handling: 
    - folder given as an input
    - unknown or an inaccessible file given as input
    - any order of options and input will work
    - no error in case of bad arguments 
- date
    - -u : output UTC/universal time
    - -R : output date and time in RFC 2822 format.  Example: Mon, 14 Aug 2006 02:34:56 -0600
    
     Error handling: 
     - throws error in case of bad arguments 
     - `date` shows local time in the format `%a %b %d %H:%M:%S %Z %Y`
     - any order of options are valid and they work
- rm
    - -r: remove directories and their contents recursively
    - -f: ignore nonexistent files and arguments, never prompt
    - -d: remove empty directories
    
    Error handling:
    - respective options of rm do there respective task. If used of other purpose, error is thrown
        - -r does't delete folder
        - -d only deletes empty directory
    - error thrown in case we don't have rights to rm the given file/folder
    - order does't matter
    
- mkdir
    - -p : no error if existing, make parent directories as needed
    - -v : print a message for each created directory
    
    Error handling:
    - error given in case dir already exists and -p is not used
    - error given in case of making nested dirs without using -p
    - order of options given does't matter 
    

### Internal Commands

- cd
    - `cd`, `cd -`, `cd ~` work
    - `cd  ` is equivalent to `cd ~` which is equivalent to changing dir to $HOME 
    - `cd -` goes to previous directory
        -P    Do not follow symbolic links
        -L    Follow symbolic links (default)
    
    Error handling:  
        - `cd -` gives error if cd has not been used before  
        - cd to file or an unknown dir gives an error
- pwd    
      print name of current/working directory
- history
    - `history x` displays last x commands
    - -c : Clear the history list/file
    - -a : Append the new history lines (history lines entered since the beginning of the current Bash session) to the history file.    
        Usage: `history -a <file_name>`. the content of the file will be append to the history file
    
    Error handling: 
    - The file given in case of -a should be accessible and known, otherwise error is thrown
    - In case of `history x`, if the x is greater than number of commands in the history file, then no error is thrown and available stuffs are shown
- echo  
    It simply prints the what is given in front of it. 
    - removes pairwise`"` and  `'`
    - -E : (default option) disable escape sequence processing
    - prints any other options as if it was an input  
- exit  
      cause normal process termination
