< [Назад](https://github.com/Denactive/CheckMates/#top

# <a name="backend"></a>Проект CheckMates. Back-end #
## Разработчики ##
- [Кириллов Денис](https://github.com/Denactive)
- [Любский Юрий](https://github.com/yurij-lyubskij)

## Документация ##
Открыть можно в [drawio](https://app.diagrams.net)
[UML](https://drive.google.com/drive/folders/18x52xWfRX_7n567CYJ1daEaKte2um9FB)

## Требования ##
- Linux Ubuntu 20.04.2 или Windows 10
- Boost 1.76
- Cmake 3.11 и выше

## Сборка ##
Сборка на Linux:
0. Установить Boost::beast и Boost::asio, указать путь до библиотеки в $path
1. mkdir tmp && cd tmp/
2. cmake ..
3. make
4. ./server
Сборка на Windows (Visual Studio):
0. Установить Boost::beast и Boost::asio
1. Создать пустой проект
2. Установить стандарт языка С++17 в свойствах проекта
3. Указать путь до файлов библиотеки Boost в "подключаемых каталогах"
4. Ctrl + F5

## <a name="test"></a>Тестовый клиент ##
Требования в ПО аналогичны требованию ПО сервера.

CMakeList.txt не прилагаю.

Исходник находится [тут](./test_client/FullClient.cpp).
