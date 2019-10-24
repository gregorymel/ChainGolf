# ChainGolf

#### Environment project for blockchain implementation on [UTON HACK](http://utonhack.com/).

# English

## Task
 
Write the shortest and most concise blockchain, with its own cryptocurrency.
The application implemented must be a blockchain node that supports JSON-RPC requests.
The network resulting from the running nodes must be able to perform transactions and viewing of wallet
balance.

The amount of cryptocurrency must always be an integer number (assuming that we can only
work with an integer amount of currency). For simplicity reasons, we assume that the address of
wallets is a natural number less than 1e6. The genesis block should contain a record about the
emission of 1e6 currency units into the wallet with the address 0. Also, to simplify the task, we will
refuse from digital signatures of transactions in principle, and assume that each request
received via RPC is fair (but not necessarily valid).

## Interface provided by node 
RPC-server that will receive requests in JSON format and response in
JSON format.

Supported queries and their syntax (the same names indicate the same values):

##### transfer

    {"method": "transfer", "params": [_from_address_, _to_address_, _amount_], "id": _number_ }
    
    {"jsonrpc" "2.0", "result": "ok", "id": _number_} - if successful
    
    {"jsonrpc" "2.0", "result": "fail", "id": _number_} - in case of failure
    
##### get_balance

The "get_balance" method is responsible for getting the balance on the specified purse.

    {"method": "get_balance", "params": [_address_], "id": _number_}
    
    {"jsonrpc." "2.0", "result": _money_amount_number_, "id": _number_}

All queries and responses must be valid [JSON RPC](https://www.jsonrpc.org/specification) messages,
all parameters are integer numbers.


## Launch and Testing

Application language: C++. C++17 and the currently implemented features
of C++20 of the GNU Gcc 9.2 implementation will be available. Static libraries Boost 1.71.0,
OpenSSL 1.1.1 and JSON RPC (https://github.com/cinemast/libjson-rpc-cpp) will be available for
including and linking. The entire application source code must be provided in a single file:
main.cpp. Build will be performed with the help of the build.sh bash script, the main meaning of
which is expressed in the following command:

    g++ main.cpp -o node.out -fPIC -lboost... -lssl -ljsonrpc -pedantic -O2 -std=c++2a

where -lboost... - all available statically assembled Boost modules.
The include files of Boost, OpenSSL and Json-RPC will be installed in /usr/include just like via apt
get install. So, for e.g., the boost asio will be available as #include <boost/asio.hpp>.

## Applications are executed with 

- root rights in Ubuntu 18.04 64-bit;
- at least 512 MB RAM for each node individually;
- at least 10GB of SSD space;
- Intel Core i7 4.7 GHz;
- networking between nodes.

There will be no access for the nodes to the Internet.

Several instances of the application, provided by the participant, will be launched using virtualization. 
The first instance will be launched at the IP address 192.168.2.3. Other instances of
the application will be launched at an unknown IP address (not necessarily in local network).
During the testing, the queries to these working instances will be performed, the syntax of which is
described above.

The number of running instances of the application is unknown in advance, but it will be at least 5.
No RPC requests will be received during the first 5 seconds launch of all nodes: it is assumed
that the nodes will create a P2P network and synchronize during this time. After this period of time the
active testing phase will be performed: cases of extreme network behavior (jitter, packet reordering,
packet loss, packet corruption, etc.) will be simulated; forced shutdown of one or more instances
will also be carried out, after which the validity of the remaining network will be checked.

Transaction time limit: 0.5 seconds. After this time (if there is no interference in the network), all
nodes should be informed that the transaction was successfully completed. This is the maximum
time limit per transaction: if the duration of the transaction exceeds this limit, the transaction will be
considered as not completed. Note that this is the maximum time per transaction: the transaction
speed will also be evaluated.

## Evaluation criteria

- Size, purity and elegance of the source code. Each source code file will be passed through
the Clang-Format utility using Google Code Style. Then a visual
check of the purity and brevity of the code will be performed by a jury. The
use of C++17, C++20 and minimum number of warning-like features in gcc pedantic mode
is welcome.
- Security of the obtained network. The resulting network must meet the basic principles of
blockchain: decentralization, resistance to various kinds of network abnormalities (failure of
some nodes, network errors, etc.).
- Special attention will be paid to the selected and implemented consensus. We hope that the
established limit on the duration of the transaction will encourage you to implement not
PoW-consensus.
- Resource consumption of nodes
- Scope of work.

The results should be provided in the following format: your_team_name.tar.gz, which will contain
2 files:
1) main.cpp - containing the implementation of the node
2) node.out is an ELF-executable file built for the x86-64 platform, PIC, statically linked.

#### Good luck!


# Русский

## Задание 

Написать самый короткий и лаконичный блокчейн с собственной криптовалютой.

Реализуемое приложение должно представлять собой блокчейн-узел, который поддерживает
выполнение запросов по протоколу JSON-RPC. Сеть, получаемая в результате работы узлов,
должна уметь осуществлять транзакции и просмотр баланса пользователей сети.

