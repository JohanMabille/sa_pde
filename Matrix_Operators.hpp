#ifndef Matrix_Operators_HPP
#define Matrix_Operators_HPP

#include <vector>
using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix_Operators;

Vector operator*(const Matrix_Operators& C,const Vector& V);
Vector operator*(const double& a,const Vector& V);
Vector operator+(const double& a,const Vector& V);
Vector operator+(const Vector& V,const Vector& W);
Vector operator*(const Vector& V,const Vector& W);
Vector exp(const Vector& V);
double operator^(const Vector& V,const Vector& W);

#endif



