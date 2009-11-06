struct test
	{
		struct inner
		{
			int c;
			int d;
		}a;
		int b;
	} ;

int main()
{

	struct test x[10];
	struct test y[10];
	struct test s1;
	struct test s2;
	struct test *tp;
	int a;
	s1.b=1;
	s1.a.c=2;
	s1.a.d=3;
	s2=s1;
	cout=s2.b;
	cout=s2.a.c;
	cout=s2.a.d;
	y[0]=s1;
	x[0]=y[0];
	cout=x[0].b;
	cout=x[0].a.c;
	cout=x[0].a.d;
	y[1] = y[0];
	x[1].b = y[1].b;
	x[1].a = y[1].a;
	cout=x[1].b;
	cout=x[1].a.c;
	cout=x[1].a.d;
	tp=&s1;
	cout=&s1;
	cout=tp;
	a=6;
	cout=a;
	return 0;
}
