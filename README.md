# scala-compiler

Учебный компилятор подмножества Scala 2.13. В текущей версии реализованы лексический анализ,
синтаксический разбор Bison, построение AST и два варианта DOT-визуализации дерева.

## Требования

- Windows;
- MSYS2 MinGW-w64 с `g++` (стандарт C++17);
- Python 3 для BiVi;
- Graphviz (`dot`) только для преобразования DOT в SVG.

Flex и Bison 3.8.2 находятся в `files/win_flex_bison-2.5.25`.
Заголовок `FlexLexer.h` также берётся из этого каталога.

## Сборка

Из корня проекта:

```bat
build.bat
```

Скрипт:

1. генерирует `parser/parser.tab.c` и `parser/parser.tab.h`;
2. генерирует `lexer/lexer.cc`;
3. собирает `scala-compiler.exe` из лексера, парсера, AST и `main.cpp`.

## Визуализация

```bat
visualize.bat tests\frontend.scala
```

Результаты сохраняются в `out`:

| Файл | Содержимое |
|---|---|
| `example_parsing.txt` | отладочный trace Bison (`yydebug = 1`) |
| `parse_tree.dot` | полное дерево разбора, восстановленное BiVi из trace |
| `ast.dot` | семантическое AST, созданное действиями правил |
| `parse_tree.svg` | BiVi-дерево, если установлен Graphviz |
| `ast.svg` | AST, если установлен Graphviz |

BiVi показывает **конкретное дерево разбора**: терминалы, пунктуацию, `NL` и вспомогательные
нетерминалы. `ast.dot` показывает более компактное **AST** для последующих стадий компилятора.

Если Graphviz установлен, файлы можно создать вручную:

```bat
dot -Tsvg out\parse_tree.dot -o out\parse_tree.svg
dot -Tsvg out\ast.dot -o out\ast.svg
```

Без `visualize.bat` последовательность команд такая:

```bat
scala-compiler.exe tests\frontend.scala > out\ast.dot 2> out\example_parsing.txt
python files\BiVi-bison-visualizer\bivi.py out\example_parsing.txt > out\parse_tree.dot
```

## AST

Каталог `nodes/` повторяет архитектуру компилятора из примера `scala_compiler`:

- `nodes/Node.h` — базовый узел с `id`, `toDot()`, `getDotLabel()` и `getChildren()`;
- `nodes/Types.h` — перечисления типов модификаторов, выражений, литералов и объявлений;
- `nodes/nodes.h` — общий заголовок всех узлов;
- тематические каталоги: `id`, `modifier`, `type`, `var`, `func`, `definitions`, `stats`,
  `templates`, `class`, `exprs`, `generator`, `try`, `import`.

В конкретных классах используются собственные типизированные поля. Например:

- `ClassDefNode` хранит `fullId`, `modifiers`, `classParams` и `classTemplateOpt`;
- `FunDefNode` хранит `funSig`, возвращаемый тип и тело;
- `SimpleExpr1Node` содержит отдельные поля для целого, `double`, строки, `char`, `bool`,
  идентификатора, вызова метода и литералов;
- `ExprNode` содержит типизированные поля ветвей `if`, циклов, `try` и перечислений `for`.

Создание узлов выполняется непосредственно в семантических действиях `parser/parser.y`.
`%union` содержит отдельный тип указателя почти для каждого нетерминала. `%destructor`
удаляет незавершённые поддеревья при синтаксической ошибке, а `deleteNodeTree()` освобождает
успешно построенное дерево в `main.cpp`.

## Лексер

`lexer/lexer.l` поддерживает два режима:

- в составе `scala-compiler.exe` возвращает токены и значения `yylval` парсеру;
- с макросом `SCALA_LEXER_STANDALONE` сохраняет прежний текстовый вывод для lexer-тестов.

Если между токенами вставляется несколько `NL`, используется очередь: сначала парсер получает все
`NL`, затем реальный токен вместе с сохранённым semantic value.

Автономная сборка и тесты:

```bat
cd lexer
build.bat
run_tests.bat
```

## Проверочные входные файлы

- `tests/frontend.scala` — комплексный разбор с классами, объектом, наследованием, массивами,
  циклами, исключениями, `new` и разными выражениями;
- `lexer/test.scala` — обычный объект с методами и переменными;
- `lexer/tests/input` — отдельные лексические тесты.

В грамматике остаются два ожидаемых shift/reduce-конфликта для `catch` и `finally` у вложенного
`try`; Bison разрешает их сдвигом. Поэтому используется `%expect 2`.

Смотреть - https://graph.flyte.org/