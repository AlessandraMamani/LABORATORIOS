#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class StackRaw {
private:
  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;

  void grow();

public:
  StackRaw() = default;
  StackRaw(const StackRaw &other);
  StackRaw(StackRaw &&other) noexcept;
  StackRaw &operator=(const StackRaw &other);
  StackRaw &operator=(StackRaw &&other) noexcept;
  ~StackRaw();

  void push(const T &x);
  void push(T &&x);
  void pop();

  T &top();
  const T &top() const;

  bool empty() const noexcept { return size_ == 0; }
  std::size_t size() const noexcept { return size_; }
  std::size_t capacity() const noexcept { return capacity_; }
};

// Restricción didáctica: T debe ser construible por defecto y asignable.
// No se permite usar std::vector dentro de esta clase.

template<typename T>
void StackRaw<T>::grow() {
    std::size_t newCapacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
    T *newData_ = new T[newCapacity_]; //RESERVA DE MEM
    for(std::size_t i = 0; i < size_; ++i){
        newData_[i] = std::move(data_[i]);
    }
    delete [] data_;
    data_ = newData_;
    capacity_ = newCapacity_;
}

template<typename T>
StackRaw<T>::StackRaw(const StackRaw &other) 
      : data_(other.capacity_ > 0 ? new T[other.capacity_] : nullptr), 
        size_(other.size_), 
        capacity_(other.capacity_) {
    for (std::size_t i = 0; i < size_; ++i)
        data_[i] = other.data_[i];    
}

template<typename T>
StackRaw<T>::StackRaw(StackRaw &&other) noexcept 
      : data_(other.data_), 
        size_(other.size_), 
        capacity_(other.capacity_){
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    
  // TODO: transferir ownership y dejar el origen vacío.
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(const StackRaw &other) {
    if (this != &other){
        T* newData = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i)
            newData[i] = other.data_[i];
        delete[] data_;
        data_ = newData;
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    return *this;        
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(StackRaw &&other) noexcept {
    if (this != &other){
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

  // TODO: liberar el recurso actual, transferir ownership y vaciar el origen.
  return *this;
}

template<typename T>
StackRaw<T>::~StackRaw() {
  delete[] data_;
}

template<typename T>
void StackRaw<T>::push(const T &x) {
    if (size_ == capacity_)
        grow();
    data_[size_] = x;
    ++size_;
  //throw std::logic_error("TODO StackRaw::push(const T&)");
}

template<typename T>
void StackRaw<T>::push(T &&x) {
    if (size_ == capacity_)
        grow();
    data_[size_] = std::move(x);
    ++size_;
  //throw std::logic_error("TODO StackRaw::push(T&&)");
}

template<typename T>
void StackRaw<T>::pop() {
    if (empty())
        throw std::out_of_range("Stack is empty");
    --size_; 
  //throw std::logic_error("TODO StackRaw::pop");
}

template<typename T>
T &StackRaw<T>::top() {
    if (empty())
        throw std::out_of_range("Stack is empty");
  
    return data_[size_ - 1];
  //throw std::logic_error("TODO StackRaw::top");
}

template<typename T>
const T &StackRaw<T>::top() const {
    if (empty())
           throw std::out_of_range("Stack is empty");
    return data_[size_ - 1];
  //throw std::logic_error("TODO StackRaw::top const");
}
