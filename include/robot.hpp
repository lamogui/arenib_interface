
#ifndef ROBOT__HPP
#define ROBOT__HPP

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "popup_widget.hpp"

class AbstractRobot : public sf::Drawable, public sf::Transformable
{
  public:
    AbstractRobot(const sf::IpAddress& addr, unsigned short port);
    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const = 0;
    static AbstractRobot* createFromName(std::string name,const sf::IpAddress& addr, unsigned short port);
    bool extract(sf::Packet& packet);
    bool send(sf::Packet& packet);

    //Create optionnal widget
    virtual inline RobotWidget* createWidget(std::string name) { (void) name; return 0;}

    sf::Mutex mutex;
    
  protected:

    virtual void setupGraphics()=0;
    inline virtual bool extractExtraInfos(sf::Packet& packet) {
      (void) packet;
      return true;
    }
    sf::IpAddress _addr;
    sf::Color _color;
    sf::Thread _thread;
    unsigned short _port;
    sf::Uint16 _flags;
    sf::Uint8 _state;
    
};

class Robot : public AbstractRobot
{
  public:
    Robot(const sf::IpAddress& addr, unsigned short port);
    virtual ~Robot();
    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;
    virtual RobotWidget* createWidget(std::string name);

  protected:
    virtual void setupGraphics();

  private:
    sf::RectangleShape _corp;
    sf::RectangleShape _roueGauche;
    sf::RectangleShape _roueDroite;
    sf::CircleShape _bumper;
    RobotWidget* _widget;
};




#endif
