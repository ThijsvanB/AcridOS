global _idt_load, _irqdef_handler, ;default calls
global _irq0_handler, _irq5_handler, _irq6_handler, _irq7_handler, _irq9_handler, _irq10_handler, _irq11_handler, _irq12_handler,  _irq13_handler, _irq14_handler, _irq16_handler, _irq17_handler, _irq19_handler, _irq20_handler ;fault handlers
global _irq1_handler, _irq3_handler, _irq4_handler, ;Traps
global _irq8_handler, _irq18_handler, ;abort
global _irq2_handler, _irq32_handler, _irq33_handler ;interrupt handlers
global _irq15_handler, _irq31_handler, ;reserved
global _irq30_handler

extern _idtptr, _exc_def, ;default variable/handler
extern _exc_div0, _exc_debug, _exc_debug, _exc_Break, _exc_overflow, _exc_BRE, _exc_InvOpc, _exc_DNA, _exc_DF, _exc_CSO   ;exception calls
extern _exc_InvTSS, _exc_SNP, _exc_SSF, _exc_gp, _exc_PageFault, _exc_x87FP, _exc_Align, _exc_Machine, _exc_SIMDFloat, _exc_Virt, _exc_Security ;exception calls
extern _int_NMI, _int_pit, _int_kb, ;interrupt calls

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
    call _exc_def
    mov al, 0x20
    out 0x20, al
    RESTORE_REGS
    iret

_irq0_handler:
    SAVE_REGS
    call _exc_div0
    RESTORE_REGS
    iret
   
_irq1_handler:
    SAVE_REGS
    call _exc_debug
    RESTORE_REGS
    iret

_irq2_handler:
    SAVE_REGS
    call _int_NMI
    RESTORE_REGS
    iret

_irq3_handler:
    SAVE_REGS
    call _exc_Break
    RESTORE_REGS
    iret
    
_irq4_handler:
    SAVE_REGS
    call _exc_overflow
    RESTORE_REGS
    iret
    
_irq5_handler:
    SAVE_REGS
    call _exc_BRE
    RESTORE_REGS
    iret
    
_irq6_handler:
    SAVE_REGS
    call _exc_InvOpc
    RESTORE_REGS
    iret
    
_irq7_handler:
    SAVE_REGS
    call _exc_DNA
    RESTORE_REGS
    iret

_irq8_handler:
    SAVE_REGS
    call _exc_DF
    RESTORE_REGS
    iret
    
_irq9_handler:
    SAVE_REGS
    call _exc_CSO
    RESTORE_REGS
    iret
    
_irq10_handler:
    SAVE_REGS
    call _exc_InvTSS
    RESTORE_REGS
    iret

_irq11_handler:
    SAVE_REGS
    call _exc_SNP
    RESTORE_REGS
    iret
    
_irq12_handler:
    SAVE_REGS
    call _exc_SSF
    RESTORE_REGS
    iret
    
_irq13_handler:
    SAVE_REGS
    call _exc_gp
    RESTORE_REGS
    add esp, 4
    iret

_irq14_handler:
    SAVE_REGS
    call _exc_PageFault
    RESTORE_REGS
    iret
    
_irq15_handler:
    iret

_irq16_handler:
    SAVE_REGS
    call _exc_x87FP
    RESTORE_REGS
    iret

_irq17_handler:
    SAVE_REGS
    call _exc_Align
    RESTORE_REGS
    iret

_irq18_handler:
    SAVE_REGS
    call _exc_Machine
    RESTORE_REGS
    iret

_irq19_handler:
    SAVE_REGS
    call _exc_SIMDFloat
    RESTORE_REGS
    iret

_irq20_handler:
    SAVE_REGS
    call _exc_Virt
    RESTORE_REGS
    iret

_irq30_handler:
    SAVE_REGS
    call _exc_Security
    RESTORE_REGS
    iret

_irq31_handler:
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