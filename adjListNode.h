#ifndef ADJLISTNODE_H
# define ADJLISTNODE_H

class AdjListNode {
    int v;
    double weight;

  public:
    AdjListNode(int _v, double _w);
    int getV();
    double getWeight();
};
#endif
