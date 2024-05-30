# Вариант 8

<p align="justify">
Спроектировать базу данных, построить программу, обеспечивающую взаимодействие с ней в режиме диалога, для коллекционера марок, собирающего тематическую коллекцию. 
В БД должны храниться сведения о марках, имеющихся в коллекции, и сведения об их положении в коллекции
</p>

<p align="justify">
Сведения о марках должны включать в себя номер марки, страну выпуска марки, номер серии, тему серии, год выпуска, цвет марки, размер марки, цену марки, тему марки. 
Марки расположены в коллекции по темам. 
Сведения о положении марки в коллекции включают в себя: номер раздела коллекции (разбит на тома по темам и странам), в котором хранится марка, номер тома, номер страницы и уникальное положение марки на странице. 
Возможно открытие новых или закрытие старых тем. Место расположения марки может изменятся.
</p>

Коллекционеру могут потребоваться следующие сведения:
- марки каких стран содержатся в данном разделе;
- в каком томе коллекции находится марка определенной серии;
- в каких местах коллекции находятся марки указанной темы;
- какие темы у серий, включающих марки определенного размера;
- марка какой страны находится в данном месте.

Коллекционер может вносить следующие изменения:
- добавление марки новой темы;
- удаление всех марок одной темы;
- изменение места расположения марки в коллекции;

<p align="justify">
Необходимо предусмотреть возможность выдачи справки о странах, чьи марки находятся в данной теме, и отчета по коллекции (количество и названия тем и стран по разделам, количество марок каждой страны для каждой темы, количество страниц в коллекции)
</p>