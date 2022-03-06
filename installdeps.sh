chmod +x ./build.sh

echo "This will install vcpkg to your home directory."
echo "It will also install ninja."
echo "Are you sure you want to continue? (y/n)"
read response

if [ $response != "y" ]; then
    exit 1
fi

cd ~
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
sudo chmod +x bootstrap-vcpkg.sh
./bootstrap-vcpkg.sh
./vcpkg integrate install

echo "export PATH=\"$HOME/vcpkg/bin:\$PATH\"" >> ~/.bashrc
export PATH="$HOME/vcpkg:$PATH"

sudo apt install ninja-build -y

echo "Done."