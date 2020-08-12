#include "geo2d.h"
#include "game_object.h"

#include "../../TestRunner/test_runner.h"

#include <vector>
#include <memory>

using namespace std;

// РћРїСЂРµРґРµР»РёС‚Рµ РєР»Р°СЃСЃС‹ Unit, Building, Tower Рё Fence С‚Р°Рє, С‡С‚РѕР±С‹ РѕРЅРё РЅР°СЃР»РµРґРѕРІР°Р»РёСЃСЊ РѕС‚
// GameObject Рё СЂРµР°Р»РёР·РѕРІС‹РІР°Р»Рё РµРіРѕ РёРЅС‚РµСЂС„РµР№СЃ.

class Unit : public GameObject{
public:
	explicit Unit(geo2d::Point position) : pos(position) {};
	bool Collide(const GameObject& that) const;
	bool CollideWith(const Unit& that) const;
	bool CollideWith(const Building& that) const;
	bool CollideWith(const Tower& that) const;
	bool CollideWith(const Fence& that) const;
	geo2d::Point GetPos() const;
private:
	geo2d::Point pos;
};

class Building : public GameObject {
public:
	explicit Building(geo2d::Rectangle geometry) : pos(geometry) {};
	bool Collide(const GameObject& that) const;
	bool CollideWith(const Unit& that) const;
	bool CollideWith(const Building& that) const;
	bool CollideWith(const Tower& that) const;
	bool CollideWith(const Fence& that) const;
	geo2d::Rectangle GetPos() const;
private:
	geo2d::Rectangle pos;
};

class Tower : public GameObject{
public:
	explicit Tower(geo2d::Circle geometry) : pos(geometry) {};
	bool Collide(const GameObject& that) const;
	bool CollideWith(const Unit& that) const;
	bool CollideWith(const Building& that) const;
	bool CollideWith(const Tower& that) const;
	bool CollideWith(const Fence& that) const;
	geo2d::Circle GetPos() const;
private:
	geo2d::Circle pos;
};

class Fence : public GameObject{
public:
	explicit Fence(geo2d::Segment geometry) : pos(geometry) {};
	bool Collide(const GameObject& that) const;
	bool CollideWith(const Unit& that) const;
	bool CollideWith(const Building& that) const;
	bool CollideWith(const Tower& that) const;
	bool CollideWith(const Fence& that) const;
	geo2d::Segment GetPos() const;
private:
	geo2d::Segment pos;
};


//
bool Unit::Collide(const GameObject& that) const {
	return that.CollideWith(*this);
}
bool Unit::CollideWith(const Unit& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Unit::CollideWith(const Building& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Unit::CollideWith(const Tower& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Unit::CollideWith(const Fence& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
geo2d::Point Unit::GetPos() const {
	return pos;
}

bool Building::Collide(const GameObject& that) const {
	return that.CollideWith(*this);
}
bool Building::CollideWith(const Unit& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Building::CollideWith(const Building& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Building::CollideWith(const Tower& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Building::CollideWith(const Fence& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
geo2d::Rectangle Building::GetPos() const {
	return pos;
}

bool Tower::Collide(const GameObject& that) const {
	return that.CollideWith(*this);
}
bool Tower::CollideWith(const Unit& that) const{
	return geo2d::Collide(pos, that.GetPos());
}
bool Tower::CollideWith(const Building& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Tower::CollideWith(const Tower& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Tower::CollideWith(const Fence& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
geo2d::Circle Tower::GetPos() const {
	return pos;
}

bool Fence::Collide(const GameObject& that) const {
	return that.CollideWith(*this);
}
bool Fence::CollideWith(const Unit& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Fence::CollideWith(const Building& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Fence::CollideWith(const Tower& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
bool Fence::CollideWith(const Fence& that) const {
	return geo2d::Collide(pos, that.GetPos());
}
geo2d::Segment Fence::GetPos() const {
	return pos;
}
//
bool Collide(const GameObject& first, const GameObject& second) {
	return first.Collide(second);
}
void TestAddingNewObjectOnMap() {
  // Р®РЅРёС‚-С‚РµСЃС‚ РјРѕРґРµР»РёСЂСѓРµС‚ СЃРёС‚СѓР°С†РёСЋ, РєРѕРіРґР° РЅР° РёРіСЂРѕРІРѕР№ РєР°СЂС‚Рµ СѓР¶Рµ РµСЃС‚СЊ РєР°РєРёРµ-С‚Рѕ РѕР±СЉРµРєС‚С‹,
  // Рё РјС‹ С…РѕС‚РёРј РґРѕР±Р°РІРёС‚СЊ РЅР° РЅРµС‘ РЅРѕРІС‹Р№, РЅР°РїСЂРёРјРµСЂ, РїРѕСЃС‚СЂРѕРёС‚СЊ РЅРѕРІРѕРµ Р·РґР°РЅРёРµ РёР»Рё Р±Р°С€РЅСЋ.
  // РњС‹ РјРѕР¶РµРј РµРіРѕ РґРѕР±Р°РІРёС‚СЊ, С‚РѕР»СЊРєРѕ РµСЃР»Рё РѕРЅ РЅРµ РїРµСЂРµСЃРµРєР°РµС‚СЃСЏ РЅРё СЃ РѕРґРЅРёРј РёР· СЃСѓС‰РµСЃС‚РІСѓСЋС‰РёС….
  using namespace geo2d;

  const vector<shared_ptr<GameObject>> game_map = {
    make_shared<Unit>(Point{3, 3}),
    make_shared<Unit>(Point{5, 5}),
    make_shared<Unit>(Point{3, 7}),
    make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
    make_shared<Tower>(Circle{Point{9, 4}, 1}),
    make_shared<Tower>(Circle{Point{10, 7}, 1}),
    make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
  };

  for (size_t i = 0; i < game_map.size(); ++i) {
    Assert(
      Collide(*game_map[i], *game_map[i]),
      "An object doesn't collide with itself: " + to_string(i)
    );

    for (size_t j = 0; j < i; ++j) {
      Assert(
        !Collide(*game_map[i], *game_map[j]),
        "Unexpected collision found " + to_string(i) + ' ' + to_string(j)
      );
    }
  }

  auto new_warehouse = make_shared<Building>(Rectangle{{4, 3}, {9, 6}});
  ASSERT(!Collide(*new_warehouse, *game_map[0]));
  ASSERT( Collide(*new_warehouse, *game_map[1]));
  ASSERT(!Collide(*new_warehouse, *game_map[2]));
  ASSERT( Collide(*new_warehouse, *game_map[3]));
  ASSERT( Collide(*new_warehouse, *game_map[4]));
  ASSERT(!Collide(*new_warehouse, *game_map[5]));
  ASSERT(!Collide(*new_warehouse, *game_map[6]));

  auto new_defense_tower = make_shared<Tower>(Circle{{8, 2}, 2});
  ASSERT(!Collide(*new_defense_tower, *game_map[0]));
  ASSERT(!Collide(*new_defense_tower, *game_map[1]));
  ASSERT(!Collide(*new_defense_tower, *game_map[2]));
  ASSERT( Collide(*new_defense_tower, *game_map[3]));
  ASSERT( Collide(*new_defense_tower, *game_map[4]));
  ASSERT(!Collide(*new_defense_tower, *game_map[5]));
  ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestAddingNewObjectOnMap);
  return 0;
}
