//
// Created by 2ToThe10th on 16.04.2021.
//

#ifndef HW4_SRC_MAP_WITHOUT_CODE_GENERATION_H_
#define HW4_SRC_MAP_WITHOUT_CODE_GENERATION_H_

#include <cstdint>
#include <memory>
#include "Map.h"

class MapWithoutCodeGeneration : public Map {
 public:
  static std::shared_ptr<MapWithoutCodeGeneration> CreateMapFromFile(const std::string &filter_path);

 public:
  static constexpr int kArraySize = 256;

  [[nodiscard]] uint8_t GetR(unsigned char index) const override;
  [[nodiscard]] uint8_t GetG(unsigned char index) const override;
  [[nodiscard]] uint8_t GetB(unsigned char index) const override;

 private:
  uint8_t r_[kArraySize]{};
  uint8_t g_[kArraySize]{};
  uint8_t b_[kArraySize]{};

  MapWithoutCodeGeneration() = default;
};

#endif //HW4_SRC_MAP_WITHOUT_CODE_GENERATION_H_
