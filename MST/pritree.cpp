#ifndef PRITREE_CPP
#include "pritree.hpp"
#define GT >
#define LT <
#include <math.h>
//initilize the length of btree 5
template<class T>
Pritree<T>::Pritree()
{
  this->btree = new T[6];
  this->length = 0;
  this->maxLength = 5;
}

//free all the space
template<class T>
Pritree<T>::~Pritree()
{
  delete []btree;
}

//insert a element into priority queue
template<class T>
void Pritree<T>::insert(T ele_in)
{
  if(this->length == 0)
  {
    this->btree[1] = ele_in;
    this->length++;
  }
  else
  {
    ifResize();
    this->btree[this->length+1] = ele_in;
    this->length++;
    sift_up(this->length);
  }
}

//get it root element, but not delete it
template<class T>
T Pritree<T>::getHead()
{
  if(this->length == 0)
  {
    cout<<"Queue is empty\n";
  }
  return btree[1];
}

//get it root element, and delete it.
template<class T>
T Pritree<T>::popHead()
{
  if(this->length != 0)
  {
    T tt = btree[1];
    btree[1] = btree[this->length];
    this->length--;
    sift_down(1);
    return tt;
  }
  else
  {
    cout<<"Queue is empty\n";
    T tt;
    return tt;
  }
}

//get the length of queue
template<class T>
int Pritree<T>::getSize()
{
  return this->length;
}

//make the length of array 2 times than origin
//need test as it size 11
template<class T>
void Pritree<T>::ifResize()
{
  if(this->length + 1 > this->maxLength)
  {
    T temp[this->length+1];
    for(int counter = 1 ; counter <= this->length; counter++)
    {
      temp[counter] = this->btree[counter];
    }
    delete []this->btree;
    this->btree = new T[this->length*2 +1];
    this->maxLength = this->length*2;
    for(int counter = 1 ; counter <= this->length; counter++)
    {
        this->btree[counter] = temp[counter];
    }
  }
}

template<class T>
void Pritree<T>::sift_up(int position)
{
    while(floor(position / 2)!= 0)
    {
        if(btree[position/2] GT btree[position])
        {
            T temp;
            temp = btree[position/2];
            btree[position/2] = btree[position];
            btree[position] = temp;
            position = floor(position/2);
        }
        else
          break;
    }
}

template<class T>
void Pritree<T>::sift_down(int position)
{
  int nextposition;
  if(2*position > this->length)
    return;
  if(2*position < this->length)
  {
    if(btree[position*2] GT btree[position*2 +1])
      nextposition =position*2 + 1;
    else
      nextposition =position*2;
  }
  if(2*position == this->length)
    nextposition =position*2;

  if(btree[nextposition] LT btree[position] )
  {
    T temp;
    temp = btree[nextposition];
    btree[nextposition] = btree[position];
    btree[position] = temp;
    sift_down(nextposition);
  }
}

#define  PRITREE_CPP
#endif
