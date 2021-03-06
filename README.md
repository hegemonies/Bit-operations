http://csc-programming.readthedocs.io/03-bitwise-operations.html
## Лабораторная работа 3: битовые операции
# Проблема
Пусть необходимо хранить большое количество чисел (в оперативной памяти или на диске).
Рассматриваем беззнаковые целые числа в диапазоне [0;221−1][0;221−1].
Наименьший подходящий тип данных для хранения таких чисел — uint32_t.
При использовании этого типа возникает проблема: если данные состоят только из чисел в диапазоне [0;28−1][0;28−1], то из четырех используемых бит значимый только младший, остальные заполнены нулями. Например, последовательность [1, 2, 3, 4] будет представлена следующим образом (для удобства запишем по одному числу в строке):

00000000 00000000 00000000 00000001 

00000000 00000000 00000000 00000010 

00000000 00000000 00000000 00000011 

00000000 00000000 00000000 00000100 

Если бы для хранения чисел был использован один байт, то объем данных можно было бы сократить в 4 раза:

00000001 00000010 00000011 00000100

Однако по условию требуется хранить числа, требующие от 1 до 4 байт. Использовать числа различной разрядности вперемешку нельзя, т. к. в этом случае невозможно однозначно интерпретировать содержимое памяти. Так, последовательность:


00000001 00000010 00000011 00000100


можно интерпретировать различными способами:

00000001 — 1

00000010 — 2

00000011 — 3

00000100 — 4

или как два числа:

00000001 00000010 — 258

00000011 00000100 — 772

или как одно число:

00000001 00000010 00000011 00000100 — 16909060

Появляется потребность в способе кодирования, который позволил бы использовать переменное число байт для хранения различных чисел и при этом был бы однозначно декодируемым.

Решение
Для решения поставленной задачи будем использовать следующий алгоритм:

Числа [0;28−1][0;28−1] будем представлять в виде 0xxxxxxx, «как есть»:

00000000 — 0

00000001 — 1

...

00000101 — 5

...

01111111 — 127

Для бо́льших значений в старшем байте будем хранить столько единиц, сколько байт требуется для представления закодированного числа. 110xxxxx — два, 1110xxxx — три, и т. д. Все последующие байты имеют вид 10xxxxxx.

Биты, обозначенные символами x, заполняются битами кодируемого числа.

Для выбора длины кода можно руководствоваться таблицей:

Количество значащих бит кодируемого числа	Количество байт в коде	Шаблон
7	1	0xxxxxxx

11	2	110xxxxx 10xxxxxx

16	3	1110xxxx 10xxxxxx 10xxxxxx

21	4	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

Пример кодирования числа
Пусть требуется закодировать число 0xa8cc. Число занимает 2 байта, 16 бит. Следовательно, для закодированного числа потребуется 3 байта.

Используем шаблон: 1110xxxx 10xxxxxx 10xxxxxx

Двоичное представление числа 0xa8cc: 1010100011001100

Теперь значащие биты числа нужно подставить в шаблон:

Шаблон:    1110xxxx 10xxxxxx 10xxxxxx

Число:         1010   100011   001100

Результат: 11101010 10100011 10001100

Шестнадцатеричное представление закодированного числа: 0xa8cc

Пример декодирования числа
Выполним обратную операцию. Пусть на входе дан байтовый поток: 11101010 10100011 10001100.

Считываем первый байт: 11101010.

Байт начинается с трех единиц. Следовательно, всего в закодированном числе три байта. Один уже считан, нужно считать еще два: 10100011 10001100.

Шаблон для трехбайтового кода известен, осталось из закодированного числа выделить значащие биты:

Шаблон: 1110xxxx 10xxxxxx 10xxxxxx Считанный код: 11101010 10100011 10001100 Значащие биты: 1010 100011 001100

Декодированное число: 0b1010100011001100 = 0xa8cc.

Потери данных
Во входном потоке возможны потери данных. Например, дана такая последовательность: 10001100 11101010 10100011 10001100. Первый байт имеет вид 10xxxxxx. Такой байт не может быть первым, т.к. в соответствии с алгоритмом кодирования было установлено, что такой вид принимают байты, следующие за первым. Следовательно, часть данных в начале была потеряна. В этом случае можно пропускать байты до тех пор, пока не будет считан байт, обозначающий начало кода.

Обратная ситуация: 11101010 10100011. В этой последовательности первый байт свидетельствует о том, что закодированное представление занимает 3 байта, но по факту присутствует только два. Далее следует либо конец входного потока, либо очередной лидирующий байт. В этом случае неполный код можно игнорировать.

Задание
Разработать приложение для кодирования и декодирования чисел по описанному выше алгоритму.

Пример кодирования:

