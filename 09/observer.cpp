/**
 * Salon de discussion qui notifie ses utilisateurs. 
 */
#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct IObserver {
    virtual ~IObserver() = default;
    virtual void onMessage(const std::string &text) = 0;
};

class ChatRoom {
public:
    void subscribe(const std::shared_ptr<IObserver>&o) {
        observers_.push_back(o);
    }

    void post(const std::string& text) {
        std::erase_if(observers_, [](const auto& weak){ return weak.expired(); });

        for (const auto &weak : observers_) {
            if (const auto observer = weak.lock()) 
                observer->onMessage(text);
        }
    }

    std::vector<std::weak_ptr<IObserver>> observers_;
};

class User: public IObserver {
  public:
    explicit User(std::string name) : name_(std::move(name)) {}
    void onMessage(const std::string&text) override {
        std::cout << name_ << " recevied: " << text << '\n';
    }
    ~User() override { std::cout << name_ << " has left\n"; }
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
    } // bob est détruit ici.

    room.post("anyone here?");
}
