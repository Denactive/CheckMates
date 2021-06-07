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

#gmock
#sudo apt-get install libgmock-dev
curl -O https://github.com/google/googletest/archive/refs/heads/master.zip
#sudo mkdir /usr/src/googletest/googlemock/build
ls -lh /home/travis/Downloads 
sudo mv /home/travis/Downloads/googletest-master.zip /usr/src/
sudo unzip /usr/src/googletest-master.zip
sudo mv /usr/src/googletest-master /usr/src/googletest
ls -lh /usr/src/googletest
sudo mkdir /usr/src/googletest/googlemock/build
sudo cd /usr/src/googletest/googlemock/
sudo cmake .
sudo make
sudo cp *.a /usr/lib
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
