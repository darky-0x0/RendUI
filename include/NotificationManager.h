#pragma once
#include "Notification.h"



namespace RendUI {
    class NotificationManager {
    public:
        NotificationManager();
        void show(const std::string& msg, const sf::RenderWindow& window);
        void update(float dt);
        void draw(sf::RenderWindow& window, const sf::View& view);

    private:
        sf::Font font;
        std::vector<std::unique_ptr<Notification>> notifications;
    };
}