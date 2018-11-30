#ifndef PRITREE_HPP
#include <iostream>
using namespace std;
template<class T>
class Pritree{
public:
  //initilize the size of btree 5
  //set smallToBig true
  Pritree();

  //free all the space
  ~Pritree();

  //insert a element into priority tree
  void insert(T ele_in);

  //get it root element, but not delete it
  T getHead();

  //get it root element, and delete it.
  T popHead();

  //get the length of queue
  int getSize();
private:
  T* btree;//it will be used as a array.
  int length;
  int maxLength;

  void ifResize();
  void sift_up(int position);
  void sift_down(int position);
};
#define  PRITREE_HPP
#endif
