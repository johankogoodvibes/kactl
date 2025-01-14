export CXXFLAGS="-O2 -g -std=c++17 -Wall -Wextra -Wconversion -Wfatal-errors -fsanitize=undefined,address"
alias c='g++ $CXXFLAGS'
function cr(){
    exe=${1%.*}
    make $exe && echo compiled && time ./$exe
}