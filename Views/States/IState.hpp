//
// Created on 2017/09/11 at 22:13.
//

#ifndef GWENT_ISTATE_HPP
#define GWENT_ISTATE_HPP

#include "../BaseWindow.hpp"


class IState
{
protected:
    BaseWindow *Base;
public:
    virtual void SetBase(BaseWindow *baseWindow) final
    {
        Base = baseWindow;
    }


    BaseWindow *GetBase() const
    {
        return Base;
    }
};


#endif //GWENT_ISTATE_HPP
