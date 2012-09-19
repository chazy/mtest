#!/usr/bin/python

start_block ="""
.globl bigass_function
    bigass_function:
"""

rept_block = """    mov     r0, pc
    sub     r1, pc, r0
    cmp     r1, #4
    bxne    lr
"""
end_block ="""
    ldr     r2, =bigass_function
    mov     pc, r2
"""

if __name__ == "__main__":
    i = 0;

    print start_block
    while i < 436480:
        print rept_block
        i = i + 1
    print end_block

