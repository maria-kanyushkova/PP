#Лабораторная работа №7.

>Инкапсуляция работы потока

##Цели и задачи

Подготовить класс, инкапсулирующий логику работы с потоком.

##Постановка задачи

Реализовать класс, реализующий интерфейс IWorker с методами:

1. bool ExecuteTask( ITask) - выполняет метод ITask::Execute в потоке. Если в настоящее время поток выполняет другую задачу, то текущая задача должна завершиться. Возвращает true - если задача успешно выполнилась, иначе false.

2. IsBusy() - возвращает true, если поток выполняет какую-либо операцию, либо false.

При удалении объекта класса IWorker объект должен дожидаться окончания выполнения текущей задачи. Новые задачи приниматься не должны. Объекты, которые ожидали выполнение задач должны получить корректный сигнал, что их задачи выполнены не будут.

При помощи объектов классов IWorker и ITask реализовать задание из Лабораторной номер 1. Графики строить не нужно. Классы IWorker и ITask будут использоваться в следующей лабораторной.

##Требования

1. Программа должна быть реализована в виде консольного приложения и использовать Windows SDK, язык программирования – С++