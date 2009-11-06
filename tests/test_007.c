
int printf();
int x;

int foo()
{
  x = 100;
  return x;
}

int main()
{
  int y[100*10];
  foo();
  return foo();
}
