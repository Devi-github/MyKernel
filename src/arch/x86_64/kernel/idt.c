#include "idt.h"
#include "panic.h"
#include <string.h>

#define IDT_MAX_DESCRIPTORS 256

struct idt_entry {
    uint16 offset_1;        // offset bits 0..15
    uint16 segment;        // a code segment selector in GDT or LDT
    uint8  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8  type_attributes; // gate type, dpl, and p fields
    uint16 offset_2;        // offset bits 16..31
    uint32 offset_3;        // offset bits 32..63
    uint32 zero;            // reserved
} __attribute__((packed));

struct idt_ptr {
    uint16 size;
    uint64 base;
} __attribute((packed));

struct interrupt_frame
{
    uint64 ip;
    uint16 cs;
    uint16 flags;
    uint16 sp;
    uint16 ss;
} __attribute__((packed));

__attribute__((aligned(0x10)))
static struct idt_entry IDT[IDT_MAX_DESCRIPTORS];
static struct idt_ptr idtr;

typedef void (*isr_t)(struct interrupt_frame *frame); 

extern void* isr_stub_table[];

void exception_handler(uint64 rax) {
    char buffer[256];
    int args[] = { rax };
    vformat(buffer, sizeof(buffer), "Exception occured: %d", (void*)args);

    struct KernelPanicInfo panicInfo = {
        .message = buffer
    };

    kpanic(&panicInfo);
}

void insert_isr(uint8 vector, isr_t routine, uint8 flags) {
    struct idt_entry *entry = &IDT[vector];
    
    entry->offset_1         = (uint64)routine & 0xFFFF;
    entry->segment          = 0x8; // kernel code
    entry->ist              = 0;
    entry->type_attributes  = flags;
    entry->offset_2         = ((uint64)routine >> 16) & 0xFFFF;
    entry->offset_3         = ((uint64)routine >> 32) & 0xFFFFFFF;
    entry->zero             = 0;
}

OsResult load_idt(void) {
    idtr.base = (uint64)&IDT;
    idtr.size = (uint16)sizeof(struct idt_entry) * IDT_MAX_DESCRIPTORS;

    for(uint8 vector = 0; vector < 32; vector++) {
        insert_isr(vector, isr_stub_table[vector], 0x8E);
    }

    asm volatile("lidt %0" : "=m"(idtr));
    asm volatile("sti"); // enable interrupts
    
    return OS_RESULT_SUCCESS;
}
