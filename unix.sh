git pull
git add .
git commit -m "update"
git push origin main

#rm -rf build/
cmake -S . -B build
cmake --build build
PROJECT_NAME=$(grep -iE "^ *project" CMakeLists.txt | cut -d '(' -f2 | awk '{print $1}' | tr -d ')')
./build/"$PROJECT_NAME"
