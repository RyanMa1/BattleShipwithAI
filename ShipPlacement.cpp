//
// Created by matth on 6/9/2019.
//

#include "ShipPlacement.h"

ShipPlacement::ShipPlacement() :
        rowStart(-1), colStart(-1), rowEnd(-1), colEnd(-1), orientation('1')
{}

int ShipPlacement::getRowStart() const {
    return rowStart;
}

int ShipPlacement::getColStart() const {
    return colStart;
}

int ShipPlacement::getRowEnd() const {
    return rowEnd;
}

int ShipPlacement::getColEnd() const {
    return colEnd;
}

char ShipPlacement::getOrientation() const {
    return orientation;
}

int ShipPlacement::getShipSize() const {
    return shipSize;
}
