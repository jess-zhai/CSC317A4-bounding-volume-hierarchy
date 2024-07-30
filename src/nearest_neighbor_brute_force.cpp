#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  I = -1;
  sqrD = std::numeric_limits<double>::infinity();
  for (int i = 0; i < points.rows(); i++) {
    Eigen::RowVector3d diff = query - points.row(i);
    double curr_sqrD = diff.squaredNorm(); // Compute the squared distance between query and the current point

    // If the current squared distance is less than the smallest seen so far, update I and sqrD
    if (curr_sqrD < sqrD) {
      sqrD = curr_sqrD;
      I = i;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
