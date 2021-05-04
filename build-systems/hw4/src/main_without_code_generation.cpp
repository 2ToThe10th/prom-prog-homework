#include <iostream>
#include "map_without_code_generation.h"
#include "map_image.h"

int main() {
  auto map = MapWithoutCodeGeneration::CreateMapFromFile("map.png");
  if (!map) {
    return 1;
  }
  std::string image_path;
  std::cout << "Write filenames to apply filter:" << std::endl;
  while (std::getline(std::cin, image_path)) {
    MapImage(map, image_path, "filtered_without_code_generation_" + image_path);
  }
  return 0;
}