#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here: 
  if (!ray_intersect_box(ray, this->box, min_t, max_t)) {
    return false; 
  }
  bool intersect_left = false;
  bool intersect_right = false;

  double t_left = std::numeric_limits<double>::max(), t_right = std::numeric_limits<double>::max();
  std::shared_ptr<Object> left_descendant, right_descendant;

  // Check for the existence of left and right children and intersections
  if (this->left) {
    intersect_left = this->left->ray_intersect(ray, min_t, max_t, t_left, left_descendant);
    if (!left_descendant) {
      left_descendant = this->left;
    }
  }

  if (this->right) {
    intersect_right = this->right->ray_intersect(ray, min_t, max_t, t_right, right_descendant);
    if (!right_descendant) {
      right_descendant = this->right;
    }
  }

  // Determine the closest intersection
  if (intersect_left && intersect_right) {
    if (t_left < t_right) {
      t = t_left;
      descendant = left_descendant;
    } else {
      t = t_right;
      descendant = right_descendant;
    }
    return true;
  } else if (intersect_left) {
    t = t_left;
    descendant = left_descendant;
    return true;
  } else if (intersect_right) {
    t = t_right;
    descendant = right_descendant;
    return true;
  }

  return false;
  
  ////////////////////////////////////////////////////////////////////////////
}

