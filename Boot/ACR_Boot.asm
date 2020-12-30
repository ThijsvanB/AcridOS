[bits 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x1000
    mov [BOOT_DRIVE], dl  		;Set location of drive
                                
    mov bp, 0x8000			;Set stack   It's a little above the bootsector
    mov ss, bp
    mov sp, 0xf000
    
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    
    call load_kernel                    ;Load kernel
    
    call switch_to_pm                   ;Switch to 32 bit mode

[bits 16]
disk_load:
    push dx
    
    mov ah, 0x02
    mov al, 52      ;amount of sectors to read
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    
    int 0x13
    
;   jc disk_error
    
    pop dx
;   cmp dh, al
;   jne disk_error
    ret

gdt_start:
    
    
gdt_null:
    dd 0x0, 0x0
    

gdt_code:
    dw 0xffff, 0x0
    db 0x0, 10011010b, 11001111b, 0x0


gdt_data:
    dw 0xffff, 0x0
    db 0x0, 10010010b, 11001111b, 0x0
    
    
gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start
    
    
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET ;load kernel
    mov dl, [BOOT_DRIVE]
    call disk_load
    
    ret

[bits 16]
switch_to_pm:
    cli
    
    lgdt [gdt_descriptor]
    
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    
    jmp CODE_SEG:init_pm
    

[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ebp, 0x90000
    mov esp, ebp
    
    call BEGIN_PM


[bits 32]  
BEGIN_PM:
    call KERNEL_OFFSET
    
    jmp $

BOOT_DRIVE db 0

TIMES 510 - ($-$$) db 0
DW 0xAA55
