//
// Created by Elias on 30/09/2024.
//

#include "DraggedPiece.h"
#include "BoardValues.h"
#include "EngineBase/EngineBase.h"
#include "Board.h"

DraggedPiece::DraggedPiece(uint64_t fromLocation)
{
    fromLocation_ = fromLocation;
    int position = 0;
    while ((fromLocation & 1) == 0)
    {
        fromLocation >>= 1;
        position++;
    }
    idToUpdate_ = position;
    location_ = EngineBase::getMousePosition();
    offset_ = std::make_pair((location_.first - LEFTMARGIN) % TILESIZE, (location_.second - TOPMARGIN) % TILESIZE);
    originalLocation_ = location_;
    originalLocation_.first -= offset_.first;
    originalLocation_.second -= offset_.second;
    EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, idToUpdate_, SecondaryCMD::Z, 2});
    EngineBase::executeCommand(Command(PrimaryCMD::DONEWRITING));
    EngineBase::executeCommand(Command(PrimaryCMD::SORTDRAWABLES));
}

uint64_t DraggedPiece::updateLocation()
{
    if (EngineBase::mouseButtonReleased(ENGINEBASE_BUTTON_LEFT))
    {
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, idToUpdate_, SecondaryCMD::X,
            (float)originalLocation_.first
        });
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, idToUpdate_, SecondaryCMD::Y,
            (float)originalLocation_.second
        });
        location_.first = (int)(location_.first - LEFTMARGIN);
        location_.second = (int)(location_.second - TOPMARGIN);
        location_.first -= location_.first % TILESIZE;
        location_.second -= location_.second % TILESIZE;
        location_.first /= TILESIZE;
        location_.second /= TILESIZE;
        return Board::getBitBoardFromLocation(location_);
    }
    else
    {
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, idToUpdate_, SecondaryCMD::X,
            (float)location_.first - (float)offset_.first
        });
        EngineBase::executeCommand({
            PrimaryCMD::UPDATE, ObjectType::DRAWABLE, idToUpdate_, SecondaryCMD::Y,
            (float)location_.second - (float)offset_.second
        });
        EngineBase::executeCommand(Command(PrimaryCMD::DONEWRITING));

        location_ = EngineBase::getMousePosition();
        return 0;
    }
}

uint64_t DraggedPiece::getFromLocation() const
{
    return fromLocation_;
}
