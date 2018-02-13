

# Buffer Overflow exploits

## How does mem looks like

### memory general layout

0xfff #high memory address:
- [kernel : command line parameters, env variables]
- [stack] :
    - grows in down direction to heap
    - holds local variables of each of functions
    - when call function ie.
- [ *begin* ]
- [ ... ]
- [ *end* ]
- [heap]:
    - grows in up direction to stack
    - allocate large chunks of data like arrays
- [data]:
    - uninitialized and initialized variables go here
- [text]:
    - actual code of program,
    - machine instructions that we compiled are loaded there,
    - read only
    - we dont want to mess up there

0x000 # low memory address

### memory with some function in stack

0xfff:
- [kernel]
- [stack begin]
- [[function]]
- [[parameters: a, b, etc...]]
- [[return: address where main go after strcpy]]
- [stack end]
- [...]
- [heap]
- [...]

0x000


### Simple function buffer overflow

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
    char buf[500];
    strcpy(buf, argv[1]);
    return 0;
}
