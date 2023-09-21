#pragma once

namespace sdlw {

template<typename T>
class MovePtr {
public:
  explicit MovePtr(T *ptr)
    : _ptr{ ptr } {}

  MovePtr(const MovePtr<T> &)            = delete;
  MovePtr &operator=(const MovePtr<T> &) = delete;
  MovePtr &operator=(MovePtr<T> &&other) = delete;

  MovePtr(MovePtr<T> &&other)
    : _ptr{ other._ptr } {
    other._ptr = nullptr;
  }

  T *get() const {
    return _ptr;
  }

private:
  T *_ptr;
};

}
