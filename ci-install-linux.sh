sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

sudo apt-get install g++
sudo apt-get install cmake

sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp ./lib/libgtest*.a /usr/lib
cd -

sudo apt-get install libgmock-dev
sudo mkdir /usr/src/googletest/googlemock/build
cd /usr/src/googletest/googlemock/build
sudo cmake ..
ls -lh
sudo make
ls -lh
#sudo cp ./lib/libgtest*.a /usr/lib
cd -



- pip install codecov
#sudo apt-get install -y valgrind
#sudo apt-get install -y cppcheck

#gcovr
#Installing python is unnesessary
#sudo apt install -y python3-pip
sudo apt-get install python3-setuptools && sudo pip3 install git+https://github.com/gcovr/gcovr.git

#lcov
sudo apt-get install lcov
