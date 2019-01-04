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


  //从队列中删除ele_in元素，使用传进来的equal函数来检查队列中的元素是否和传进来的ele_in相等。
  void delete_ele(T ele_in,bool(*equal)(T t1,T t2));


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
