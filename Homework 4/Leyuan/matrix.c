#include <stdio.h>

#include "matrix.h"

void vv_cross(vector out, vector l, vector r)
{
  /* Cross products only make sense on direction vectors.  We can *
   * ignore the homogeneous coordinate and treat this as a        *
   * 3-vector.                                                    */

  out[0] = l[1] * r[2] - l[2] * r[1];
  out[1] = l[2] * r[0] - l[0] * r[2];
  out[1] = l[0] * r[1] - l[1] * r[0];
}

double v_length(vector v)
{
  return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

void mm_mul(matrix out, matrix l, matrix r)
{
  out[0][0] = ((l[0][0] * r[0][0]) + (l[0][1] * r[1][0]) +
               (l[0][2] * r[2][0]) + (l[0][3] * r[3][0]));
  out[0][1] = ((l[0][0] * r[0][1]) + (l[0][1] * r[1][1]) +
               (l[0][2] * r[2][1]) + (l[0][3] * r[3][1]));
  out[0][2] = ((l[0][0] * r[0][2]) + (l[0][1] * r[1][2]) +
               (l[0][2] * r[2][2]) + (l[0][3] * r[3][2]));
  out[0][3] = ((l[0][0] * r[0][3]) + (l[0][1] * r[1][3]) +
               (l[0][2] * r[2][3]) + (l[0][3] * r[3][3]));

  out[1][0] = ((l[1][0] * r[0][0]) + (l[1][1] * r[1][0]) +
               (l[1][2] * r[2][0]) + (l[1][3] * r[3][0]));
  out[1][1] = ((l[1][0] * r[0][1]) + (l[1][1] * r[1][1]) +
               (l[1][2] * r[2][1]) + (l[1][3] * r[3][1]));
  out[1][2] = ((l[1][0] * r[0][2]) + (l[1][1] * r[1][2]) +
               (l[1][2] * r[2][2]) + (l[1][3] * r[3][2]));
  out[1][3] = ((l[1][0] * r[0][3]) + (l[1][1] * r[1][3]) +
               (l[1][2] * r[2][3]) + (l[1][3] * r[3][3]));

  out[2][0] = ((l[2][0] * r[0][0]) + (l[2][1] * r[1][0]) +
               (l[2][2] * r[2][0]) + (l[2][3] * r[3][0]));
  out[2][1] = ((l[2][0] * r[0][1]) + (l[2][1] * r[1][1]) +
               (l[2][2] * r[2][1]) + (l[2][3] * r[3][1]));
  out[2][2] = ((l[2][0] * r[0][2]) + (l[2][1] * r[1][2]) +
               (l[2][2] * r[2][2]) + (l[2][3] * r[3][2]));
  out[2][3] = ((l[2][0] * r[0][3]) + (l[2][1] * r[1][3]) +
               (l[2][2] * r[2][3]) + (l[2][3] * r[3][3]));

  out[3][0] = ((l[3][0] * r[0][0]) + (l[3][1] * r[1][0]) +
               (l[3][2] * r[2][0]) + (l[3][3] * r[3][0]));
  out[3][1] = ((l[3][0] * r[0][1]) + (l[3][1] * r[1][1]) +
               (l[3][2] * r[2][1]) + (l[3][3] * r[3][1]));
  out[3][2] = ((l[3][0] * r[0][2]) + (l[3][1] * r[1][2]) +
               (l[3][2] * r[2][2]) + (l[3][3] * r[3][2]));
  out[3][3] = ((l[3][0] * r[0][3]) + (l[3][1] * r[1][3]) +
               (l[3][2] * r[2][3]) + (l[3][3] * r[3][3]));
}

void mv_mul(vector out, matrix l, vector r)
{
  out[0] = ((l[0][0] * r[0]) + (l[0][1] * r[1]) +
            (l[0][2] * r[2]) + (l[0][3] * r[3]));
  out[1] = ((l[1][0] * r[0]) + (l[1][1] * r[1]) +
            (l[1][2] * r[2]) + (l[1][3] * r[3]));
  out[2] = ((l[2][0] * r[0]) + (l[2][1] * r[1]) +
            (l[2][2] * r[2]) + (l[2][3] * r[3]));
  out[3] = ((l[3][0] * r[0]) + (l[3][1] * r[1]) +
            (l[3][2] * r[2]) + (l[3][3] * r[3]));
}

void m_viewport(matrix vp, double x, double y)
{
  vp[0][0] = x / 2;
  vp[0][1] = vp[0][2] = 0;
  vp[0][3] = (x - 1) / 2;
  vp[1][0] = 0;
  vp[1][1] = y / 2;
  vp[1][2] = 0;
  vp[1][3] = (y - 1) / 2;
  vp[2][0] = vp[2][1] = 0;
  vp[2][2] = 1;
  vp[2][3] = vp[3][0] = vp[3][1] = vp[3][2] = 0;
  vp[3][3] = 1;
}

void m_orth(matrix orth, double r, double l,
            double t, double b, double n, double f)
{
  orth[0][0] = 2 / (r - l);
  orth[0][1] = orth[0][2] = 0;
  orth[0][3] = -(r + l) / (r - l);
  orth[1][0] = 0;
  orth[1][1] = 2 / (t - b);
  orth[1][2] = 0;
  orth[1][3] = -(t + b) / (t - b);
  orth[2][0] = orth[2][1] = 0;
  orth[2][2] = 2 / (n - f);
  orth[2][3] = -(n + f) / (n - f);
  orth[3][0] = orth[3][1] = orth[3][2] = 0;
  orth[3][3] = 1;
}

void m_camera(matrix cam, vector eye, vector gaze, vector up)
{
  vector u, v, w;
  double d;

  d = -v_length(gaze);
  w[0] = gaze[0] / d;
  w[1] = gaze[1] / d;
  w[2] = gaze[2] / d;

  vv_cross(u, up, w);
  d = v_length(u);
  u[0] /= d;
  u[1] /= d;
  u[2] /= d;

  vv_cross(v, w, u);

  cam[0][0] = u[0];
  cam[0][1] = v[0];
  cam[0][2] = w[0];
  cam[0][3] = eye[0];
  cam[1][0] = u[1];
  cam[1][1] = v[1];
  cam[1][2] = w[1];
  cam[1][3] = eye[1];
  cam[2][0] = u[2];
  cam[2][1] = v[2];
  cam[2][2] = w[2];
  cam[2][3] = eye[2];
  cam[3][0] = cam[3][1] = cam[3][2] = 0;
  cam[3][3] = 1;
}

void m_per(matrix per, double n, double f)
{
  per[0][0] = n;
  per[0][1] = per[0][2] = per[0][3] = per[1][0] = 0;
  per[1][1] = n;
  per[1][2] = per[1][3] = per[2][0] = per[2][1] = 0;
  per[2][2] = n + f;
  per[2][3] = -n * f;
  per[3][0] = per[3][1] = 0;
  per[3][2] = 1;
  per[3][3] = 0;
}

void m_print(matrix m)
{
  printf("--                             --\n"
         "|%7.2f %7.2f %7.2f %7.2f|\n"
         "|%7.2f %7.2f %7.2f %7.2f|\n"
         "|%7.2f %7.2f %7.2f %7.2f|\n"
         "|%7.2f %7.2f %7.2f %7.2f|\n"
         "--                             --\n",
         m[0][0], m[0][1], m[0][2], m[0][3],
         m[1][0], m[1][1], m[1][2], m[1][3],
         m[2][0], m[2][1], m[2][2], m[2][3],
         m[3][0], m[3][1], m[3][2], m[3][3]);
}

void v_print(vector v)
{
  printf("[%7.2f %7.2f %7.2f %7.2f]\n",
         v[0], v[1], v[2], v[3]);
}

void m_copy(matrix new, matrix old)
{
  new[0][0] = old[0][0];
  new[0][1] = old[0][1];
  new[0][2] = old[0][2];
  new[0][3] = old[0][3];
  new[1][0] = old[1][0];
  new[1][1] = old[1][1];
  new[1][2] = old[1][2];
  new[1][3] = old[1][3];
  new[2][0] = old[2][0];
  new[2][1] = old[2][1];
  new[2][2] = old[2][2];
  new[2][3] = old[2][3];
  new[3][0] = old[3][0];
  new[3][1] = old[3][1];
  new[3][2] = old[3][2];
  new[3][3] = old[3][3];
}

void v_normalize(vector v)
{
  v[0] /= v[3];
  v[1] /= v[3];
  v[2] /= v[3];
  v[3] = 1;
}
