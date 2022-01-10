/* Unrolled matvec and the operations have been put in functions. */

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


static void
matvec(int A[N][N], const int B[N])
{
  int i, j;

  for (j = 0; j < N; ++j)
    for (i = 0; i < N; i += 4)
      {
        A[i+0][j] += B[i+0];
        A[i+1][j] += B[i+1];
        A[i+2][j] += B[i+2];
        A[i+3][j] += B[i+3];
      }
}

static void
print_diag(const int A[N][N])
{
  int i;

  /* Print elements on the diagonal */
  for (i = 0; i < N; ++i)
    print_roman(A[i][i]);
}


int main(void)
{
  matvec(A, B);
  print_diag(A);

  return 0;
}
