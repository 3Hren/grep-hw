grep-hw
=======
Зависимости:
 * c++11
 * boost_system
 * boost_filesystem
 * boost_regex
 * boost_thread

Собирал на gcc-4.7.3 на Ubuntu 13.04
 
[Сборка]:
git clone git://github.com/3Hren/grep-hw.git
cd grep-gw
mkdir build; cd build
cmake ..
make

[Использование:]
./grep-hw [PATH=.]

Например:
./grep-hw
./grep-hw /
./grep-hw /home
