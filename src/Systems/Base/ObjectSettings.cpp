// -*- Mode: C++; tab-width:2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi:tw=80:et:ts=2:sts=2
//
// -----------------------------------------------------------------------
//
// This file is part of RLVM, a RealLive virtual machine clone.
//
// -----------------------------------------------------------------------
//
// Copyright (C) 2007 Elliot Glaysher
//  
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//  
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//  
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//  
// -----------------------------------------------------------------------

#include "Systems/Base/ObjectSettings.hpp"

// -----------------------------------------------------------------------
// ObjectSettings
// -----------------------------------------------------------------------

ObjectSettings::ObjectSettings()
  : layer(0), spaceKey(0), objOnOff(0), timeMod(0), dispSort(0), initMod(0),
    weatherOnOff(0)
{}

// -----------------------------------------------------------------------

ObjectSettings::ObjectSettings(const std::vector<int>& data)
  : layer(0), spaceKey(0), objOnOff(0), timeMod(0), dispSort(0), initMod(0),
    weatherOnOff(0)
{
  if(data.size() > 0)
    layer = data[0];
  if(data.size() > 1)
    spaceKey = data[1];
  if(data.size() > 2)
    objOnOff = data[2];
  if(data.size() > 3)
    timeMod = data[3];
  if(data.size() > 4)
    dispSort = data[4];
  if(data.size() > 5)
    initMod = data[5];
  if(data.size() > 6)
    weatherOnOff = data[6];
}