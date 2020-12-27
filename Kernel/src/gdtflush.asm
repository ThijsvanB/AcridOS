global _gdt_flush, _set_gdt

gdtr DW 0
    DD 0

_set_gdt:
    mov eax, [esp + 4]
    mov [gdtr + 2], eax
    mov ax, [esp + 8]
    mov [gdtr], ax
    lgdt[gdtr]
    ret

_gdt_flush:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush
    
flush:
    ret