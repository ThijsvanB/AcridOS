global _idt_load, _irqdef_handler, _irq0_handler, _irq13_handler, _irq32_handler, _irq33_handler
extern _idtptr, _int_def, _int_div0, _int_pit, _int_kb, _int_gp

%macro	SAVE_REGS 0
	pushad 
	push ds
	push es
	push fs
	push gs 
	push ebx
	mov bx,0x10
	mov ds,bx
	pop ebx
%endmacro

%macro	RESTORE_REGS 0
	pop gs
	pop fs
	pop es
	pop ds
	popad
%endmacro

_idt_load:
    lidt[_idtptr]
    
    ret

_irqdef_handler:
    SAVE_REGS
    call _int_def
    mov al, 0x20
    out 0x20, al
    RESTORE_REGS
    iret

_irq0_handler:
    SAVE_REGS
    call _int_div0
    RESTORE_REGS

_irq13_handler:
    SAVE_REGS
    call _int_gp
    RESTORE_REGS
    add esp, 4
    iret

_irq32_handler:
    SAVE_REGS
    call _int_pit
    mov al, 0x20
    out 0x20, al
    RESTORE_REGS
    iret

_irq33_handler:
    SAVE_REGS
    call _int_kb
    mov al, 0x20
    out 0x20, al
    RESTORE_REGS
    iret