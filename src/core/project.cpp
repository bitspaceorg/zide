#include "project.h"

namespace core {
Project::Project(std::string projectName) : m_projectName(projectName) {}
Project::~Project() = default;

std::string Project::name() const { return m_projectName; }
std::string Project::author() const { return m_projectName; }
std::string Project::description() const { return m_projectName; }
size_t Project::active() const { return m_selectedSprite; }

void Project::setName(std::string name) { m_projectName = name; }
void Project::setActive(size_t spriteIndex) { m_selectedSprite = spriteIndex; }
void Project::setAuthor(std::string author) { m_authorName = author; }
void Project::setDescription(std::string description) {
  m_projectDescription = description;
}
void Project::addSprite(uint32_t width, uint32_t height, std::string name) {
  m_spriteList.emplace_back(make_shared<Sprite>(width, height, name));
}
} // namespace core
