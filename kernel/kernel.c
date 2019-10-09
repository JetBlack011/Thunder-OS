#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/mem.h"

#include "kernel.h"
#include "shell.h"

#include <stdint.h>

void kernel_main() {
    isr_install();
    irq_install();
    heap_init();
    shell_init();
    clear_screen();

    kprint("Welcome to Thunder-OS!\nType HELP to get started\nThundy-OS> ");
}
