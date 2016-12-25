/* Copyright (C) 2016, Nikolai Wuttke. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "base/warnings.hpp"
#include "base/spatial_types.hpp"
#include "engine/base_components.hpp"
#include "engine/timing.hpp"
#include "sdl_utils/texture.hpp"

RIGEL_DISABLE_WARNINGS
#include <boost/optional.hpp>
RIGEL_RESTORE_WARNINGS

#include <vector>


namespace rigel { namespace engine { namespace components {

struct SpriteFrame {
  SpriteFrame() = default;
  SpriteFrame(
    sdl_utils::NonOwningTexture image,
    base::Vector drawOffset
  )
    : mImage(std::move(image))
    , mDrawOffset(drawOffset)
  {
  }

  sdl_utils::NonOwningTexture mImage;
  base::Vector mDrawOffset;
};


struct Sprite {
  std::vector<SpriteFrame> mFrames;
  int mDrawOrder;

  std::vector<int> mFramesToRender;
  bool mShow = true;
};


/** Indicates that an entity should always be drawn last
 *
 * An entity marked with this component will alwyas have its Sprite drawn after
 * drawing the world, even if it is placed on top of foreground tiles.
 */
struct DrawTopMost {};


struct AnimationSequence {
  AnimationSequence() = default;
  explicit AnimationSequence(
    const int delayInTicks,
    boost::optional<int> endFrame = boost::none
  )
    : AnimationSequence(delayInTicks, 0, endFrame)
  {
  }

  AnimationSequence(
    const int delayInTicks,
    const int startFrame,
    boost::optional<int> endFrame,
    const int renderSlot = 0
  )
    : mDelayInTicks(delayInTicks)
    , mStartFrame(startFrame)
    , mEndFrame(std::move(endFrame))
    , mRenderSlot(renderSlot)
  {
  }

  int mDelayInTicks = 0;
  int mStartFrame = 0;
  boost::optional<int> mEndFrame;
  int mRenderSlot = 0;

  TimeStepper mTimeStepper;
};


struct Animated {
  std::vector<AnimationSequence> mSequences;
};

}}}