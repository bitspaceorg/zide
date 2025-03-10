#pragma once
#include "forward_declarations.h"
#include <string>
// clang-format off
namespace core {
class Project {
public:
                Project(std::string projectName);
                ~Project();

  size_t        active()                                    const;
  std::string   name()                                      const;
  std::string   author()                                    const;
  std::string   description()                               const;

  void          setName(std::string name);
  void          setActive(size_t spriteIndex); // [TODO]: Observer needed
  void          setAuthor(std::string author);
  void          setDescription(std::string description);
  void          addSprite(uint32_t width, uint32_t height, std::string name);

private:
  size_t        m_selectedSprite;
  SpriteList    m_spriteList;
  std::string   m_authorName          = "<Unknown>";
  std::string   m_projectName         = "Untitled";
  std::string   m_projectDescription  = "";

};
} // namespace core
