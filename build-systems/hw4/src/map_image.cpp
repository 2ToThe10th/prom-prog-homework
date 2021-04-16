//
// Created by 2ToThe10th on 16.04.2021.
//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

#include "map_image.h"

void MapImage(std::shared_ptr<Map> map, const std::string &image_path, const std::string &output_path) {
  cv::Mat img = imread(image_path, cv::IMREAD_COLOR);
  if (img.empty()) {
    std::cout << "Could not read the image: " << image_path << std::endl;
    return;
  }

  for (int i = 0; i < img.cols; ++i) {
    for (int j = 0; j < img.rows; ++j) {
      auto &pixel = img.at<cv::Vec3b>(j, i);
      pixel.val[0] = map->GetB(pixel.val[0]);
      pixel.val[1] = map->GetG(pixel.val[1]);
      pixel.val[2] = map->GetR(pixel.val[2]);
    }
  }

  imwrite(output_path, img);
}