#include <stdarg.h>

#include "types.h"
#include "sbi.h"

static char digits[] = "0123456789abcdef";

static void printint(uint32_t xx, int base, int sign) {
  char buf[16];
  int i;
  uint32_t x;

  if (sign && ((sign = (xx < 0))))
    x = -xx;
  else
    x = xx;

  i = 0;
  do {
    buf[i++] = digits[x % base];
  } while ((x /= base) != 0);

  if (sign)
    buf[i++] = '-';

  while (--i >= 0)
    putchar(buf[i]);
}

static void printptr(uint32_t x) {
  uint32_t i;
  putchar('0');
  putchar('x');
  for (i = 0; i < (sizeof(uint32_t) * 2); i++, x <<= 4)
    putchar(digits[x >> (sizeof(uint32_t) * 8 - 4)]);
}

int printf(char *fmt, ...) {
  va_list ap;
  int cx, c2;
  char *s;

  va_start(ap, fmt);
  for (int i = 0; (cx = fmt[i] & 0xff) != 0; i++) {
    if (cx != '%') {
      putchar(cx);
      continue;
    }
    i++;
    int c0 = fmt[i + 0] & 0xff;
    int c1 = c2 = 0;
    if (c0) c1 = fmt[i + 1] & 0xff;
    if (c1) c2 = fmt[i + 2] & 0xff;
    if (c0 == 'd') {
      printint(va_arg(ap, int), 10, 1);
    } else if (c0 == 'l' && c1 == 'd') {
      printint(va_arg(ap, uint32_t), 10, 1);
      i += 1;
    } else if (c0 == 'l' && c1 == 'l' && c2 == 'd') {
      printint(va_arg(ap, uint32_t), 10, 1);
      i += 2;
    } else if (c0 == 'u') {
      printint(va_arg(ap, int), 10, 0);
    } else if (c0 == 'l' && c1 == 'u') {
      printint(va_arg(ap, uint32_t), 10, 0);
      i += 1;
    } else if (c0 == 'l' && c1 == 'l' && c2 == 'u') {
      printint(va_arg(ap, uint32_t), 10, 0);
      i += 2;
    } else if (c0 == 'x') {
      printint(va_arg(ap, int), 16, 0);
    } else if (c0 == 'l' && c1 == 'x') {
      printint(va_arg(ap, uint32_t), 16, 0);
      i += 1;
    } else if (c0 == 'l' && c1 == 'l' && c2 == 'x') {
      printint(va_arg(ap, uint32_t), 16, 0);
      i += 2;
    } else if (c0 == 'p') {
      printptr(va_arg(ap, uint32_t));
    } else if (c0 == 's') {
      if ((s = va_arg(ap, char*)) == 0)
        s = "(null)";
      for (; *s; s++)
        putchar(*s);
    } else if (c0 == '%') {
      putchar('%');
    } else if (c0 == 0) {
      break;
    } else {
      // Print unknown % sequence to draw attention.
      putchar('%');
      putchar(c0);
    }

#if 0
    switch(c){
    case 'd':
      printint(va_arg(ap, int), 10, 1);
      break;
    case 'x':
      printint(va_arg(ap, int), 16, 1);
      break;
    case 'p':
      printptr(va_arg(ap, uint32_t));
      break;
    case 's':
      if((s = va_arg(ap, char*)) == 0)
        s = "(null)";
      for(; *s; s++)
        putchar(*s);
      break;
    case '%':
      putchar('%');
      break;
    default:
      // Print unknown % sequence to draw attention.
      putchar('%');
      putchar(c);
      break;
    }
#endif
  }
  va_end(ap);

  return 0;
}

