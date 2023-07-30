#ifndef INVENTORY_H
#define INVENTORY_H

#include <valarray>
#include <string>
#include "resource_enum.h"

class Inventory {
  std::valarray<int> resources;
	
public:
  int GetResource(ResourceEnum::Type type) const;
	int GetTotal() const;
  bool CanAfford(const Inventory& cost) const;
  
  Inventory& operator+=(const Inventory& other);
  Inventory& operator-=(const Inventory& other);
  Inventory& operator*=(int multiplier);
  
  explicit operator std::string() const;
  explicit Inventory(int brick, int energy, int glass, int heat, int wifi);
  
  friend bool operator==(const Inventory& inv1, const Inventory& inv2);
  friend bool operator!=(const Inventory& inv1, const Inventory& inv2);
};

Inventory operator+(Inventory inv1, const Inventory& inv2);
Inventory operator-(Inventory inv1, const Inventory& inv2);
Inventory operator*(Inventory inventory, int multiplier);
Inventory operator*(int multiplier, Inventory inventory);
bool operator==(const Inventory& inv1, const Inventory& inv2);
bool operator!=(const Inventory& inv1, const Inventory& inv2);

#endif
