# minishell

+ улучшен parser функции export.
+ добавлено условие для парсера значения
+ парсер, если в строке первый символ символ:)
+ парсер двойных кавычек, но некорректно работают листы
Выдает ошибку при неверном ключе (если первый символ цифра или символ(кроме _), если в ключе есть символы кроме букв, цифр, _). 
Нет функции для очищения и отдельной для ошибки. Ключ и значение записываются в структуру s_list_env, где ключ char *key. Вся строка с ключом char *value. Значение с равно char *str . Нужно добавить функцию для ошибок + записи ерно, придумать структуру для записи после парсинга кавычек и $. Можно возвращать указатель и саму строку? Добавить парсинг одинарных кавычек
