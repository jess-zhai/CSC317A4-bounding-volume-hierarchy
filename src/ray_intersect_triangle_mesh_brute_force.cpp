#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  hit_t = std::numeric_limits<double>::infinity();
  hit_f = -1;
  const int num_f = F.rows();
  double t_temp;
  
  for (int i=0; i<num_f; i++) {
    const Eigen::RowVector3d A = V.row(F(i, 0));
    const Eigen::RowVector3d B = V.row(F(i, 1));
    const Eigen::RowVector3d C = V.row(F(i, 2));

    if (ray_intersect_triangle(ray, A, B, C, min_t, max_t, t_temp)) {
      if (t_temp < hit_t) {
        hit_t = t_temp;
        hit_f = i;
        if (hit_t == min_t){
          return true;
        }
      }
    }
  }

  if (hit_f >= 0) {
    return true;
  } else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}