$ ./coder encode points.txt units.bin
Здесь:

encode — команда кодирования

points.txt — входной текстовый файл, содержащий числа, записанные в шестнадцатеричной системе счисления.

Пример содержимого файла:

7

1e7

79e7

1e79e7

units.bin — выходной бинарный файл.

Пример результата (для просмотра используется утилита hexdump)::
$ hexdump -C units.bin

00000000 07 c7 a7 e7 a7 a7 f7 a7 a7 a7

Пример декодирования:

$ ./coder decode units.bin points.txt
Запуск с некорректным количеством аргументов или некорректной командой:

$ ./coder foobar
Usage:

coder encode <in-file-name> <out-file-name>

coder decode <in-file-name> <out-file-name>

Кодируемые числа считывать в переменную типа uint32_t. Для представления в памяти закодированного числа можно использовать структуру:

enum {
    MaxCodeLength = 4
};

typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnits;
Здесь:

code — закодированные байты, в порядке от старшего к младшему.
length — количество байт в закодированном представлении.
Предлагается следующая структура проекта:

.
|-- Makefile
`-- src
    |-- coder.c
    |-- coder.h
    |-- command.c
    |-- command.h
    `-- main.c`
Файлы command.h и command.c:

int encode_file(const char *in_file_name, const char *out_file_name)
Кодирование текстового файла в бинарный, реализация команды encode.

Параметры:	
char *in_file_name (const) –
путь ко входному текстовому файлу

char *out_file_name (const) –
путь к выходному бинарному файлу

Результат:	
0 в случае успеха, -1 в случае ошибки

int decode_file(const char *in_file_name, const char *out_file_name)
Декодирование бинарного файла, реализация команды decode.

Параметры:	
char *in_file_name (const) –
путь ко входному бинарному файлу

char *out_file_name (const) –
путь к выходному текстовому файлу

Результат:	
0 в случае успеха, -1 в случае ошибки

Файлы coder.h и coder.c:

int encode(uint32_t code_point, CodeUnits *code_units)
Параметры:	
code_point – число, которое необходимо закодировать
code_unit – выходной параметр, результат кодирования
Результат:	
0, если кодирование успешно, -1 иначе

uint32_t decode(const CodeUnit *code_unit)
Допущение: code_unit - корректный код, полученный с помощью функции read_next_code_unit.

Параметры:	code_unit – закодированное представление числа
Return code_point:
 	результат декодирования
int read_next_code_unit(FILE *in, CodeUnits *code_units)
Считывает последовательность code_units из потока in. Implementation note: если считываемый code_unit битый, то функция пропускает байты до тех пор, пока не найдет корректный лидирующий байт.

Результат:	0 в случае успеха, -1 в случае ошибки или EOF
int write_code_unit(FILE *out, const CodeUnit *code_unit)
Примечание: обычно в подобных задачах используется другая декомпозиция. Предлагаемый вариант намеренно упрощен в учебных целях.

Аргументы командной строки
Обработка аргументов командной строки осуществляется через параметры функции main. Прмер:

#include <stdio.h>

int main(int argc, char *argv[])
{
    // argc - количество аргументов
    // argv - массив указателей на строки.
    // Нулевой элемент - командна запуска приложения

    int i;
    for (i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}
Запуск приложения:

$ ./prog first second third
argv[0] = ./prog
argv[1] = first
argv[2] = second
argv[3] = third
Переносимое считывание значений
Для считывания переменных типа unsigned int используется спецификатор %x:

unsigned int var;
fscanf(in, "%x", &var);
В текущей работе мы будем использовать типы фиксированной разрядности: uint32_t, uint8_t. Каждый такой тип является синонимом одного из встроенных типов языка С. Не гарантируется, что uint32_t будет синонимом для unsigned int. Следовательно, использование спецификатора %x может быть непереносимым и вести себя некорректно на других платформах.

Для обеспечения переносимости в заголовочном файле inttypes.h определен ряд макросов вида SCNxN, где N — разрядность переменной. Так, для считывания переменной типа uint32_t следует использовать макрос SCNx32, а для ее вывода PRIx32.

Пример:

#include <inttypes.h>

// В функции считывания данных
uint32_t code_point;

fscanf(in, "%" SCNx32, &code_point);

printf("%" PRIx32, code_point);
После обработки препроцессором в строки могут принять вид:

uint32_t code_point;

fscanf(in, "%" "x", &code_point);

printf("%" "x", code_point);
Подробнее: Fixed width integer types

Источники
Bitwise operations in C — основы
Mask — не всегда удобно устанавливать биты по одному.
man 3 fopen — см. открытие файлов в бинарном режиме
man 3 fread — функции чтения/записи при работе с бинарными файлами
