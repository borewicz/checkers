#ifndef CHECKERSFIELD_H
#define CHECKERSFIELD_H

#include <QPushButton>

enum FieldState {
    Black,
    White,
    CrownBlack,
    CrownWhite,
    Free,
    Null
};

class CheckersField : public QPushButton
{
    const QString BLACK_IMG = ":/black.png";
    const QString WHITE_IMG = ":/white.png";
    const QString BLACK_CROWDED_IMG = ":/black_crowded.png";
    const QString WHITE_CROWDED_IMG = ":/white_crowded.png";
    const QString NULL_IMG = ":/null_white.png";
    const QString FREE_IMG = ":/null_black.png";

    FieldState _state;
    using QPushButton::setIcon;
    bool _crowded = false;
public:
    CheckersField(bool isUsed);
    void setState(FieldState state);
    FieldState state();
    FieldState originalState();
    void setSelected(bool);
    void setCrowded(bool);
    bool crowded();
};

#endif // CHECKERSFIELD_H
