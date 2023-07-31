#ifndef INVENTORY_H
#define INVENTORY_H

#include <valarray>
#include <string>
#include "resource_enum.h"
#include "../Utility/print.h"

class Inventory {
  std::valarray<int> resources;

  template <typename ContainerType, typename ReturnType>
  class IteratorImpl {
    ContainerType& resources;
    int index;

    IteratorImpl(ContainerType& resources, int index) : resources(resources), index(index) {}

  public:
    std::pair<ResourceEnum::Type, ReturnType&> operator*() {
      return { ResourceEnum::Type(index), resources[index] };
    }

    IteratorImpl& operator++() {
      Assert(0 <= index && index < int(ResourceEnum::Type::COUNT), "incrementing iterator passed the end");
      ++index;
      return *this;
    }

    bool operator==(const IteratorImpl& other) const {
      return &resources == &other.resources && index == other.index;
    }

    bool operator!=(const IteratorImpl& other) const {
      return !(*this == other);
    }

    friend class Inventory;
  };

public:
  using Iterator = IteratorImpl<std::valarray<int>, int>;
  using ConstIterator = IteratorImpl<const std::valarray<int>, const int>;

  explicit Inventory(int brick, int energy, int glass, int heat, int wifi);
  explicit Inventory(ResourceEnum::Type type, int count); 

  int GetResource(ResourceEnum::Type type) const;
	int GetTotal() const;
  bool CanAfford(const Inventory& cost) const;

  Iterator begin();
  ConstIterator begin() const;
  Iterator end();
  ConstIterator end() const;

  explicit operator std::string() const;
  Inventory& operator+=(const Inventory& other);
  Inventory& operator-=(const Inventory& other);
  Inventory& operator*=(int multiplier);
  
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
