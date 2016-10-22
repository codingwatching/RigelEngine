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

#include "map.hpp"

#include <data/game_traits.hpp>

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility>


namespace rigel { namespace data { namespace map {

using namespace std;


Map::Map(
  TileSet tileSet,
  Image backdrop,
  boost::optional<Image>&& secondaryBackdrop,
  const int widthInTiles,
  const int heightInTiles
)
  : mTileSet(std::move(tileSet))
  , mLayers({
      TileArray(widthInTiles*heightInTiles, 0),
      TileArray(widthInTiles*heightInTiles, 0)})
  , mBackdropImage(std::move(backdrop))
  , mSecondaryBackdropImage(std::move(secondaryBackdrop))
  , mWidthInTiles(static_cast<size_t>(widthInTiles))
  , mHeightInTiles(static_cast<size_t>(heightInTiles))
{
  assert(widthInTiles >= 0);
  assert(heightInTiles >= 0);
}


Map::Map(
  TileSet tileSet,
  Image backdrop,
  const int widthInTiles,
  const int heightInTiles
)
  : Map(move(tileSet), move(backdrop), boost::none, widthInTiles, heightInTiles)
{
}


map::TileIndex Map::tileAt(
  const int layer,
  const int x,
  const int y
) const {
  return tileRefAt(layer, x, y);
}


void Map::setTileAt(
  const int layer,
  const int x,
  const int y,
  TileIndex index
) {
  if (index >= GameTraits::CZone::numTilesTotal) {
    throw invalid_argument("Tile index too large for tile set");
  }
  tileRefAt(layer, x, y) = index;
}


const map::TileIndex& Map::tileRefAt(
  const int layerS,
  const int xS,
  const int yS
) const {
  const auto layer = static_cast<size_t>(layerS);
  const auto x = static_cast<size_t>(xS);
  const auto y = static_cast<size_t>(yS);

  if (layer >= mLayers.size()) {
    throw invalid_argument("Layer index out of bounds");
  }
  if (x >= mWidthInTiles) {
    throw invalid_argument("X coord out of bounds");
  }
  if (y >= mHeightInTiles) {
    throw invalid_argument("Y coord out of bounds");
  }
  return mLayers[layer][x + y*mWidthInTiles];
}


map::TileIndex& Map::tileRefAt(
  const int layer,
  const int x,
  const int y
) {
  return const_cast<map::TileIndex&>(
    static_cast<const Map&>(*this).tileRefAt(layer, x, y));
}


}}}