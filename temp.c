

void add(int *n1, int *n2)
{
  *n1 = *n1 + *n2;
  return;
}

int main(void)
{
  int n1 = 1;
  int n2 = 2;
  add (&n1, &n2);
  
  
}
