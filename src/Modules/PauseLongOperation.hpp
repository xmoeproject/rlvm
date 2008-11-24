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
// the Free Software Foundation; either version 3 of the License, or
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

#ifndef __PauseLongOperation_hpp__
#define __PauseLongOperation_hpp__

#include "MachineBase/LongOperation.hpp"
#include "Systems/Base/EventHandler.hpp"

/**
 * Main pause function. Exported for TextoutLongOperation to abuse.
 */
struct PauseLongOperation : public LongOperation, public EventHandler
{
private:
  RLMachine& machine;

  bool is_done_;

  /**
   * @name Automode Related Variables
   *
   * @{
   */
  /// Keeps track of when PauseLongOperation was constructed (in ticks from
  /// start)
  unsigned int start_time_;

  /// How long after start_time_ to automatically break out of this
  /// Longoperation if auto mode is enabled
  unsigned int automode_time_;
  /// @}

public:
  PauseLongOperation(RLMachine& machine);
  ~PauseLongOperation();

  // ------------------------------------------ [ EventHandler interface ]
  void mouseMotion(const Point&);
  bool mouseButtonStateChanged(MouseButton mouseButton, bool pressed);
  bool keyStateChanged(KeyCode keyCode, bool pressed);

  // ----------------------------------------- [ LongOperation interface ]
  bool operator()(RLMachine& machine);
};

// -----------------------------------------------------------------------
// NewPageAfterLongop
// -----------------------------------------------------------------------
class NewPageAfterLongop : public PerformAfterLongOperationDecorator
{
private:
  virtual void performAfterLongOperation(RLMachine& machine);
public:
  NewPageAfterLongop(LongOperation* inOp);
  ~NewPageAfterLongop();
};

// -----------------------------------------------------------------------
// HardBrakeAfterLongop
// -----------------------------------------------------------------------
class HardBrakeAfterLongop : public PerformAfterLongOperationDecorator
{
private:
  virtual void performAfterLongOperation(RLMachine& machine);
public:
  HardBrakeAfterLongop(LongOperation* inOp);
  ~HardBrakeAfterLongop();
};

#endif
