int Factorial(int x){
	int y=1;
	if(x<=1)
		return 1;
	for(int i=2;i<=x;i++)
		y*=i;
	return y;
}
