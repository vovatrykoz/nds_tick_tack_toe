#include <cell.h>

Cell::Cell() : mark(Empty) {};

Cell::setMark(cellMark mark) {
    this->mark = mark;
}