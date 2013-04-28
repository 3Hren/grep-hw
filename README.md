grep-hw
=======
Программа убийца find, grep и (внезапно) wikipedia. Осуществляет поиск 10 наиболее встречающихся слов в текстовых файлах
во всех директориях начиная от **[PATH]** и рекурсивно ниже нее.

Словом считается любая последовательность символов ``[a-zA-Z0-9]``

Если файл или директорию невозможно открыть, выводит сообщение, что-то типа (в данном случае нет прав):
~~~
boost::filesystem::directory_iterator::construct: Permission denied: "/sys/kernel/debug"
~~~

Зависимости:
--------------
 * c++11
 * boost_system
 * boost_filesystem
 * boost_regex
 * boost_thread

Собирал на gcc-4.7.3 на Ubuntu 13.04
 
Сборка:
--------------
~~~
git clone git://github.com/3Hren/grep-hw.git
cd grep-gw
mkdir build; cd build
cmake ..
make
~~~

Использование:
--------------
~~~
./grep-hw [PATH]
~~~

Например:
~~~
./grep-hw
./grep-hw /
./grep-hw /home
~~~

Пример вывода:
~~~
evgeny@ubuntu-home:~/Dropbox/C++/Grep/build$ ./grep-hw /
boost::filesystem::directory_iterator::construct: Permission denied: "/etc/ssl/private"
... <<< МНОГО ПРЕДУПРЕЖДЕНИЙ >>> ...
boost::filesystem::directory_iterator::construct: Permission denied: "/root"
[Word]                            [Count]
the                               5021011
and                               3219400
to                                2422901
of                                2176299
a                                 1546756
he                                1441077
in                                1313539
that                              1184637
his                               1149736
was                               1061491
73.57 s
~~~
