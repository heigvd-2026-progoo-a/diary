// g++ -std=c++20 observer.cpp -o observer
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onMessage(const std::string& text) = 0;
};

class ChatRoom {
public:
    // The room does not own its observers: it only keeps weak references.
    void subscribe(const std::shared_ptr<IObserver>& observer) {
        observers_.push_back(observer);
    }

    void post(const std::string& text) {
        // Forget the observers that no longer exist.
        std::erase_if(observers_, [](const auto& weak) { return weak.expired(); });

        for (const auto& weak : observers_)
            if (auto observer = weak.lock()) observer->onMessage(text);
    }

private:
    std::vector<std::weak_ptr<IObserver>> observers_;
};

struct User : public IObserver {
    explicit User(std::string name) : name_(std::move(name)) {}
    ~User() override { std::cout << name_ << " left\n"; }

    void onMessage(const std::string& text) override {
        std::cout << name_ << " received: " << text << '\n';
    }

private:
    std::string name_;
};

int main() {
    ChatRoom room;
    auto alice = std::make_shared<User>("Alice");
    room.subscribe(alice);

    {
        auto bob = std::make_shared<User>("Bob");
        room.subscribe(bob);
        room.post("hello");
    }  // Bob is destroyed here and never unsubscribed

    room.post("anyone here?");  // with an IObserver* this would be a use-after-free
}
