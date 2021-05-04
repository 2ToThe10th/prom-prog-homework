//
// Created by 2ToThe10th on 16.04.2021.
//

#ifndef HW4_SRC_MAP_H_
#define HW4_SRC_MAP_H_

class Map {
 public:
  [[nodiscard]] virtual uint8_t GetR(unsigned char index) const = 0;
  [[nodiscard]] virtual uint8_t GetG(unsigned char index) const = 0;
  [[nodiscard]] virtual uint8_t GetB(unsigned char index) const = 0;
};

#endif //HW4_SRC_MAP_H_
