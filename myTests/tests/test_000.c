int incr(int a)
{
	return a+1;
}

int main()
{
	int x[10];
	int y[10];
	int i;

	for(i=0;i<10;i=i+1)
		x[i]=i;

	for(i=0;i<10;i=i+1)
		y[x[i]]=i;

	for(i=0;i<10;i=i+1)
		cout=y[x[i]];
	return 0;
}
