//
// Created by Elias on 30/09/2024.
//

#include "DraggedPiece.h"
#include "BoardValues.h"
#include "EngineBase/EngineBase.h"

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
}

uint64_t DraggedPiece::updateLocation()
{
    if (EngineBase::mouseButtonReleased(ENGINEBASE_BUTTON_LEFT))
    {
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, idToUpdate_, SecondaryCMD::X,
                                    (float) originalLocation_.first});
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, idToUpdate_, SecondaryCMD::Y,
                                    (float) originalLocation_.second});
        return location_.first / TILESIZE + (location_.second / TILESIZE) * 8;
    }
    else
    {
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, idToUpdate_, SecondaryCMD::X,
                                    (float) location_.first - (float) offset_.first});
        EngineBase::executeCommand({PrimaryCMD::UPDATE, ObjectType::DRAWABLE, idToUpdate_, SecondaryCMD::Y,
                                    (float) location_.second - (float) offset_.second});
        EngineBase::executeCommand(Command(PrimaryCMD::DONEWRITING));

        location_ = EngineBase::getMousePosition();
        return 0;
    }
}

uint64_t DraggedPiece::getFromLocation() const
{
    return fromLocation_;
}
