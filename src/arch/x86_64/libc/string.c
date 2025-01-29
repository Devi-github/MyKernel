#include "string.h"

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

size_t itoa(int num, char *number)
{
    int dgcount = digit_count(num);
    int index = dgcount - 1;
    char x;

    size_t bytes_written = 0;

    if(num == 0 && dgcount == 1) {
        number[0] = '0';
        number[1] = '\0';
        bytes_written += 2;
    } else {
        while(num != 0) {
            x = num % 10;

            number[index] = x + '0';
            bytes_written++;

            index--;
            num = num / 10;
        }
        number[dgcount] = '\0';
        bytes_written++;
    }

    return bytes_written;
}

size_t itoa64(uint64 num, char *number) {
    int dgcount = digit_count64(num);
    int index = dgcount - 1;
    char x;

    size_t bytes_written = 0;

    if(num == 0 && dgcount == 1) {
        number[0] = '0';
        number[1] = '\0';
        bytes_written += 2;
    } else {
        while(num != 0) {
            x = num % 10;
            
            number[index] = x + '0';
            bytes_written++;

            index--;
            num = num / 10;
        }
        number[dgcount] = '\0';
        bytes_written++;
    }

    return bytes_written;
}

size_t strlen(const char* str) {
    size_t length = 0;
    while(str[length])
        length++;
    return length;
}

void memcpy(void *dst, const void *src, size_t len) {
    // TODO: More efficient implementation may include passing uint32/uint64
    // based on divisibility of length
    for(size_t i = 0; i < len; i++) {
        ((char*)dst)[i] = ((char*)src)[i];
    }
}

size_t vformat(char *buffer, size_t buffer_size, const char *fmt, void *args) {
    size_t bytes_written = 0;
    
    char c;
    size_t i = 0;

    enum FormatState {
        FMT_CHARS, FMT_FORMAT
    } state = FMT_CHARS;

    while((c = fmt[i++]) != '\0') {
        if(bytes_written >= buffer_size) {
            buffer[buffer_size - 1] = '\0';
            break;
            // who cares about buffer overflow if you just don't care
            // TODO: But for real, add a check for every buffer write
        }

        if(state == FMT_CHARS) {
            switch(c) {
                case '%':
                state = FMT_FORMAT;
                break;
                default:
                buffer[bytes_written++] = c;
                break;
            }
        } else {
            const size_t STEP_SIZE = sizeof(size_t);

            char digit_buffer[32];
            size_t len;
            switch(c) {
                case 'i':
                case 'd':
                int32 digit = *(int32*)args;
                args += STEP_SIZE;
                len = itoa(digit, digit_buffer);
                for(size_t j = 0; j < len; j++) {
                    buffer[bytes_written++] = digit_buffer[j];
                }
                break;

                case '%':
                buffer[bytes_written++] = '%';
                break;

                case 's':
                const char *str = *(const char **)args;
                args += STEP_SIZE;
                len = strlen(str);
                memcpy(buffer + bytes_written, str, len);
                bytes_written += len;
                break;

                // TODO: Add more formats.
                default:
                break; // if format invalid, just write nothing
            }
            state = FMT_CHARS;
        }
    }

    buffer[bytes_written++] = '\0';
    return bytes_written;
}
