typedef double (*RRFUN) (double x);
typedef enum {SF_OK=0, SF_ERROR} ErrorCode;
double delenie(double a, double b, double ep, RRFUN func, ErrorCode *error_code);


