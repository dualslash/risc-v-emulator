extern void print_roman(int s);

#define N 8

static int A[N][N] =
{
  { 1, 1, 1, 1,  1, 1, 1, 1 },
  { 2, 2, 2, 2,  2, 2, 2, 2 },
  { 3, 3, 3, 3,  3, 3, 3, 3 },
  { 4, 4, 4, 4,  4, 4, 4, 4 },
  { 5, 5, 5, 5,  5, 5, 5, 5 },
  { 6, 6, 6, 6,  6, 6, 6, 6 },
  { 7, 7, 7, 7,  7, 7, 7, 7 },
  { 8, 8, 8, 8,  8, 8, 8, 8 },
};

static int B[N] =
{ 34, 65, 56, 34,  23, 25, 65, 6 };

int main(void)
{
  int i, j;

  /* Perform matrix vector addition */
  for (j = 0; j < N; ++j)
    for (i = 0; i < N; ++i)
      A[i][j] += B[i];

  /* Print elements on the diagonal */
  for (i = 0; i < N; ++i)
    print_roman(A[i][i]);

  return 0;
}
