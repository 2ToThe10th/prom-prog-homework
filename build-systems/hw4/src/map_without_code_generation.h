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

  [[nodiscard]] const uint8_t *GetR() const override;
  [[nodiscard]] const uint8_t *GetG() const override;
  [[nodiscard]] const uint8_t *GetB() const override;

 private:
  uint8_t r[kArraySize]{};
  uint8_t g[kArraySize]{};
  uint8_t b[kArraySize]{};

  MapWithoutCodeGeneration() = default;
};

#endif //HW4_SRC_MAP_WITHOUT_CODE_GENERATION_H_
