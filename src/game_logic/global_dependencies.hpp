/* Copyright (C) 2018, Nikolai Wuttke. All rights reserved.
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

#include "base/spatial_types.hpp"
#include "base/warnings.hpp"

RIGEL_DISABLE_WARNINGS
#include <entityx/entityx.h>
RIGEL_RESTORE_WARNINGS


namespace rigel {
  struct IGameServiceProvider;

  namespace engine {
    class CollisionChecker;
    class ParticleSystem;
    class RandomNumberGenerator;
  }

  namespace game_logic {
    struct IEntityFactory;
    class Player;
  }
}


namespace rigel { namespace game_logic {

struct GlobalDependencies {
  Player* mpPlayer;
  const engine::CollisionChecker* mpCollisionChecker;
  engine::ParticleSystem* mpParticles;
  engine::RandomNumberGenerator* mpRandomGenerator;
  IEntityFactory* mpEntityFactory;
  IGameServiceProvider* mpServiceProvider;
  entityx::EventManager* mpEvents;
  const base::Vector* mpCameraPosition;
};

}}