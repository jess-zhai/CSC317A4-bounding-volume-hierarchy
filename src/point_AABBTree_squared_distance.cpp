#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  using QueueElement = std::pair<double, std::shared_ptr<Object>>;
  std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> queue;

  double min_dist_found = max_sqrd;
  descendant = NULL;

  // Add root to the queue
  double root_sqrd = point_box_squared_distance(query, root->box);
  queue.emplace(root_sqrd, root);

  while (!queue.empty()){
    double current_sqrd = queue.top().first;
    std::shared_ptr<Object> current_node = queue.top().second;
    queue.pop();

    // If the current distance is larger than the smallest distance found so far,
    // then we don't need to process this node or its descendants.
    if (current_sqrd > min_dist_found){
        continue;
    }
    std::shared_ptr<AABBTree> current_tree = std::dynamic_pointer_cast<AABBTree>(current_node);
    if (current_tree){
      // Internal node: enqueue its children
      if (current_tree->left){
          double left_sqrd = point_box_squared_distance(query, current_tree->left->box);
          queue.emplace(left_sqrd, current_tree->left);
      }
      if (current_tree->right){
          double right_sqrd = point_box_squared_distance(query, current_tree->right->box);
          queue.emplace(right_sqrd, current_tree->right);
      }
    } else {
      // Leaf node: compute actual squared distance and update the min distance found
      double leaf_sqrd;
      std::shared_ptr<Object> leaf_descendant;
      if (current_node->point_squared_distance(query, min_sqrd, min_dist_found, leaf_sqrd, leaf_descendant)){
        if (leaf_sqrd < min_dist_found){
            min_dist_found = leaf_sqrd;
            descendant = current_node;
        }
      }
    }
  }
  if (descendant){
    sqrd = min_dist_found;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
