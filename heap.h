#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>

#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below

  // data members
  // vector for heap elements
  std::vector<T> heap_;
  // number of children per node
  int m_;
  // Comparator for determining priority
  PComparator comp_;

  // helper functions
  // restore heap invariant
  void heapify(int idx);
  // parent index
  int parent(int idx) const;
  // child index
  int child(int idx, int k) const;
};

// Add implementation of member functions here

// constructor
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) {
  this->m_ = m;
  this->comp_ = c;

  // make sure m is at least 2
  if(m_ < 2) {
    m_ = 2;
  }
}

// destructor
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {
  // nothing to do
}

// push iterm onto heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
  // push item to end of vector
  heap_.push_back(item);
  
  // restore the heap invariant by moving the item up as needed
  int idx = heap_.size() - 1;
  int parent_idx = parent(idx);

  // while item is not at root and has higher priority than parent
  while(idx > 0 && comp_(heap_[idx], heap_[parent_idx])) {
    // swap with parent
    std::swap(heap_[idx], heap_[parent_idx]);

    // move up
    idx = parent_idx;
    parent_idx = parent(idx);
  }
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================

    throw std::underflow_error("Heap is empty");


  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return heap_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================

    throw std::underflow_error("Heap is empty");


  }

  // replace root with last element
  heap_[0] = heap_.back();

  // remove last element
  heap_.pop_back();

  // restore heap invariant if heap is not empty
  if(!empty()) {
    heapify(0);
  }
}

// check if heap is empty
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  return heap_.empty();
}

// get size of heap
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
  return heap_.size();
}

// helper function to restore heap invariant
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(int idx)
{
  int size = heap_.size();
  int child_idx = child(idx, 1);
  int min_idx;

  // loop runs while node has children
  while(child_idx < size) {
    // find child with highest priority
    min_idx = child_idx;

    // check all children
    for(int k = 2; k <= m_; k++) {
      child_idx = child(idx, k);

      // if child exists and has higher priority
      if(child_idx < size && comp_(heap_[child_idx], heap_[min_idx])) {
        min_idx = child_idx;
      }
    }

    // if node has higher priority than all children
    if(comp_(heap_[idx], heap_[min_idx])) {
      return;
    }

    // swap with highest priority
    std::swap(heap_[idx], heap_[min_idx]);

    idx = min_idx;
    child_idx = child(idx, 1);
  }
}

// helper function to get parent index
template <typename T, typename PComparator>
int Heap<T, PComparator>::parent(int idx) const
{
  return (idx - 1) / m_;
}

// helper function to get chid index
template <typename T, typename PComparator>
int Heap<T, PComparator>::child(int idx, int k) const
{
  return m_ * idx + k;
}


#endif

