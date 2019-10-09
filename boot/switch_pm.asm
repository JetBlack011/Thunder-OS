[bits 16]
switch_to_pm:
    cli                   ; 1. Disable BIOS interrupts
    lgdt [gdt_descriptor] ; 2. Load the GDT with predefined descriptor
    mov eax, cr0
    or eax, 0x1           ; 3. Set 32-bit mode bit in cr0
    mov cr0, eax
    jmp CODE_SEG:init_pm  ; 4. Far jump to different segment to clear pipeline

[bits 32]
init_pm: ; Enter 32-bit protected mode
    mov ax, DATA_SEG      ; 5. Update the segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000      ; 6. Update stack to top of usable memory
    mov esp, ebp

    call BEGIN_PM         ; 7. Call a well-known label 32-bit code
