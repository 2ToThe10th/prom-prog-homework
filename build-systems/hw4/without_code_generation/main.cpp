#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

class Map {
 public:
  static std::shared_ptr<Map> CreateMapFromFile(const std::string &filter_path) {
    cv::Mat filter = imread(filter_path, cv::IMREAD_COLOR);
    if (filter.empty()) {
      std::cout << "Could not read the filter: " << filter_path << std::endl;
      return nullptr;
    }
    if (filter.size[0] != 3 && filter.size[1] != kArraySize) {
      std::cout << "Incorrect filter size: " << filter.size << std::endl;
      return nullptr;
    }
    auto map = std::shared_ptr<Map>(new Map());
    for (int i = 0; i < kArraySize; ++i) {
      map->r[i] = filter.at<cv::Vec3b>(0, i).val[2];
      map->g[i] = filter.at<cv::Vec3b>(1, i).val[1];
      map->b[i] = filter.at<cv::Vec3b>(2, i).val[0];
    }
    return map;
  }

 public:
  static constexpr int kArraySize = 256;

  uint8_t r[kArraySize];
  uint8_t g[kArraySize];
  uint8_t b[kArraySize];

 private:
  Map() = default;
};

void MapImage(std::shared_ptr<Map> map, const std::string &image_path) {
  cv::Mat img = imread(image_path, cv::IMREAD_COLOR);
  if (img.empty()) {
    std::cout << "Could not read the image: " << image_path << std::endl;
    return;
  }

  for (int i = 0; i < img.cols; ++i) {
    for (int j = 0; j < img.rows; ++j) {
      auto &pixel = img.at<cv::Vec3b>(j, i);
      pixel.val[0] = map->b[pixel.val[0]];
      pixel.val[1] = map->g[pixel.val[1]];
      pixel.val[2] = map->r[pixel.val[2]];
    }
  }

  imwrite("filtered_" + image_path, img);
}

int main() {
  auto map = Map::CreateMapFromFile("map.png");
  if (!map) {
    return 1;
  }
  std::string image_path;
  std::cout << "Write filenames to apply filter:" << std::endl;
  while (std::getline(std::cin, image_path)) {
    MapImage(map, image_path);
  }
  return 0;
}