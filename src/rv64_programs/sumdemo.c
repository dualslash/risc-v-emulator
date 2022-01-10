extern void print_roman(int s);

static int sum_array(int n, int x[])
{
  int i, s = 0;
  for (i = 0; i < n; ++i)
    s += x[i];
  return s;
}

static int values[] = { 1, 2, 3, 4, 5, 6 };

int main(void)
{
  int s = sum_array(6, values);
  print_roman(s);

  return 0;
}
