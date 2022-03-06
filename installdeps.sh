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

# If the export for vcpkg is alread in the .bashrc file, we don't need to do anything
if ! grep -q "export PATH=\"$HOME/vcpkg:\$PATH\"" ~/.bashrc; then
    echo "export PATH=\"$HOME/vcpkg:\$PATH\"" >> ~/.bashrc
    export PATH="$HOME/vcpkg:$PATH"
fi

if ! grep -q "export VCPKG_ROOT=\"$HOME/vcpkg\"" ~/.bashrc; then
    echo "export VCPKG_ROOT=\"$HOME/vcpkg\"" >> ~/.bashrc
    export VCPKG_ROOT="$HOME/vcpkg"
fi


sudo apt install ninja-build -y

echo "Done."