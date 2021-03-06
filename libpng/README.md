# libpng
libpng - это библиотека для работы с растровой графикой в формате PNG. Так как формат PNG использует сжатие, работа с этим форматом вручную может оказаться более сложной, чем, допустим, с форматом BMP. Для того, что бы облегчить себе жизнь, предлагается использовать библиотеку libpng.

**Обратите особое внимание на подход к обработке ошибок и исключительных ситуаций!**

## Установка
Установить библиотеку можно следующей командой
```
sudo apt-get install libpng16-dev
```

## Сборка
При сборке программы необходимо явно указать линковщику на использование этой библиотеки. Для этого используется флаг `-lpng`
Например:
```
gcc my-png-editor.c -lpng
```

## Примеры и ссылки
- Информация по libpng и самому формату: http://www.libpng.org/
- В текущей директории содержится простой пример использования библиотеки libpng
- Более полный пример работы с библиотекой: https://github.com/glennrp/libpng/blob/libpng16/example.c
