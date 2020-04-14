#include "newton.h"

int main()
{
	matrix a;
	a.print();
	a.print_fluxion();
	a.iteration();
	return 0;
}