
int putchar(int c)
{
  volatile char *debugout = (char*)0x200;

  *debugout = c;
  return 0;
}

void puts(const char *str)
{
  for (const char *s = str; *s != '\0'; s++)
    putchar(*s);
  putchar('\n');
}

int main(void)
{
  puts("hello");
  return 0;
}
