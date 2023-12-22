#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>
#include <concepts>


namespace list {
  template<typename T, typename... Args>
  concept sameTypes = (std::is_same_v<T, Args> && ...);  

  template<typename T>
  class _element {
    public:
      using _ptr = std::shared_ptr<_element<T>>;
      
      _element(T val)
        : _value(val) {}

      void setPrev(_ptr& prev) {
        _refs.first = prev;
      }
      
      void setNext(_ptr& next) {
        _refs.second = next;
      }

      friend std::ostream& operator<<(std::ostream& os, const _element& obj) {
        os << obj._value;
        return os;
      }
      
      T _value;
    private:
      std::pair<_ptr, _ptr> _refs = { nullptr, nullptr };
  };

  template<typename T>
  class linked {
    public:
      template<typename... U>
      requires sameTypes<T, U...>
      linked(U&&... args) 
        : _elements({std::forward<std::shared_ptr<_element<U>>>(std::make_shared<_element<U>>(args))...})
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
        return _elements[index]->_value;
      }

      void remove(const size_t index) {
        _elements.erase(_elements.begin() + index);
      }

      void print() {
        for(size_t i=0; i<_elements.size(); ++i) {
          auto& _current = _elements[i];

          //if previous exists
          if(i > 0) {
            auto& _prev = _elements[i-1];

            std::cout << *_prev << ' ';

          } else { std::cout << "  "; }

          std::cout << *_current << ' ';
          //if next exists
          if(i+1 < _elements.size()) {
            auto& _next = _elements[i+1];
            
            std::cout << *_next << ' ';
          } else { std::cout << "  "; }

          std::cout << std::endl;
        }
        
      } 

    constexpr inline const std::size_t size() const { return _elements.size(); }
    
    private:
      std::vector<std::shared_ptr<_element<T>>> _elements;
  };
}
