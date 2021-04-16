//
// Created by 2ToThe10th on 16.04.2021.
//

#ifndef HW4_SRC_MAP_H_
#define HW4_SRC_MAP_H_

class Map {
 public:
  [[nodiscard]] virtual const uint8_t *GetR() const = 0;
  [[nodiscard]] virtual const uint8_t *GetG() const = 0;
  [[nodiscard]] virtual const uint8_t *GetB() const = 0;
};

#endif //HW4_SRC_MAP_H_
