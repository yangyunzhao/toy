/**
 * Copyright © Mahjong squad
 * All Rights Reserved.
 * Authors:
 *          yangyunzhao@qq.com 
 */

#pragma once

#include "common.h"

class BaseAST {
public:
    virtual void accept(Visitor &visitor) = 0;
    BaseAST() = default;
    virtual ~BaseAST() = default;
};
