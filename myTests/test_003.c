int main()
{
  int arr[100];
  int y;
  int *x;

  x = &arr[10];

  *x = 5;
  cout=x;
  cout=*x;
  cout=&arr[10];
  cout=arr[10];
  return 0;
}
