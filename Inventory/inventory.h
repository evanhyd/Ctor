#ifndef INVENTORY_H
#define INVENTORY_H

#include <valarray>
#include <string>

class Inventory {
  std::valarray<int> resources;
	
public:
	explicit constexpr Inventory(int brick, int energy, int glass, int heat, int wifi);
	
	int GetTotal() const;
  bool CanAfford(const Inventory& cost) const;
	bool TrySpend(const Inventory& other);
	void Gain(const Inventory& other);

  explicit operator std::string() const;
};

#endif
