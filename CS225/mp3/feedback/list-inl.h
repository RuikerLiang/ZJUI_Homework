#pragma once
#include "list.h"
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  if (head_ == NULL)
    return;
  ListNode* nxt = head_->next;
  for (ListNode* i = head_; i != NULL; nxt = nxt == NULL ? NULL : nxt->next)
  {
    delete i;
    i = nxt;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1
  ListNode* tmp = head_;
  head_ = new ListNode(ndata);
  if (tmp)
    tmp->prev = head_;
  head_->next = tmp;
  head_->prev = NULL;
  length_++;
  if (!tail_)
    tail_ = head_;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
  ListNode* tmp = tail_;
  tail_ = new ListNode(ndata);
  if (tmp)
    tmp->next = tail_;
  tail_->prev = tmp;
  tail_->next = NULL;
  length_++;
  if (!head_)
    head_ = tail_;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

template <class T>
void swap_(T &a, T &b)
{
  T tmp = a;
  a = b;
  b = tmp;
}
/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1
  ListNode* traverse = startPoint;
  while (traverse != endPoint)
  {
    swap_(traverse->prev, traverse->next);
    traverse = traverse->prev;
  }
  swap_(endPoint->next, endPoint->prev);
  swap_(startPoint, endPoint);
  swap_(endPoint->next, startPoint->prev);
  if (startPoint->prev)
    startPoint->prev->next = startPoint;
  if (endPoint->next)
    endPoint->next->prev = endPoint;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  auto get_nxt = [n](ListNode* ptr)
  {
    if (ptr == NULL)
      return ptr;
    for (int i = 1; i < n; ++i)
      if (ptr->next != NULL)
        ptr = ptr->next;
    return ptr;
  };
  if (head_ == NULL)
    return;
  ListNode* traverse = head_, *nxt = get_nxt(head_);
  while (traverse != NULL)
  {
    if (traverse == head_)
      reverse(head_, nxt);
    else
      reverse(traverse, nxt);
    tail_ = nxt;
    traverse = nxt->next;
    nxt = get_nxt(traverse);
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  int cnt = 0;
  ListNode* nxt = NULL;
  for (ListNode* i = head_; i != NULL && i != tail_; i = nxt, cnt = cnt ^ 1)
  {
    nxt = i->next;
    if (!cnt)
      continue;
    i->prev->next = i->next;
    i->next->prev = i->prev;
    tail_->next = i;
    i->prev = tail_;
    i->next = NULL;
    tail_ = i;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    ListNode* traverse = start;
    for (int i = 1; i < splitPoint; ++i)
      if (traverse != NULL)
        traverse = traverse->next;
    auto ret = traverse->next;
    traverse->next = NULL;
    return ret;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (!first && !second)
    return NULL;
  ListNode* traverse[2] = { first, second };
  ListNode* new_head, *new_tail;
  new_head = new_tail = NULL;
  while (traverse[0] != NULL || traverse[1] != NULL)
  {
    int bit = -1;
    for (int i = 0; i < 2; ++i)
      if (traverse[i] != NULL)
      {
        if (bit == -1)
        {
          bit = i;
          continue;
        }
        if (traverse[i]->data < traverse[bit]->data)
          bit = i;
      }
    if (!new_head)
    {
      new_head = new_tail = traverse[bit];
      traverse[bit] = traverse[bit]->next;
      new_tail->next = NULL;
      continue;
    }
    new_tail->next = traverse[bit], traverse[bit]->prev = new_tail;
    new_tail = traverse[bit];
    traverse[bit] = traverse[bit]->next;
    new_tail->next = NULL;
  }
  return new_head;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    if (chainLength == 1)
      return start;
    
    int fir_len = chainLength / 2, sec_len = chainLength - fir_len;
    ListNode* sec = split(start, fir_len);
    start = mergesort(start, fir_len);
    sec = mergesort(sec,sec_len);
    start = merge(start, sec);
    return start;
}
