//
// Created by Pavel Akhtyamov on 02.05.2020.
//
#include "WeatherMock.h"

cpr::Response WeatherMock::JustGet(const std::string &city, const cpr::Url &url) {
  return Weather::Get(city, url);
}

