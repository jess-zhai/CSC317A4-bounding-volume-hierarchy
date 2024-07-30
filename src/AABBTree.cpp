#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (const auto& obj : objects) {
    insert_box_into_box(obj->box, this->box);
  }
  if (num_leaves == 0) {
    this->left = NULL;
    this->right = NULL;
  } else if (num_leaves == 1) {
    this->left = objects[0];
    this->right = NULL;
  } else if (num_leaves == 2) {
    this->left = objects[0];
    this->right = objects[1];
  } else {
    int axis = 0;
    double longest = -1;
    for (int i=0; i<3; i++) {
      double length = this->box.max_corner(i) - this->box.min_corner(i);
      if (length > longest) {
        longest = length;
        axis = i;
      }
    }
    double mid = this->box.center()(axis);

    std::vector<std::shared_ptr<Object>> left_objects, right_objects;
  for (const auto& obj : objects) {
    if (obj->box.center()(axis) < mid) {
      left_objects.push_back(obj);
    } else {
      right_objects.push_back(obj);
    }
  }
  
  if (left_objects.size() == 0 && right_objects.size() != 0){
    left_objects.push_back(right_objects.back());
    right_objects.pop_back();
  } else if (left_objects.size() != 0 && right_objects.size() == 0){
    right_objects.push_back(left_objects.back());
    left_objects.pop_back();
  }

  this->left = std::make_shared<AABBTree>(left_objects, depth + 1);
  this->right = std::make_shared<AABBTree>(right_objects, depth + 1);

  }
  ////////////////////////////////////////////////////////////////////////////
}
