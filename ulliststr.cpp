#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val){
  if(size()==0) {
    tail_ = new Item();
    tail_->last = 1;
    tail_->val[0] = val;
    head_ = tail_;
  }
  else if(tail_->last==ARRSIZE){
    Item* newItem = new Item();
    Item* tempItem = tail_;
    newItem->last = 1;
    newItem->val[0] = val;
    newItem->prev = tempItem;
    tempItem->next = newItem;
    tail_ = newItem;
  }
  else {
    tail_->last = tail_->last+1;
    tail_->val[tail_->last-1] = val;
  }
  size_++;
}

void ULListStr::push_front(const std::string& val){
  if(head_==NULL){
    head_ = new Item();
    head_->last = ARRSIZE;
    head_->first = ARRSIZE-1;
    head_->val[ARRSIZE-1] = val;
    tail_ = head_;
  }
  else if(head_->first == 0) {
    Item* newItem = new Item();
    Item* tempItem = head_;
    newItem->first = ARRSIZE-1;
    newItem->last = ARRSIZE;
    newItem->val[ARRSIZE-1] = val;
    newItem->next = tempItem;
    tempItem->prev = newItem;
    head_ = newItem;
  }
  else{
    head_->first = head_->first-1;
    head_->val[head_->first] = val;
  }
  size_++;
}

void ULListStr::pop_back(){
  if(empty()) return;
  if(size()==1) {
    delete head_;
    head_ = NULL;
    tail_ = NULL;
    size_--;
    return;
  }
  if(tail_->last-tail_->first==1){
    Item* temp = tail_->prev;
    delete tail_;
    tail_ = temp;
    tail_->next = NULL;
  }
  else{
    tail_->last--;
  }
  size_--;
}

void ULListStr::pop_front(){
  if(empty()) return;
  if(size()==1){
    delete head_;
    head_ = NULL;
    tail_ = NULL;
    size_--;
    return;
  }
  if(head_->last-head_->first==1) {
    Item* temp = head_->next;
    delete head_;
    head_ = temp;
    head_->prev = NULL;
  }
  else{
    head_->first++;
  }
  size_--;
}

std::string const& ULListStr::front() const{
  if(!empty()) return head_->val[head_->first];
  return NULL;
}

std::string const& ULListStr::back() const{
  if(!empty()) return tail_->val[tail_->last-1];
  return NULL;
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  if(loc>=size()||loc<0) return NULL;
  int cnt = 0;
  Item* temp = head_;
  int idx = head_->first;
  while(cnt!=loc){
    cnt++;
    idx++;
    if(idx==temp->last){
      temp = temp->next;
      idx = temp->first;
    }
  }
  return &(temp->val[idx]);
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
