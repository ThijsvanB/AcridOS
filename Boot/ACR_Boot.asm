[bits 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x1000
    mov ah, 0x0e        		;Set a begin message
    mov al, '0'
    int 0x10
          
    mov [BOOT_DRIVE], dl  		;Set location of drive
                                
    mov bp, 0x8000			;Set stack   It's a little above the bootsector
    mov ss, bp
    mov sp, 0xf000
    
    call load_kernel
    
    call switch_to_pm
    
    jmp $

[bits 16]
disk_load:
    push dx
    
    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    
    int 0x13
    
    jc disk_error
    
    pop dx
    cmp dh, al
    jne disk_error
    ret
    
disk_error:
    mov ah, 0x0e
    mov al, 'D'
    int 0x10
    
    jmp $


gdt_start:
    
    
gdt_null:
    dd 0x0
    dd 0x0
    

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0


gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
    
    
gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start
    
    
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


[bits 16]
load_kernel:
    mov ah, 0x0e
    mov al, '1'
    int 0x10
    
    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load
    
    ret

[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
    
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY
    
print_string_pm_loop:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK
            
    cmp al, 0
    je print_string_pm_done
    
    mov[edx], ax
    
    add ebx, 1
    add edx, 2
    
    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret

[bits 16]
switch_to_pm:
    mov ah, 0x0e
    mov al, '2'
    int 0x10

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
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    
    call KERNEL_OFFSET

    jmp $

BOOT_DRIVE db 0
MSG_PROT_MODE db "32 bit mode", 0

TIMES 510 - ($-$$) db 0
DW 0xAA55
