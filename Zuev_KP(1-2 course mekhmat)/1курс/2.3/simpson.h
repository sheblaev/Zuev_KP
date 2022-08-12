typedef double(*RRFUN)(double a);

double modul(double x);
double integrate(double a, double b, double n, RRFUN ffunc);

