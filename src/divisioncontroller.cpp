#include "divisioncontroller.h"

#include <QQmlEngine>

#include "divisionmodel.h"
#include "division.h"

struct DivisionController::impl_t
{
    std::unique_ptr<DivisionModel> model;
};

DivisionController* DivisionController::instance()
{
    static DivisionController dc;
    return &dc;
}

DivisionController::DivisionController()
{
    createImpl();

    impl().model = std::make_unique<DivisionModel>();
}

DivisionController::~DivisionController()
{
}

void DivisionController::registerType()
{
    qmlRegisterSingletonInstance<DivisionController>("DivisionController", 1, 0, "DivisionController", DivisionController::instance());
}

DivisionModel* DivisionController::model()
{
    return impl().model.get();
}

void DivisionController::add()
{
    impl().model->addDivision(new Division);
}
