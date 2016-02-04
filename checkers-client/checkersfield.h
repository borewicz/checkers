#ifndef CHECKERSFIELD_H
#define CHECKERSFIELD_H

#include <QPushButton>

enum FieldState {
    Black,
    White,
    Free,
    Null
};

class CheckersField : public QPushButton
{
    const QString BLACK_IMG = ":/black.png";
    const QString WHITE_IMG = ":/white.png";
    const QString NULL_IMG = ":/null_white.png";
    const QString FREE_IMG = ":/null_black.png";
    FieldState _state;
    using QPushButton::setIcon;
public:
    CheckersField(bool isUsed);
    void setState(FieldState state);
    FieldState state();
    FieldState originalState();
    void setSelected(bool);
    bool isSelected();
};

#endif // CHECKERSFIELD_H
