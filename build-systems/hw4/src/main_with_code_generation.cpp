#include <iostream>
#include <string>
#include "map_with_code_generation.h"
#include "map_image.h"

int main() {
  auto map = std::make_shared<MapWithCodeGeneration>();
  std::string image_path;
  std::cout << "Write filenames to apply filter:" << std::endl;
  while (std::getline(std::cin, image_path)) {
    MapImage(map, image_path, "filtered_with_code_generation_" + image_path);
  }
  return 0;
}