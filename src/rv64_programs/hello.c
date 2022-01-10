
int main(void)
{
    volatile char *debugout = (char*)0x200;

    *debugout = 'h';
    *debugout = 'e';
    *debugout = 'l';
    *debugout = 'l';
    *debugout = 'o';
    *debugout = '\n';
    return 0;
}
