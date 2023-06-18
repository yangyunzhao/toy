/**
 * Copyright © Mahjong squad
 * All Rights Reserved.
 * Authors:
 *          yangyunzhao@qq.com 
 */
#pragma once

#include "BaseAST.h"

class CompUnitAST : public BaseAST{
public:
    CompUnitAST();
    virtual ~CompUnitAST();
    virtual void accept(Visitor &visitor) override;
};