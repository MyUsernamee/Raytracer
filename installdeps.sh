chmod +x ./build.sh

echo "This will install vcpkg to your home directory."
echo "It will also install cmake and ninja."
echo "Are you sure you want to continue? (y/n)"
read response

if [ $response != "y" ]; then
    exit 1
fi

cd ~
mkdir testinstall/
cd testinstall/
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
sudo chmod +x bootstrap-vcpkg.sh
./bootstrap-vcpkg.sh
./vcpkg integrate install

cd /opt
curl https://github.com/Kitware/CMake/releases/download/v3.23.0-rc2/cmake-3.23.0-rc2-linux-x86_64.sh
sudo chmod +x cmake-3.23.0-rc2-linux-x86_64.sh

# Create sym link in /usr/local/bin
sudo ln -s /opt/cmake-3.23.0-rc2-linux-x86_64/bin/* /usr/local/bin/

sudo apt install ninja-build -y

echo "Done."