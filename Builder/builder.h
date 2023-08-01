#ifndef BUILDER_H
#define BUILDER_H 
#include <vector> 
#include <string>
#include <map>
#include <optional>
#include "../Inventory/inventory.h"
#include "../Building/property.h"
#include "../Building/residence_property.h"
#include "../SaveLoadable/save_loadable.h"
#include "colour_enum.h"

class Dice; 

class Builder : public SaveLoadable {
protected:
  ColourEnum::Type colour;
  Inventory inventory;
  std::map<int, Property*> roads;
  std::map<int, ResidenceProperty*> residences;
  const Dice* dice;

public:
  Inventory& GetInventory();
  const Inventory& GetInventory() const;
  int GetVictoryPoints() const;

  bool OwnRoad(int roadIndex) const; 
  bool OwnResidence(int residenceIndex) const; 
  void AddRoad(int index, Property& property);
  void AddResidence(int index, ResidenceProperty& property);
  int OwnedRoadCount() const;
  int OwnedResidenceCount() const;

  int Roll();
  void SetDice(const Dice& newDice);
  
  ColourEnum::Type GetColour() const;
  std::string GetStats() const;
  std::string GetResidences() const;

  virtual std::string SaveData() const override;
  virtual void LoadData(std::ifstream& file) override;
  
  explicit Builder(ColourEnum::Type colour);
  virtual ~Builder();
};

#endif 
