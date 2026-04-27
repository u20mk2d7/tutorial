git add .
git commit -m "update"
git push origin main

rm -rf build/
cmake -S . -B build
cmake --build build
./build/cornerstone
