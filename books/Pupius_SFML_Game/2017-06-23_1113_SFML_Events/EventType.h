#pragma once


enum class EventType
{
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1, Mouse, Joystick
};


struct EventInfo
{
    EventInfo() { m_code = 0; }
    EventInfo(int l_event) { m_code = l_event; }

    union
    {
        int m_code;
    };
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
    EventDetails(const std::string& l_bindName)
        : m_name(l_bindName)
    {
        Clear();
    }

    void Clear()
    {
        m_size = sf::Vector2i(0, 0);
        m_textEntered = 0;
        m_mouse = sf::Vector2i(0, 0);
        m_mouseWheelDelta = 0;
        m_keyCode = -1;
    }
    std::string  m_name;
    sf::Vector2i m_size;
    sf::Uint32   m_textEntered;
    sf::Vector2i m_mouse;
    int          m_mouseWheelDelta;
    int          m_keyCode; // Single key code.

};


struct Binding
{
    Binding(const std::string& l_name)
        : m_name(l_name), m_details(l_name), c(0) {}

    void BindEvent(EventType l_type,
        EventInfo l_info = EventInfo())
    {
        m_events.emplace_back(l_type, l_info);
    }

    Events       m_events;
    std::string  m_name;
    int          c; // Count of events that are "happening".
    EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;

using CallbackContainer = std::unordered_map<
    std::string, std::function<void(EventDetails*)>>;

enum class StateType;

using Callbacks = std::unordered_map<
    StateType, CallbackContainer>;

class EventManager
{
public:
    EventManager();
    ~EventManager();

    bool AddBinding(Binding *l_binding);
    bool RemoveBinding(std::string l_name);
    void SetFocus(const bool& l_focus);

    // Needs to be defined in the header!
    template<class T>
    bool AddCallback(const std::string& l_name,
        void(T::*l_func)(EventDetails*), T* l_instance)
    {
        auto temp = std::bind(l_func, l_instance,
            std::placeholders::_1);
        return m_callbacks.emplace(l_name, temp).second;
    }

    void RemoveCallback(const std::string& l_name)
    {
        m_callbacks.erase(l_name);
    }

    void HandleEvent(sf::Event& l_event);

    void Update();

    sf::Vector2i GetMousePos(sf::RenderWindow* l_wind = nullptr)
    {
        return (l_wind ? sf::Mouse::getPosition(*l_wind)
            : sf::Mouse::getPosition());
    }

private:
    void LoadBindings();

    Bindings  m_bindings;
    Callbacks m_callbacks;
    bool      m_hasFocus;
};


void EventManager::HandleEvent(sf::Event& l_event) 
{
    // Handling SFML events.
    for (auto &b_itr : m_bindings)
    {

        Binding* bind = b_itr.second;
        for (auto &e_itr : bind->m_events)
        {
            EventType sfmlEvent = (EventType)l_event.type;
            if (e_itr.first != sfmlEvent) { continue; }

            if (sfmlEvent == EventType::KeyDown ||
                sfmlEvent == EventType::KeyUp)
            {
                if (e_itr.second.m_code == l_event.key.code) 
                {
                    // Matching event/keystroke.
                    // Increase count.
                    if (bind->m_details.m_keyCode != -1) 
                    {
                        bind->m_details.m_keyCode = e_itr.second.m_code;
                    }
                    ++(bind->c);
                    break;
                }
            }
            else if (sfmlEvent == EventType::MButtonDown ||
                sfmlEvent == EventType::MButtonUp)
            {
                if (e_itr.second.m_code == l_event.mouseButton.button) 
                {
                    // Matching event/keystroke.
                    // Increase count.
                    bind->m_details.m_mouse.x = l_event.mouseButton.x;
                    bind->m_details.m_mouse.y = l_event.mouseButton.y;
                    if (bind->m_details.m_keyCode != -1) {
                        bind->m_details.m_keyCode = e_itr.second.m_code;
                    }
                    ++(bind->c);
                    break;
                }
            }
            else {
                // No need for additional checking.
                if (sfmlEvent == EventType::MouseWheel) 
                {
                    bind->m_details.m_mouseWheelDelta =
                        l_event.mouseWheel.delta;
                }
                else if (sfmlEvent == EventType::WindowResized) 
                {
                    bind->m_details.m_size.x = l_event.size.width;
                    bind->m_details.m_size.y = l_event.size.height;
                }
                else if (sfmlEvent == EventType::TextEntered) {
                    bind->m_details.m_textEntered = l_event.text.unicode;
                }
                ++(bind->c);
            }

        }
    }
}