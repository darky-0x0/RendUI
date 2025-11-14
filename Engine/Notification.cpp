#include "pch.h"
#include "Notification.h"
#include <Windows.h>


using namespace RendUI;

Notification::Notification(const std::string& msg, const sf::Font& font, float windowWidth, float windowHeight)
    : lifetime(3.f), finished(false), text(font)
{
    std::wstring wMsg = stringToWstring(msg);
    text.setString(wMsg);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);

    updatePosition(windowWidth, windowHeight);

    background.setPosition(position);
    text.setPosition({ position.x + padding, position.y + padding / 2.f });
}

void Notification::update(float dt) {
    lifetime -= dt;
    if (lifetime <= 0.f) finished = true;

    float alpha = std::clamp(lifetime / 3.f, 0.f, 1.f);
    sf::Color bg = background.getFillColor();
    sf::Color txt = text.getFillColor();
    background.setFillColor(bg);
    text.setFillColor(txt);
}

void Notification::draw(sf::RenderWindow& window, const sf::View& view, float windowWidth, float windowHeight) {
    
    updatePosition(windowWidth, windowHeight);

    background.setPosition(position);
    text.setPosition({ position.x + padding, position.y + padding / 2.f });

    if (!finished) {
        window.draw(background);
        window.draw(text);
    }
}

void Notification::updatePosition(float windowWidth, float windowHeight) {
    // вычисляем размер под текст
    sf::FloatRect tb = text.getLocalBounds();
    width = std::min(windowWidth * 0.9f, tb.size.x + padding * 2.f);
    height = tb.size.y + padding * 2.f;

    background.setSize({ width, height });
    background.setFillColor(sf::Color(0, 0, 0, 180));
    background.setOutlineThickness(2.f);
    background.setOutlineColor(sf::Color::White);

    // позиция — по центру, снизу
    float x = (windowWidth - width) / 2.f;
    float y = windowHeight - height - 20.f;

    position = { x, y };
}

// Конвертация строки
std::wstring Notification::stringToWstring(const std::string& str)
{
    if (str.empty()) return L"";
    // Определяем, сколько wchar_t нужно для строки
    int size_needed = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    if (size_needed == 0) {
        std::cerr << "Ошибка конвертации строки!\n";
        return L"";
    }
    std::wstring wstr(size_needed - 1, 0); // -1 потому что MultiByteToWideChar считает \0
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], size_needed);
    return wstr;
}