#ifndef __MATH_H__
#define __MATH_H__

double round(double x);
double floor(double x);
double ceil(double x);
double square(double x);
double square_root(double x);
double square_root_r(double x);
static double square_root_rec(double min, double max, double x);

double round(double x){
	return (int)(x + 0.5);
}

double floor(double x){
	return (int)x;
}

double ceil(double x){
	return (int)(x + 0.9);
}

double square(double x){
	return x * x;
}

double square_root(double x){
	double min = 0.0;
	double max = x;
	double mid;

	while(min <= max){
		mid = (min + max) / 2.0;	
		
		if(mid * mid == x){
			return mid;

		}else if(mid * mid > x){
			max = mid;

		}else{
			min = mid;	
		}
	}

	return -1.0;
}

double square_root_r(double x){
	return square_root_rec(0, x, x);	
}

static double square_root_rec(double min, double max, double x){
	if(min > max){
		return -1.0;
	}
	
	double mid = (min + max) / 2.0;

	if(mid * mid == x){
		return mid;
	
	}else if(mid * mid > x){
		return square_root_rec(min, mid, x);

	}else{
		return square_root_rec(mid, max, x);
	}
}

#endif // __MATH_H__

