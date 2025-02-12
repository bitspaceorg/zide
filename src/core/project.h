#pragma once

#include "forward_declarations.h"
#include <string>

namespace core {


class Project {
public:
  Project(std::string projectName) : m_projectName(projectName){};
  void setAuthor(std::string author) { this->m_authorName = author; };

private:
  std::string m_projectName = "Untitled";
  std::string m_projectDescription;
  std::string m_authorName = "<Unknown>";
  SpriteList m_spriteList;
};

} // namespace core
