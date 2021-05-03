# Functions

Максимальный code coverage 92.9% так как есть 2 места, где кидаются исключения и у них есть ветки:
 - исключение поймано
 - исключение не поймано

У нас нет возможности протестировать не пойманное исключение, так как тогда программа завершиться.

# Tree

Невозможно проверить ветки:
 - Исключения в 13 и 17 строке (2 ветки)
 - 12 строка. Нельзя проверить ветки так как нужно получить system_error,
   а файловую систему ломать не хочется. Где тут еще одна ветка теряется -- 
   не понятно, а я весь boost прошел(2 ветки)
 - 16 строка. 2 ветки теряются в boost, хотя там один if судя по библиотеке
 - 19 строка. Нельзя получить другие ветки так как путь уже проверен и нельзя получить 0 в filename (3)
 - 21 - не понятные ветки из boost (5)
 - 23, 30 - возможно, что закончится память, но как это тестить неясно (3)
 - 24, 31 - ветки с исключениями, которые не возможны из-за уже существующих проверок (3)
 - 48 - честно говоря не вижу, где тут может быть 6 веток (3)

Максимально возможный branch coverage - (72 - 23)/72 ~ 68.1%