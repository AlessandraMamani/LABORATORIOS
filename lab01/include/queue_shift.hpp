#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class QueueShift {
private:
  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::size_t moves_ = 0;

  void grow();

public:
  QueueShift() = default;
  QueueShift(const QueueShift &other);
  QueueShift(QueueShift &&other) noexcept;
  QueueShift &operator=(const QueueShift &other);
  QueueShift &operator=(QueueShift &&other) noexcept;
  ~QueueShift();

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
// moves_ cuenta transferencias debidas a redimensionamiento o desplazamiento,
// no la asignación normal del elemento que se inserta.

template<typename T>
void QueueShift<T>::grow() {
    std::size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    T *newData = new T[newCapacity];
    for (std::size_t i = 0; i < size_; ++i){
        newData[i] = std::move(data_[i]);
        ++moves_;
    }
    
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
    //throw std::logic_error("TODO QueueShift::grow");
}

template<typename T>
QueueShift<T>::QueueShift(const QueueShift &other) 
      : data_(other.capacity_ > 0 ? new T[other.capacity_] : nullptr),
        size_(other.size_),
        capacity_(other.capacity_),
        moves_(0){
    
    for(std::size_t i = 0; i < size_; ++i)
        data_[i] = other.data_[i];

    //throw std::logic_error("TODO QueueShift copy constructor");
}

template<typename T>
QueueShift<T>::QueueShift(QueueShift &&other) noexcept 
      : data_(other.data_),
        size_(other.size_),
        capacity_(other.capacity_),
        moves_(other.moves_){
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    other.moves_ = 0;  
 
    // TODO: transferir ownership y dejar el origen vacío.
}

template<typename T>
QueueShift<T> &QueueShift<T>::operator=(const QueueShift &other) {
    if (this != &other){
        T* newData = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i)
            newData[i] = other.data_[i];
        delete[] data_;
        data_ = newData;
        size_ = other.size_;
        capacity_ = other.capacity_;
        moves_ = 0;
    }
    return *this;

    //throw std::logic_error("TODO QueueShift copy assignment");
}

template<typename T>
QueueShift<T> &QueueShift<T>::operator=(QueueShift &&other) noexcept { 
    if (this != &other){
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;  
        moves_ = other.moves_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0; 
        other.moves_ = 0;
    }
    // TODO: liberar el recurso actual, transferir ownership y vaciar el origen.
  return *this;
}

template<typename T>
QueueShift<T>::~QueueShift() {
  delete[] data_;
}

template<typename T>
void QueueShift<T>::push(const T &x) {
    if (size_ == capacity_)
        grow();
    data_[size_] = x;
    ++size_; 

// throw std::logic_error("TODO QueueShift::push(const T&)");
}

template<typename T>
void QueueShift<T>::push(T &&x) {
    if (size_ == capacity_)
        grow();
    data_[size_] = std::move(x);
    ++size_;
    
//throw std::logic_error("TODO QueueShift::push(T&&)");
}

template<typename T>
void QueueShift<T>::pop() {
    if (empty())
        throw std::overflow_error("Queue is empty");
    for (std::size_t i = 1; i < size_; ++i){
        data_[i - 1] = std::move(data_[i]);
        ++moves_;
    }
    --size_;
  //throw std::logic_error("TODO QueueShift::pop");
}

template<typename T>
T &QueueShift<T>::front() {
    if (empty())
        throw std::out_of_range("Queue is empty");  
    return data_[0];
//throw std::logic_error("TODO QueueShift::front");
}

template<typename T>
const T &QueueShift<T>::front() const {
    if (empty())
        throw std::out_of_range("Queue is empty"); 
    return data_[0]; 
    
//throw std::logic_error("TODO QueueShift::front const");
}
