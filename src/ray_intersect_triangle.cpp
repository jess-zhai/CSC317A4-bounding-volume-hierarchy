#include "ray_intersect_triangle.h"
Eigen::Vector3d cross_product(const Eigen::Vector3d &a, const Eigen::Vector3d &b) {
  Eigen::Vector3d result;
  result(0) = a(1) * b(2) - a(2) * b(1);
  result(1) = a(2) * b(0) - a(0) * b(2);
  result(2) = a(0) * b(1) - a(1) * b(0);
  return result;
}
bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
  Eigen::Vector3d pt1(A(0), A(1), A(2));
  Eigen::Vector3d pt2(B(0), B(1), B(2));
  Eigen::Vector3d pt3(C(0), C(1), C(2));
  Eigen::Vector3d edge1 = pt2 - pt1;
  Eigen::Vector3d edge2 = pt3 - pt1;
  Eigen::Vector3d h = cross_product(ray.direction, edge2);
  double a = edge1.dot(h);

  Eigen::Vector3d normal = cross_product(edge1, edge2);
  if (normal.dot(ray.direction) == 0) {
    return false;
  }
  if (fabs(a) < 1e-8) {
      return false;
  }

  double f = 1.0/a;
  Eigen::Vector3d s = ray.origin - pt1;
  double u = f * s.dot(h);

  if (u < 0.0 || u > 1.0){
    return false;
  }
  Eigen::Vector3d q = cross_product(s, edge1);
  double v = f * ray.direction.dot(q);
  if (v < 0.0 || u + v > 1.0){
    return false;
  }
  
  double t_temp = f * edge2.dot(q);
  if (t_temp >= min_t && t_temp <= max_t){
    t = t_temp;
    return true;
  } else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