Количество полученной криптовалюты должно представлять собой целое число
(предполагаем, что мы можем работать только с целым числом валюты). Для простоты будем
предполагать, что адреса кошельков – натуральные числа, меньшие 1e6. В генезис блоке
сети должна содержаться запись об эмиссии 1e6 единиц валюты в кошелек с адресом 0.
Также, для упрощения задачи, откажемся от цифровых подписей транзакций в принципе и
будем предполагать, что каждый запрос, полученный по RPC, является честным.

## Предоставляемый интерфейс 
RPC-сервер, который будет получать запросы в формате JSON, и отвечать на них в формате JSON.

Поддерживаемые запросы и их синтаксис (одинаковыми названиями обозначены одинаковые
значения):

##### transfer

    {"method": "transfer", "params": ["from_address", "to_address", "amount"], "id": _number_ }
    
    {"jsonrpc" "2.0", "result": "ok", "id": _number_} – в случае успеха
    
    {"jsonrpc" "2.0", "result": "fail", "id": _number_} – в случае неудачи (например, если недостаточно средств для операции)
    
##### get_balance

Метод «get_balance» отвечает за получение баланса на указанном кошельке.

    {"method": "get_balance", "params": ["_address_"], "id": _number_}
    
    {"jsonrpc." "2.0", "result": _money_amount_number_, "id": _number_}

Все запросы и ответы должны являться валидными [JSON RPC](https://www.jsonrpc.org/specification) сообщениями.
Все параметры в запросах - целые числа.

## Запуск и Тестирование

Язык реализации приложения: C++. Будут доступны возможности C++17 и C++20 в
реализации GNU Gcc 9.2. При линковке будут доступны статические библиотеки
Boost 1.71.0, OpenSSL 1.1.1, JSON RPC (сборка кода с https://github.com/cinemast/libjson-rpc-
cpp). Весь исходный код приложения должен быть предоставлен в единственном файле:
main.cpp. Сборка будет происходить при помощи Bash-скрипта build.sh, основная смысловая
нагрузка которого выражена в следующей команде:

    g++ main.cpp -o node.out -fPIC -lboost... -lssl -ljsonrpc -pedantic -O2 -std=c++2a

, где -lboost... – все доступные статически собранные модули Boost.
Заголовочные файлы библиотек будут установлены в /usr/include так, как если бы пакеты Boost, OpenSSL,
JsonRPC устанавливались через apt-get: например, header Boost Asio будет доступен 
при помощи директивы #include <boost/asio.hpp>.

В runtime приложениям будет доступно:
- права root на Ubuntu 18.04 64-bit;
- 512 MB RAM для каждой ноды в отдельности;
- минимум 10GB места на SSD-накопителе
- Intel Core i7 4.7 GHz;
- сетевое взаимодействие между узлами.

Доступ к сети Internet будет отсутствовать.

При помощи виртуализации будет запущено несколько экземпляров приложения, предоставленного участником. Первый экземпляр будет запущен по IP-адресу 192.168.2.3.
Каждый следующий экземпляр приложения будет запущен по неизвестному заранее IP-адресу. В ходе тестирования к данным работающим экземплярам будут выполняться запросы,
интерфейс которых описан выше. 

Число запущенных экземпляров приложения заранее неизвестно, однако оно будет не менее5. Первые 5 секунд после запуска всех узлов не будет поступать никаких RPC-запросов:
предполагается, что в это время узлы будут создавать P2P сеть и синхронизироваться. После
данного промежутка времени будет осуществляться фаза активного тестирования: будут
моделироваться экстремальные случаи поведения сети (jitter, packet reordering, packet loss,
packet corruption и др.); также будет осуществляться принудительное завершение работы
одного или нескольких экземпляров, после чего будет происходить проверка на
жизнеспособность оставшейся сети.

## Ограничение по времени на транзакцию

0.5 секунды. Спустя это время (при отсутствии
помех в сети), все узлы должны иметь информацию о том, что данная транзакция успешно
проведена. Это максимальное ограничение по времени на одну транзакцию: если
длительность проведения транзакции будет превышать данное ограничение, транзакция
будет считаться непроведенной. Отметим, что это максимальное время на транзакцию: будет
оцениваться также скорость осуществления транзакций.

## Критерии оценки

- Размер, чистота и элегантность исходного кода. Каждый файл исходного кода будет
пропущен через утилиту Clang-Format с использованием Google Code Style. Затем, жюри будет 
проиводить визуальную оценку чистоты и краткости кода. 
Приветствуется использование возможностей C++17, C++20 и минимальное число 
warning-ов при режиме pedantic в gcc.
- Безопасность полученной сети. Итоговая сеть должна удовлетворять базовым
принципам блокчейна: децентрализация, стойкость к различного рода нештатным
ситуациям сети (выхода из строя некоторых узлов, ошибок в сети и пр.).
- Особое внимание будет уделяться выбранному и реализованному консенсусу.
Надеемся, что установленное ограничение на длительность транзакции подтолкнет
Вас к реализации не PoW-консенсусов.
- Ресурсозатратность узлов
- Объем выполненной работы


Результаты работы должны предоставляться в следующем формате: 
имя_вашей_команды.tar.gz, который будет содержать 2 файла:
1. main.cpp – содержащий реализацию узла
2. node.out – исполняемый ELF-файл, собранный под платформу x86-64, PIC, statically linked.

#### Удачи!