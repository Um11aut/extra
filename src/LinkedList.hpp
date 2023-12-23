#pragma once
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>

namespace list {
  template<typename T, typename... Args>
  concept sameTypes = (std::is_same_v<T, Args> && ...);  

  template<typename T>
  class _element {
    public:
    using _ptr = std::shared_ptr<_element<T>>;
    
    _element(T val)
      : value(val) {}    

    void setPrev(_ptr& prev) {
      _refs.first = prev;
    }
    
    void setNext(_ptr& next) {
      _refs.second = next;
    }

    constexpr inline const std::pair<_ptr, _ptr> getRefs() const { return _refs; }
    
    void operator=(const _element<T>& other) {
      value = other.value;
      _refs = other._refs;
    }

    _element<T> copy() {
      _element<T> temp(value);
      return temp;
    }

    friend std::ostream& operator<<(std::ostream& os, const _element& obj) {
      os << obj.value;
      return os;
    }
    
    T value;
    private:
    std::pair<_ptr, _ptr> _refs = { nullptr, nullptr };
  };

  template<typename T>
  class linked {
    public:
    using _ptr = std::shared_ptr<_element<T>>; 

    template<typename... U>
    requires sameTypes<T, U...>
    linked(U&&... args) 
      : _elements({
        std::forward<_ptr>(std::make_shared<_element<U>>(args))...
      })
    {
      for(size_t i=0; i<_elements.size(); ++i) {
        auto& _current = _elements[i];

        //if previous exists
        if(i > 0) {
          auto& _prev = _elements[i-1];

          _current->setPrev(_prev);
        }

        //if next exists
        if(i+1 < _elements.size()) {
          auto& _next = _elements[i+1];
          
          _current->setNext(_next);
        }
      }
    }

    T& operator[](const size_t index) {
      return _elements[index]->value;
    }
    
    _ptr& get(const size_t index) {
      return _elements[index];
    } 

    void remove(const size_t index) {
      //reset ptrs
      if(index > 0) {
        auto& _prev = _elements[index-1];
        _prev->setNext(_elements[index+1]);
      } 
      
      if(index+1 < _elements.size()) {
        auto& _next = _elements[index+1];
        _next->setPrev(_elements[index-1]);
      }

      //erase element
      _elements.erase(_elements.begin() + index);
    }

    void dublicateValues() {
      //dublicating
      std::vector<_ptr> temp;  
      std::for_each(_elements.begin(), _elements.end(), 
                    [&](const auto& el) {
                      temp.push_back(std::make_shared<_element<T>>(el->copy())); 
                    });
      _elements.insert(_elements.begin(), temp.begin(), temp.end());
      
      //reseting ptrs
      for(size_t i=0; i<size(); ++i) {
        if(i>0) {
          get(i)->setPrev(_elements[i-1]);
        }

        if(i+1<size()) {
          get(i)->setNext(_elements[i+1]);
        }
      }
    }

    constexpr inline const size_t size() const { return _elements.size(); }
    
    private:

    std::vector<_ptr> _elements;
  };

  template<typename T>
  static void print(list::linked<T>& list) {
    for(size_t i=0; i<list.size(); ++i) {
      // if prev exists
      if(list.get(i)->getRefs().first != nullptr) {
        std::cout << list.get(i)->getRefs().first->value << ' ';
      } else std::cout << "  ";

      std::cout << list.get(i)->value << ' ';

      // if next exists
      if(list.get(i)->getRefs().second != nullptr) {
        std::cout << list.get(i)->getRefs().second->value << ' ';
      } else std::cout << "  ";
      std::cout << std::endl;
    }
  }
  
}
