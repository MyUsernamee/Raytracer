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

sudo apt install cmake ninja-build -y

echo "Done."