# BinarySearchTree 

(Восьмая лабораторная работа второго семестра ИТМО).

Реализация трех STL-совместимых контейнеров для [BinarySearchTree](https://en.wikipedia.org/wiki/Binary_search_tree), реализующих различные [способы обхода дерева (in-, pre-, post-order)](https://en.wikipedia.org/wiki/Tree_traversal) через итератор.



### Реализуемые требования

Контейнер предоставляет из себя шаблон, параметрезируемый типом хранимых объектов, оператором сравнения и аллокатором, 
а так же удовлетворяет следующим требованиям к stl - совместимым контейнерам:
  - [контейнера](https://en.cppreference.com/w/cpp/named_req/Container)
  - [ассоциативный контейнера](https://en.cppreference.com/w/cpp/named_req/AssociativeContainer)
  - [контейнера с обратным итератором](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer)
  - [контейнера поддерживающие аллокатор](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer)
  - [oбладает двунаправленным итератом](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator)

Способ обхода дерева реализован через итератор, т.е. оператор "++" приводит к перемещению 
итератора к следующему элементу в дереве, согласно правилу обхода.


### Ограничения

- Стандартные контейнеры не используются.
