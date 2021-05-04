//
// Created by 2ToThe10th on 16.04.2021.
//

#include "map_with_code_generation.h"

uint8_t MapWithCodeGeneration::GetR(unsigned char index) const {
  return r_[index];
}

uint8_t MapWithCodeGeneration::GetG(unsigned char index) const {
  return g_[index];
}

uint8_t MapWithCodeGeneration::GetB(unsigned char index) const {
  return b_[index];
}