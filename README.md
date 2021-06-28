[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=4399006&assignment_repo_type=AssignmentRepo)
Ваша задача реализовать методы `insert` и `remove` в файле `tree/tree.cpp`. Дерево в данной задаче реализует множество, то есть хранит только "ключи", а не пары ключ-значение.

Метод `tree::insert` добавляет в множество (дерево) новое число и возвращает вершину, в котором это число лежит. Если число уже есть в дереве, ничего добавлять не нужно, а вернуть нужно указатель на имеющуюся вершину.

Метод `tree::remove` удаляет из множества (дерева) указанное число. Возвращает `true`, если такое число присутствовало, и `false`, если числа не было, и удалять не пришлось.

В отличие от той версии, которую я показывал на лекции, каждый узел хранит указатель на родителя. В таком варианте проще реализовать удаление вершины.

Для удобства перечислю ссылки на визуализацию:

1. https://visualgo.net/ru/bst?slide=1
2. https://www.cs.usfca.edu/~galles/visualization/BST.html

* Реализация, которую я на лекции показывал - http://coliru.stacked-crooked.com/a/164f0ea1e5c1c802
* Реализация на python: http://aliev.me/runestone/Trees/SearchTreeImplementation.html
