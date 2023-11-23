#include "stdio_myos.h"

#include "kernel.h"

#include "keyboard.h"
#include "char.h"

// VGA interface information structure
typedef struct VGAInfo {
    // Index VGA cursor is currently at
    uint32 vga_index;
    // Next line index
    uint32 next_line_index;
    // Foreground color
    uint8 g_fore_color;
    // Background color
    uint8 g_back_color;
    // Buffer pointer
    uint16* vga_buffer;
} VGAInfo;

VGAInfo info;

uint16 vga_entry(uint8 ch, uint8 fore_color, uint8 back_color) {
    uint16 ax = 0;
    uint8 ah = 0, al = 0;

    ah = back_color;
    ah <<= 4;
    ah |= fore_color;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}
void set_color(uint8 fr, uint8 bg) {
    info.g_fore_color = fr;
    info.g_back_color = bg;
}
void putc(FILE *f, char c)
{
    if(f == stdout) {
        print_char(c);
        return;
    }
    f->write(c);
}
void puts(FILE *f, const char *str)
{
    size_t len = strlen(str);
    for(size_t i = 0; i < len; i++) {
        putc(f, str[i]);
    }
}
void set_cursor(uint32 index)
{
    info.vga_index = index;
    info.next_line_index = info.vga_index / 80 + 1;
}
void set_cursor_coord(uint32 x, uint32 y) {
    info.vga_index = x + y * 80;
    info.next_line_index = y + 1;
}
void clear_vga_buffer(uint16** buffer, uint8 fore_color, uint8 back_color) {
    uint32 i;
    for(i = 0; i < BUFSIZE; i++) {
        (*buffer)[i] = vga_entry(0, fore_color, back_color);
    }
    info.next_line_index = 1;
    info.vga_index = 0;
}

void init_vga(uint8 fore_color, uint8 back_color) {
    info.vga_buffer = (uint16*)VGA_ADDRESS;
    clear_vga_buffer(&info.vga_buffer, fore_color, back_color);
    info.g_fore_color = fore_color;
    info.g_back_color = back_color;
}
void print_new_line() {
    if(info.next_line_index >= 55) {
        info.next_line_index = 0;
        clear_vga_buffer(&info.vga_buffer, info.g_fore_color, info.g_back_color);
    }
    info.vga_index = 80*info.next_line_index;
    info.next_line_index++;
}
void print_char(char ch) {
    if(ch == '\n') {
        print_new_line();
        return;
    }
    info.vga_buffer[info.vga_index] = vga_entry(ch, info.g_fore_color, info.g_back_color);
    info.vga_index++;
}
size_t strlen(const char* str) {
    size_t length = 0;
    while(str[length])
        length++;
    return length;
}
uint32 digit_count( int num) {
    uint32 count = 0;
    if(num == 0)
        return 1;
    while(num > 0) {
        count++;
        num = num / 10;
    }
    return count;
}
uint32 digit_count64(uint64 num) {
    uint32 count = 0;
    if(num == 0)
        return 1;
    while(num > 0) {
        count++;
        num = num / 10;
    }
    return count;
}
void itoa(int num, char *number)
{
    int dgcount = digit_count(num);
    int index = dgcount - 1;
    char x;

    if(num == 0 && dgcount == 1) {
        number[0] = '0';
        number[1] = '\0';
    } else {
        while(num != 0) {
            x = num % 10;
            number[index] = x + '0';
            index--;
            num = num / 10;
        }
        number[dgcount] = '\0';
    }
}
void itoa64(uint64 num, char *number) {
    int dgcount = digit_count64(num);
    int index = dgcount - 1;
    char x;

    if(num == 0 && dgcount == 1) {
        number[0] = '0';
        number[1] = '\0';
    } else {
        while(num != 0) {
            x = num % 10;
            number[index] = x + '0';
            index--;
            num = num / 10;
        }
        number[dgcount] = '\0';
    }
}
void print_int(uint32 num) {
    char str_num[digit_count(num)+1];
    itoa(num, str_num);
    print_string(str_num);
}
void print_long(uint64 num) {
    char str_num[digit_count64(num)+1];
    itoa64(num, str_num);
    print_string(str_num);
}
void print_string(char *str)
{
    uint32 index = 0;
    while(str[index]){
        print_char(str[index]);
        index++;
    }
}

uint8 inb(uint16 port)
{
    uint8 ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

void outb(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

char get_input_keycode()
{
    char ch = 0;
    while((ch = inb(KEYBOARD_PORT)) != 0) {
        if(ch > 0)
            return ch;
    }
    return ch;
}

char getc(FILE *f)
{
    if(f == stdin) {
        return get_ascii_char(get_input_keycode());
    }
    char ch = 0;
    while((ch = f->read()) != EOF) {
        if(ch > 0)
            return ch;
    }
    return 0;
}

void wait_for_io(uint32 timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

void sleep(uint32 timer_count)
{
  wait_for_io(timer_count);
}
/*
void test_input()
{
  char ch = 0;
  char keycode = 0;
  bool first = false;
  char k = get_input_keycode();
  do{
    keycode = get_input_keycode();
    if(keycode == KEY_ENTER){
      print_new_line(info);
    } else{
      ch = get_ascii_char(keycode);
      print_char(ch);
    }
    if(first)
      sleep(0x009FFFFF);
    else {
      sleep(0x0FFFFFFF);
      first = true;
    }
  }while(ch > 0);
}*/
