Задачи по программированию. I семестр
=========
<h2>☑ Задача 1. Перевернуть строку неизвестной длины</h2>
<h4>Считывать из стандартного ввода символы до двух ‘ ‘. Распечатать их в обратном порядке. Длина строки больше 256 символов.</h4>
=========
<h2>☑ Задача 2. Перевернуть список</h2>
<h4>Дан односвязный список. Перевернуть его в обратном направлении. Исходный список можно портить.</h4>
=========
<h2>☑ Задача 3. Найти значение k-ого по возрастанию элемента массива</h2>
<h4>На входе массив чисел и номер k. Не использовать сортировку, асимптотическая сложность - O(N). Массив можно портить.</h4>
=========
<h2>☑ Задача 4. Перевернуть биты в индексах массива</h2>
<h4>На входе массив длины 2^N. Переставить местами значения в ячейках массива, так чтобы в на индексах массива были произведен бит-реверс. То есть переставить A[0101]-A[1010].</h4>
=========
<h2>? Задача 5. Умножить 2 матрицы NxN</h2>
<h4>На входе 2 матрицы NxN с коэффициентами с плавающей точкой двойной точности. Вычислить произведение матриц. Сравнить асимптотическую сложность с измеренным временем работы. Определить влияние на время работы транспонирования матриц.</h4>
=========
<h2>☑ Задача 6. Игра в числа</h2>
<h4>Петя с Васей играют в числа. Петя загадывает число от 1 до 100 включительно. Вася называет числа до тех пор пока не угадает. Если число меньше загаданного, Вася получает 1 щелбан, если больше, то 2 щелбана. Определить какое минимальное количество щелбанов в худшем случае получит Вася при оптимальном алгоритме игры. Написать программу, реализующую оптимальную оценку в худшем случае. Проверить на всех входных значениях.</h4>
=========
<h2>? Задача 7. Вытесняющий стек</h2>
<h4>Реализовать стек для значений типа байт с использованием 2N ячеек оперативной памяти. При заполнении всех ячеек данные должны перемещаться в файл, таким образом, чтобы время между последовательными доступами к файлу было максимальным при наихудшей последовательности операций со стеком.</h4>
=========
<h2>Задача 8. Быстрая сортировка</h2>
<h4>Реализовать быструю сортировку используя не более одного рекурсивного вызова, не переставляя элементы в отсортированном массиве. Для массивов близких к сортированному время работы должно быть близко к среднему.</h4>
=========
<h2>☑ Задача 9. Кольцевая гонка</h2>
<h4>Проверить наличие или отсутствие цикла в односвязном списке за линейное время от длины списка. Данные списка нельзя портить. Можно использовать константное количество памяти.</h4>
=========
<h2>☑ Задача 10. Трансформация дерева</h2>
<h4>На входе префиксное выражение из букв и бинарных операций +-*/, например (**a/bc+de). Преобразовать к инфиксной форме, с использованием только необходимых скобок - a*(b/c)*(d+e). Запрещена замена операций и изменение их порядка по сравнению с префиксной записью.</h4>
=========
<h2>☑ Задача 11. Поиск минимума разности</h2>
<h4>На входе последовательность чисел с плавающей точкой двойной точности и положительное число D. Одинаковые числа на входе игнорируются. Считывать до тех пор пока расстояние между любыми двумя соседними в порядке сортировки числами больше D. Вывести в порядке сортировки. Пример: на входе D = 1.0; 0.0, 2.0, 4.0, 0.0, 6.0, 1.0, 7.0, 6.0; ответ: 0.0, 1.0, 2.0, 4.0, 6.0</h4>
=========
<h2>☑ Задача 12. Подсчет слов</h2>
<h4>На входе последовательность слов. Подсчитать количество повторений каждого слова.</h4>
=========
<h2>? Задача 13. Коммутативный хэш</h2>
<h4>Реализовать структуру для хранения ребер неориентированного графа со сложностью добавления и удаления О(1).</h4>
=========
<h2>Задача 14. Избыточность сети</h2>
<h4>На входе неориентированный связный граф, заданный списками смежности вершин. Найти в нем двусвязные компоненты, мосты и точки сочленения.</h4>
=========
<h2>Задача 15. Расписание</h2>
<h4>Построить оптимальное расписание выполнения заданий, связанных по данным для одного процессора. На входе ориентированный ациклический граф с весами на вершинах, заданный списками смежности вершин. Вершины графа - задания, ребра - связи по данным, веса вершин - время исполнения заданий. Вывести расписание в виде списка пар чисел (номер задания, время начала выполнения).</h4>
=========
<h2>? Задача 16. Ханойские башни по-новому</h2>
<h4>Для заданного N - количества дисков распечатать последовательность переносов дисков для задачи Ханойские башни. Программа должна требовать O(1) памяти. Проверить совпадение результатов с рекурсивной версией.</h4>