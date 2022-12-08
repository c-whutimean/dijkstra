#include "adjListNode.h"

AdjListNode::AdjListNode(int _v, double _w) {
  this->v = _v;
  this->weight = _w;
}

int AdjListNode::getV(void) {
  return this->v;
}

double AdjListNode::getWeight(void) {
  return this->weight;
}
