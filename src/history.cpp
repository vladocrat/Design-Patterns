#include "history.h"

#include <deque>

struct History::impl_t
{
    //std::deque<> queue;
};

History::History()
{
    createImpl();
}

History::~History()
{

}
