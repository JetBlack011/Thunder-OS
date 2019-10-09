; Global offset to use while running in bootsector
[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ; Same offset used during linkage

    mov [BOOT_DRIVE], dl ; BIOS stores boot drive in dl register
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print
    call print_nl

    call load_kernel  ; Load kernel from disk
    call switch_to_pm ; Switch to 32-bit protected mode
    jmp $             ; Never executed

%include "boot/print.asm"
%include "boot/print_hex.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/32bit_print.asm"
%include "boot/switch_pm.asm"

; 16-bit mode to utilise BIOS interrupts
[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    mov bx, KERNEL_OFFSET ; Read from disk and store at 0x1000
    mov dh, 31
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

; Begin 32-bit code section
[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET ; Relinquish control to the kernel
    jmp $ ; Hang execution when kernel finishes


BOOT_DRIVE db 0 ; Store boot drive location in case dl is overwritten
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0
MSG_RETURNED_KERNEL db "Returned from kernel. Error?", 0

; MBR padding and magic word
times 510 - ($-$$) db 0
dw 0xaa55
