#include "checkersfield.h"

CheckersField::CheckersField(bool isUsed)
{
    this->setMinimumSize(60, 60);
    this->setMaximumSize(60, 60);
    this->setFlat(true);
    this->setAutoFillBackground(true);
    this->setIconSize(QSize(60,60));
    this->setStyleSheet("border: none;");
    if (isUsed)
        setState(FieldState::Free);
    else
        setState(FieldState::Null);
}

void CheckersField::setState(FieldState state)
{
    this->_state = state;
    switch (state) {
        case FieldState::Free:
            this->setIcon(QIcon(FREE_IMG));
            break;
        case FieldState::White:
            this->setIcon(crowded() ? QIcon(WHITE_CROWDED_IMG) : QIcon(WHITE_IMG));
            break;
        case FieldState::Black:
            this->setIcon(crowded() ? QIcon(BLACK_CROWDED_IMG) : QIcon(BLACK_IMG));
            break;
        default: this->setEnabled(false);
            this->setIcon(QIcon(NULL_IMG));
            break;
    }
}

void CheckersField::setCrowded(bool isCrowded)
{
    _crowded = isCrowded;
//    setState(this->_state);
}

bool CheckersField::crowded()
{
    return _crowded;
}

FieldState CheckersField::state() {
    return this->_state;
}
