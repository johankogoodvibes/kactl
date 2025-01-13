alias c='g++ -O2 -g -std=c++17 -Wall -Wextra -Wconversion -Wfatal-errors -fsanitize=undefined,address'
function cr(){
    exe=${1%.*}
    make $exe && echo compiled && time ./$exe
}