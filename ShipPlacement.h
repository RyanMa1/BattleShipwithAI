//
// Created by matth on 6/9/2019.
//

#ifndef BATTLESHIP_SHIPPLACEMENT_H
#define BATTLESHIP_SHIPPLACEMENT_H


class ShipPlacement {

public:

    ShipPlacement();

    char getOrientation() const;

    int getRowStart() const;

    int getColStart() const;

    int getRowEnd() const;

    int getColEnd() const;

    int getShipSize() const;

    int rowStart, colStart, rowEnd, colEnd, shipSize;
    char orientation;

};


#endif //BATTLESHIP_SHIPPLACEMENT_H
