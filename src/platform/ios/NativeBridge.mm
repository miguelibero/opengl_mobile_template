//
//  NativeBridge.cpp
//  OpenglGame
//
//  Created by mibero on 14/10/14.
//  Copyright (c) 2014 Miguel Ibero. All rights reserved.
//

#include "base/NativeBridge.hpp"
#import <Foundation/Foundation.h>

NativeBridge::DataPtr NativeBridge::readAsset(const std::string& name)
{
    NSString* nsname = [NSString stringWithUTF8String:name.c_str()];
    NSString* nstype = @"";
    NSString* path = [[NSBundle mainBundle] pathForResource:nsname ofType:nstype];
    NSData* data = [NSData dataWithContentsOfFile:path];
    uint8_t* ptr = (uint8_t*)data.bytes;
    return DataPtr(new Data(ptr, ptr+data.length));
}

NativeBridge::DataPtr NativeBridge::readImage(const std::string& name)
{
    return nullptr;
}
