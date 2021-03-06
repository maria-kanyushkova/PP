#Лабораторная работа №4.

>Планировщик ОС. Приоритеты потоков. Углубленный уровень.

##Цели и задачи

Познакомиться с работой планировщика операционной системы, исследовать порядок работы потоков от количества доступных ядер, приоритетов потоков.

##Постановка задачи

На основе лабораторной работы номер 2 разработать программу, которая выводит время выполнения каждой операции (обработка одного пикселя) в миллисекундах от начала работы программы и порядковый номер для каждого потока в файл. На основе полученных данных построить в Excel наглядные Plot диаграммы (см пример рядом с заданием).

##Требования

1. Программа должна быть реализована в виде консольного приложения и использовать Windows SDK, язык программирования – С++. Имена входного и выходного bmp-файла указываются в качестве параметров командной строки.

2. Количество потоков выполнения, количество ядер, на которых разрешена обработка, и приоритеты потоков должны передаваться в командной строке. Формат командной строки произвольный, подсказка должна выводиться по параметру “/?” или при запуске без параметров.

3. Построить в Excel графики указанных ниже параметров.

    1. Количество процессоров 1, количество потоков 3, одинаковые приоритеты потоков.
    
    2. Количество процессоров 1, количество потоков 3, первый поток приоритет above_normal, второй поток приоритет normal, третий поток приоритет normal.
    
    3. Количество процессоров 1, количество потоков 3, первый поток приоритет above_normal, второй поток приоритет normal, третий поток приоритет below_normal.

    4. Повторить a-c для количества процессоров 2 и 3

4. Написать выводы: Объяснить отличие графиков при разных приоритетах потока и разном количестве ядер.