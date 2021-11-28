#ifndef MATRIX_H
# define MATRIX_H

typedef double matrix[4][4];
typedef double vector[4];

void vv_cross(vector out, vector l, vector r);
double v_length(vector v);
void mm_mul(matrix out, matrix l, matrix r);
void mv_mul(vector out, matrix l, vector r);
void m_viewport(matrix vp, double x, double y);
void m_orth(matrix orth, double r, double l,
            double t, double b, double n, double f);
void m_camera(matrix cam, vector eye, vector gaze, vector up);
void m_per(matrix per, double n, double f);
void v_print(vector v);
void m_print(matrix m);
void m_copy(matrix new, matrix old);
void v_normalize(vector v);

#endif
