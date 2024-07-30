#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double tmin = (box.min_corner[0] - ray.origin[0]) / ray.direction[0];
  double tmax = (box.max_corner[0] - ray.origin[0]) / ray.direction[0];

  if (tmin > tmax) std::swap(tmin, tmax);

  double tymin = (box.min_corner[1] - ray.origin[1]) / ray.direction[1];
  double tymax = (box.max_corner[1] - ray.origin[1]) / ray.direction[1];

  if (tymin > tymax) std::swap(tymin, tymax);

  if ((tmin > tymax) || (tymin > tmax))
    return false;

  if (tymin > tmin)
    tmin = tymin;
  if (tymax < tmax)
    tmax = tymax;

  double tzmin = (box.min_corner[2] - ray.origin[2]) / ray.direction[2];
  double tzmax = (box.max_corner[2] - ray.origin[2]) / ray.direction[2];

  if (tzmin > tzmax) std::swap(tzmin, tzmax);

  if ((tmin > tzmax) || (tzmin > tmax))
    return false;

  if (tzmin > tmin)
    tmin = tzmin;
  if (tzmax < tmax)
    tmax = tzmax;

  return (tmin < max_t) && (tmax > min_t);
  ////////////////////////////////////////////////////////////////////////////
}
