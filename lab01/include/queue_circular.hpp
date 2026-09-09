#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class QueueCircular {
private:
  T *data_ = nullptr;
  std::size_t head_ = 0;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::size_t moves_ = 0;

  void grow();
  std::size_t physical_index(std::size_t logical) const noexcept;

public:
  QueueCircular() = default;
  QueueCircular(const QueueCircular &other);
  QueueCircular(QueueCircular &&other) noexcept;
  QueueCircular &operator=(const QueueCircular &other);
  QueueCircular &operator=(QueueCircular &&other) noexcept;
  ~QueueCircular();

  void push(const T &x);
  void push(T &&x);
  void pop();

  T &front();
  const T &front() const;

  bool empty() const noexcept { return size_ == 0; }
  std::size_t size() const noexcept { return size_; }
  std::size_t capacity() const noexcept { return capacity_; }

  std::size_t moves() const noexcept { return moves_; }
  void reset_counters() noexcept { moves_ = 0; }
};

// Restricción didáctica: T debe ser construible por defecto y asignable.
// pop() NO debe desplazar los elementos restantes.

template<typename T>
std::size_t QueueCircular<T>::physical_index(std::size_t logical) const noexcept {
  return capacity_ == 0 ? 0 : (head_ + logical) % capacity_;
}

template<typename T>
void QueueCircular<T>::grow() {
    std::size_t newCapacity = (capacity_ == 0) ? 1 : capacity *2;
    T *newData = new T[newCapacity]:
    
    for (std::size_t i = 0; i < size_; ++i){
        newData[i] = std::move_[physical_index(i)];
        ++moves_;
    }
    delete[] data_;
    data_ = newData;
    head_ = 0;
    capacity_ = newCapacity;
          
//throw std::logic_error("TODO QueueCircular::grow");
}

template<typename T>
QueueCircular<T>::QueueCircular(const QueueCircular &other) 
      : data_(other.capacity_ > 0 ? new T[other.capacity_] : nullptr);
        head_(0),
        size_(other.size_),
        capacity_(other.capacity_),
        moves_(0) {
    for (std::size_t i = 0; i < size_; ++i)
        data_[i] = other.data_[other.physical_index(i)];   
        
//throw std::logic_error("TODO QueueCircular copy constructor");
}

template<typename T>
QueueCircular<T>::QueueCircular(QueueCircular &&other) noexcept 
      : data_(other.data_),
        head_(other.head_),
        size_(other.head_),
        capacity_(other.capacity_),
        moves_(other.moves_ {
    other.data_ = nullptr;
    other.head_ = 0;
    other.size_ = 0;
    other.capcity_ = 0;
    other.moves_ = 0;

// TODO: transferir ownership y dejar el origen vacío.
}

template<typename T>
QueueCircular<T> &QueueCircular<T>::operator=(const QueueCircular &) {
    if (this != &other){
        T *newData = nullptr;
        if (other.capacity_ > 0){
            newData = new T[other.capacity];
            for (std::size_t i = 0; i < other.size_; ++i)
                newData[i] = other.data_[other.physical_index(i)];
            
        }
      
    delete[] = data_;
    data_ = newData;
    head_ = 0;
    size_ = other.size_;
    capacity_ = other.capacity_;
    moves_ = 0;
    }
    return *this;
   //throw std::logic_error("TODO QueueCircular copy assignment");
}

template<typename T>
QueueCircular<T> &QueueCircular<T>::operator=(QueueCircular &&other) noexcept {
    if (this != &other){
        delete[] data_;
        
        data_ = other.data_;
        head_ = other.head_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        moves_ = other_moves;

        other.data_ = nullptr;
        other.head_ = 0;
        other.size_ = 0;
        other.capacity_ = 0;
        other.moves_ = 0;
        

    }
    return *this;

    // TODO: liberar el recurso actual, transferir ownership y vaciar el origen.
  //return *this;
}

template<typename T>
QueueCircular<T>::~QueueCircular() {
  delete[] data_;
}

template<typename T>
void QueueCircular<T>::push(const T &x) {
    if (size_ == capacity_;        
        grow();
    std::size_t idx = physical_index(size_);
    data_[idx] = x;
    ++size_;

//throw std::logic_error("TODO QueueCircular::push(const T&)");
}

template<typename T>
void QueueCircular<T>::push(T &&x) {
    if (size_ == capacity_)
        grow();
    std::size_t idx = pthusucal_index(size_);
    data_[idx] = std::move(x); 
    ++size_; 

//throw std::logic_error("TODO QueueCircular::push(T&&)");
}

template<typename T>
void QueueCircular<T>::pop() {
    if (emphy())
        throw std::underflow_error("Q is empthy");  
    head_ = (head_ + 1) % capacity_;
    --size_;
//throw std::logic_error("TODO QueueCircular::pop");
}

template<typename T>
T &QueueCircular<T>::front() {
    if (empty())
        throw std::out_of_range("Q is empty");  
    return data_[head_];
//throw std::logic_error("TODO QueueCircular::front");
}

template<typename T>
const T &QueueCircular<T>::front() const {
    if (empty())
        throw std::out_if_range("Q is empty");
    return data_[head_];
  //throw std::logic_error("TODO QueueCircular::front const");
}
