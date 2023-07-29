#ifndef INVENTORY_H
#define INVENTORY_H

#include <valarray>
#include <string>

class Inventory {
  std::valarray<int> resources;
	
public:
	int GetTotal() const;
  bool CanAfford(const Inventory& cost) const;
  
  Inventory& operator+=(const Inventory& other);
  Inventory& operator-=(const Inventory& other);
  Inventory& operator*=(int multiplier);
  explicit operator std::string() const;

  explicit Inventory(int brick, int energy, int glass, int heat, int wifi);
};

Inventory operator*(Inventory inventory, int multiplier);
Inventory operator*(int multiplier, Inventory inventory);

#endif
