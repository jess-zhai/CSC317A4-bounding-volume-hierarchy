#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> queue;
  if (box_box_intersect(rootA->box, rootB->box)) {
    queue.push_back({rootA, rootB});
  }
  
  while (!queue.empty()) {
    auto current_pair = queue.front();
    queue.pop_front();

    auto nodeA = std::dynamic_pointer_cast<AABBTree>(current_pair.first);
    auto nodeB = std::dynamic_pointer_cast<AABBTree>(current_pair.second);

    if (!nodeA && !nodeB) {
      leaf_pairs.push_back({current_pair.first, current_pair.second});
      continue;
    }

    if (!nodeA) {
      if (nodeB->left && box_box_intersect(current_pair.first->box, nodeB->left->box)) {
        queue.push_back({current_pair.first, nodeB->left});
      }
      if (nodeB->right && box_box_intersect(current_pair.first->box, nodeB->right->box)) {
        queue.push_back({current_pair.first, nodeB->right});
      }
      continue;
    }

    if (!nodeB) {
      if (nodeA->left && box_box_intersect(nodeA->left->box, current_pair.second->box)) {
        queue.push_back({nodeA->left, current_pair.second});
      }
      if (nodeA->right && box_box_intersect(nodeA->right->box, current_pair.second->box)) {
        queue.push_back({nodeA->right, current_pair.second});
      }
      continue;
    }

    // If we reached this point, both nodes are not leaves
    if (nodeA->left && nodeB->left && box_box_intersect(nodeA->left->box, nodeB->left->box)) {
      queue.push_back({nodeA->left, nodeB->left});
    }
    if (nodeA->left && nodeB->right && box_box_intersect(nodeA->left->box, nodeB->right->box)) {
      queue.push_back({nodeA->left, nodeB->right});
    }
    if (nodeA->right && nodeB->left && box_box_intersect(nodeA->right->box, nodeB->left->box)) {
      queue.push_back({nodeA->right, nodeB->left});
    }
    if (nodeA->right && nodeB->right && box_box_intersect(nodeA->right->box, nodeB->right->box)) {
      queue.push_back({nodeA->right, nodeB->right});
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
