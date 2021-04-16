//
// Created by 2ToThe10th on 16.04.2021.
//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

#include "map_without_code_generation.h"

std::shared_ptr<MapWithoutCodeGeneration> MapWithoutCodeGeneration::CreateMapFromFile(const std::string &filter_path) {
  cv::Mat filter = imread(filter_path, cv::IMREAD_COLOR);
  if (filter.empty()) {
    std::cout << "Could not read the filter: " << filter_path << std::endl;
    return nullptr;
  }
  if (filter.size[0] != 3 && filter.size[1] != kArraySize) {
    std::cout << "Incorrect filter size: " << filter.size << std::endl;
    return nullptr;
  }
  auto map = std::shared_ptr<MapWithoutCodeGeneration>(new MapWithoutCodeGeneration());
  for (int i = 0; i < kArraySize; ++i) {
    map->r[i] = filter.at<cv::Vec3b>(0, i).val[2];
    map->g[i] = filter.at<cv::Vec3b>(1, i).val[1];
    map->b[i] = filter.at<cv::Vec3b>(2, i).val[0];
  }
  return map;
}

const uint8_t *MapWithoutCodeGeneration::GetR() const {
  return r;
}

const uint8_t *MapWithoutCodeGeneration::GetG() const {
  return g;
}

const uint8_t *MapWithoutCodeGeneration::GetB() const {
  return b;
}
