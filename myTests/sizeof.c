int main()
{
	int p;
	struct test
	{
		int a;
		struct testinner
		{
			int d;
			int b[10];
		} c[5];
	} x[10];

	struct test y;
	int a[5];
	int b;

	sizeof(b = 5);
	sizeof(b);
	sizeof(a);
	sizeof(int);
	sizeof(a[5]);
	sizeof(x);
	sizeof(x[1].c);
	sizeof(x[1].c[0]);
	sizeof(x[1].c[0].d);
	sizeof(x[1].c[0].b);
	sizeof(x[1].c[0].b[0]);

	cout = sizeof(b + 1);
	cout = sizeof(b);
	cout = sizeof(a);
	cout = sizeof(int);
	cout = sizeof(a[5]);
	cout = sizeof(x);
	cout = sizeof(x[1].c);
	cout = sizeof(x[1].c[0]);
	cout = sizeof(x[1].c[0].d);
	cout = sizeof(x[1].c[0].b);
	cout = sizeof(x[1].c[0].b[0]);
	return 0;
}
