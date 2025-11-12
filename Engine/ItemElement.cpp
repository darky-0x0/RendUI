#include "pch.h"
#include "ItemElement.h"
#include "PrimitivesManager.h"


using namespace RendUI;

void ItemElement::deleteLinkedObject() {
    if (!manager) return;
    markedForDeletion = true;

    if (std::holds_alternative<std::shared_ptr<Point>>(linkedObject))
        manager->deletePoint(std::get<std::shared_ptr<Point>>(linkedObject));
    else if (std::holds_alternative<std::shared_ptr<Line>>(linkedObject))
        manager->deleteLine(std::get<std::shared_ptr<Line>>(linkedObject));
    else if (std::holds_alternative<std::shared_ptr<Polygon>>(linkedObject))
        manager->deletePolygon(std::get<std::shared_ptr<Polygon>>(linkedObject));
}