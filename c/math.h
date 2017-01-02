#ifndef __MATH_H__
#define __MATH_H__

double round(double x);
double floor(double x);
double ceil(double x);

double round(double x){
	return (int)(x + 0.5);
}

double floor(double x){
	return (int)x;
}

double ceil(double x){
	return (int)(x + 0.9);
}

#endif // __MATH_H__
