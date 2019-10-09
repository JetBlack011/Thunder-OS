print:
    pusha

; Loop until null terminator
start:
    mov al, [bx] ; 'bx' is the base address for the string
    cmp al, 0
    je done

	; Print using BIOS interrupts
    mov ah, 0x0e
    int 0x10 ; 'al' already contains the char

    ; increment pointer and loop
    add bx, 1
    jmp start

done:
    popa
    ret



print_nl:
    pusha

    mov ah, 0x0e ; Enter TTY mode
    mov al, 0x0a ; Newline character
    int 0x10
    mov al, 0x0d ; Carriage return
    int 0x10

    popa
    ret
