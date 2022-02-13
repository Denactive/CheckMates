< [Назад](https://github.com/Denactive/CheckMates/)

# <a name="top"></a>Проект CheckMates. Back-end #
## Разработчики ##
- [Очеретная Светлана](https://github.com/Svetlanlka)

## Документация ##
[Макет приложения](https://drive.google.com/drive/folders/1I9MokbBB8PtqO_jTt9GI3MAKg7JIRCas)

## Требования ##
- Linux Ubuntu 20.04.2 или Windows 10
- QT 6 и выше
- Cmake 3.11 и выше

## Сборка ##
Приложение не способно установить соединение с сервером.

Используйте [Тестовый клиент](../server#test).

Сборка на Linux:
    0. Установить QT 6, указать путь до библиотеки в $path
    1. mkdir tmp && cd tmp/
    2. cmake ..
    3. make
    4. ./client
Сборка на Windows (Visual Studio):
    0. Установить QT 6
    1. Создать пустой проект
    2. Установить стандарт языка С++17 в свойствах проекта
    3. Указать путь до файлов библиотеки QT в "подключаемых каталогах"
    4. Ctrl + F5
