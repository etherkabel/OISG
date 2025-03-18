
#include <functional>
#include <map>
template <typename... Args>
class Signal {
public:
    using SlotType = std::function<void(Args...)>;

    int connect(SlotType slot) {
        slots.emplace(m_nextId, slot);
        return m_nextId++;
    }

    template<typename T>
    int connect(T *obj, void (T::*func)(Args...)) {
        auto wrappedCallback = [obj, func](Args... args) {
            (obj->*func)(args...);
        };
        return connect(wrappedCallback);
    }

    bool disconnect(int id) {
        if (slots.find(id) != slots.end()) {
            slots.erase(id);
            return true;
        }
        return false;
    }

    void emit(Args... args) {
        auto copy = slots;
        for (auto &slot : copy) {
            slot.second(args...);
        }
    }

private:
    int m_nextId = 0;
    std::map<int, SlotType> slots;

};