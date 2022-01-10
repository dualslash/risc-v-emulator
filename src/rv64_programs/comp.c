extern void print_roman(int s);
int A[20], B[20];

int main(void)
{
    int C, i;

    for (i = 0; i < 20; ++i)
        B[i] = i;

    C = 42;

    for (i = 1; i < 20; ++i)
        A[i] = B[i-1] + C;

    print_roman(A[19]);

    return 0;
}
