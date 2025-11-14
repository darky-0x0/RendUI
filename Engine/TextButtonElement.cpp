#include "pch.h"
#include "TextButtonElement.h"
#include "Field.h"
#include <Windows.h>


using namespace RendUI;

TextButtonElement::TextButtonElement(const std::string& textStr, float fieldWidth, const sf::Font& fontRef, std::function<void()> cb)
    : text(fontRef), callback(cb)
{
    std::wstring wMsg = stringToWstring(textStr);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setString(wMsg);

    wrapText(fieldWidth - 2 * padding);

    sf::FloatRect tb = text.getLocalBounds();
    float width = fieldWidth - 2 * padding;
    float height = tb.size.y + tb.position.y + padding * 2.f;

    background.setSize({ width, height });
    background.setFillColor(sf::Color(80, 80, 80));
    background.setOutlineThickness(1.f);
    background.setOutlineColor(sf::Color::White);

    text.setPosition({ padding, padding / 2.f });
}

void TextButtonElement::wrapText(float maxWidth)
{
    std::wstring str = text.getString();
    std::wstringstream wss(str);
    std::wstring word;
    std::wstring finalStr;
    std::wstring line;

    sf::Text tempText = text; // временный текст для измерений

    while (wss >> word) {
        std::wstring testLine = line.empty() ? word : line + L" " + word;
        tempText.setString(testLine);
        if (tempText.getLocalBounds().size.x > maxWidth) {
            if (!line.empty()) finalStr += line + L"\n";
            line = word;
        }
        else {
            line = testLine;
        }
    }
    if (!line.empty()) finalStr += line;

    text.setString(finalStr);
}

void TextButtonElement::draw(sf::RenderWindow& window, const sf::Vector2f& position, float contentWidth)
{
    background.setPosition(position);
    background.setFillColor(selected ? sf::Color(80, 120, 200) : sf::Color(40, 40, 40));
    text.setPosition({ position.x + padding, position.y + padding / 2.f });
    window.draw(background);
    window.draw(text);
}

void TextButtonElement::handleEvent(const sf::Event& event, const sf::Vector2f& position, float contentWidth, const sf::Vector2f& mousePos)
{
    if (auto mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
        if(mouse->button == sf::Mouse::Button::Left) {
            sf::FloatRect bounds(position, background.getSize());
            if (bounds.contains(mousePos) && callback) {
                selected = true;
                callback(); // вызываем пользовательскую функцию
            }
        }
    }
}

// Конвертация строки
std::wstring TextButtonElement::stringToWstring(const std::string& str)
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
