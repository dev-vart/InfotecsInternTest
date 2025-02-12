Моя попытка пройти на программиста-стажера "Разработчик С++" в компанию Infotecs. Не увенчалась успехом - отказ. В ридми: полное условие задания и ответ от компании после выполнения.

Тестовое задание для стажера на позицию «Программист на языке C++»

Задание состоит из двух программ, которые необходимо реализовать. Взаимодействие программ должно быть реализовано через использование linux-сокетов.

Программа №1. 

Должна состоять из двух потоков и одного общего буфера.

Поток 1.  Принимает строку, которую введет пользователь.  Должна быть проверка, что строка состоит только из буквенных символов и не превышает 64 символа. После проверки необходимо подсчитать все вхождения каждого символа в исходную последовательность. 
Результат поиска необходимо передать в общий буфер и поток должен ожидать дальнейшего ввода пользователя.

Поток 2. Должен обрабатывать данные, которые помещаются в общий буфер. После получения данных общий буфер затирается. Поток должен вывести полученные данные на экран и  отправить в Программу №2. После этого поток ожидает следующие данные.

Примечание №1 по Программе №1: Взаимодействие потоков должно быть синхронизировано,  поток №2  не должен постоянно опрашивать общий буфер. Механизм синхронизации не должен быть глобальной переменной.

Примечание №2 по Программе №1: Работа программы должна быть максимально независима от статуса запуска программы №2. Это значит, что внезапный останов программы №2 не должен приводить к немедленным проблемам ввода у пользователя.
При перезапуске программы №2 необходимо произвести переподключение.

Программа №2. 

Ожидает данные от  Программы №1. При получении  данных, происходит анализ преданной строки и выводится в консоль все символы в порядке возрастания количества этих символов. Далее программа продолжает ожидать данные.

Примечание №1 по Программе №2: Работа программы должна быть максимально независима от статуса запуска программы №1. Внезапный останов программы №1 не должен приводить к немедленным проблемам отображения. Необходимо ожидать подключение программы №1 при потере связи между программами.

Примечание по заданию: Не обязательно все размещать в одном классе. Может быть разработана иерархия классов. Чем более функционален интерфейс класса, тем лучше.


Требования к присылаемым решениям.
-	Готовое задание должно быть передано ответным письмом в zip архиве.
-	Каждая из программ должна находиться в своей папке. 
-	Для сборки программа не должна требовать настроек системы или нахождения определенных файлов в специфичном месте. 
-	Исходный код должен компилироваться средствами cmake с использованием gcc для работы в среде Linux. В папке с исходным кодом не должно быть мусора: неиспользуемых файлов исходных кодов или ресурсов, промежуточных файлов сборки и т.д.
-	Максимальное время на выполнение задания –  1 неделя.

Мы проверили ваше тестовое задание. К сожалению, в данный момент мы не готовы пригласить вас на собеседование.

Фитбэк по заданию такой.

Плюсы:

·         Проект собирается с помощью cmake.
·         Проект выполняет поставленную задачу.
·         Программы корректно завершаются при различных ситуациях.
·         Присутствует информирование пользователя.
·         Для синхронизации потоков использован std::condition_variable и unique_lock
·         Грамотная работа с сетевым взаимодействием.
·         Используются структуры STL.
·         Использованы стандартные инстрменты
·         Присутствуют комментарии

Минусы:

·         Отсутствует гибкость в программах.
·         Недостаточное применение STL
·         Присутствие утечек памяти
·         Нарушение принципов ООП.
·         Нарушение принципов разработки многопоточных программ
·         Отсутствие RAII.
·         Отсутствие обработки исключений.
·         Отсутствие констант
·         Присутствие лишних аллокаций.
·         Отсутствие README.md
·         Отсутствие тестов.

Вакансия закрылась до того, как мне ответили, так что, скорее всего, просто нашли другого кандитата. Надеюсь эта репа поможет кому-то, кто будет пытаться попасть в Infotecs
