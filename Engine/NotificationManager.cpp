#include "pch.h"
#include "NotificationManager.h"


using namespace RendUI;

NotificationManager::NotificationManager() {
    if (!font.openFromFile("sources/fonts/LeticeaBumsteadCyrillic.otf")) { // путь к шрифту
        std::cerr << "Не удалось загрузить шрифт!" << std::endl;
        exit(1);
    }
}

void NotificationManager::show(const std::string& msg, const sf::RenderWindow& window) {
    float w = static_cast<float>(window.getSize().x);
    float h = static_cast<float>(window.getSize().y);
    notifications.push_back(std::make_unique<Notification>(msg, font, w, h));
}

void NotificationManager::update(float dt) {
    for (auto it = notifications.begin(); it != notifications.end();) {
        (*it)->update(dt);
        if ((*it)->isFinished())
            it = notifications.erase(it);
        else
            ++it;
    }
}

void NotificationManager::draw(sf::RenderWindow& window, const sf::View& view) {
    float w = static_cast<float>(window.getSize().x);
    float h = static_cast<float>(window.getSize().y);
    for (auto& n : notifications)
        n->draw(window, view, w, h);
}