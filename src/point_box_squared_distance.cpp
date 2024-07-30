#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  double dist_x = fmax(fmax(box.min_corner(0) - query(0), query(0) - box.max_corner(0)), 0);
  double dist_y = fmax(fmax(box.min_corner(1) - query(1), query(1) - box.max_corner(1)), 0);
  double dist_z = fmax(fmax(box.min_corner(2) - query(2), query(2) - box.max_corner(2)), 0);
  return dist_x * dist_x + dist_y * dist_y + dist_z * dist_z;
  ////////////////////////////////////////////////////////////////////////////
}
