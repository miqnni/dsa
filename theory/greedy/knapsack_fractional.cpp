#include <functional>
#include <iostream>

class Item {
private:
  int weight;
  int value;
  double ratio; // Value per weight unit

public:
  Item(int weight = 0, int value = 0) : weight(weight), value(value), ratio(1.0 * value / weight) {}

  int getWeight() const { return weight; }
  int getValue() const { return value; }
  double getRatio() const { return ratio; }
};

class FractionalKnapsack {
private:
  const std::function<bool(Item&, Item&)> cmp = [](Item& a, Item& b) { return a.getRatio() > b.getRatio(); };

public:
  double fractionalKnapsack(std::vector<int>& val, std::vector<int>& wt, int capacity) {
    const int n{ val.size() };
    std::vector<Item> items(n);
    for (int i{}; i < n; i++) {
      items[i] = (struct Item){ wt[i], val[i] };
      // std::cout << items[i].getRatio() << std::endl;
    }

    std::sort(items.begin(), items.end(), cmp);

    double bestTotalValue{};
    double remainingCapacity{ capacity };
    for (const Item& item : items) {
      if (item.getWeight() >= remainingCapacity) {
        // This is the last item which we take a fraction (or the whole) of.
        return bestTotalValue + remainingCapacity * item.getRatio();
      }
      // Take the whole item.
      bestTotalValue += item.getValue();
      remainingCapacity -= item.getWeight();
    }

    return bestTotalValue;
  }
};
