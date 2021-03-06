//
// Created by koncord on 30.11.17.
//

#pragma once

#include <components/openmw-mp/Base/BasePlayer.hpp>
#include <apps/openmw-mp/Script/LuaState.hpp>
#include "BaseMgr.hpp"

class Player;

class WeatherMgr final: public BaseMgr
{
public:
    static void Init(LuaState &lua);
public:
    explicit WeatherMgr(Player *player);
    ~WeatherMgr() = default;

    void setWeather(int weather);

    void setCurrent(int weather);
    int getCurrent() const;

    void setNext(int weather);
    int getNext() const;

    void setTransition(float time);
    float getTransition() const;

    void setUpdate(float time);
    float getUpdate() const;

    void requestWeather();

    void copy(const WeatherMgr &other);

private:
    void processUpdate() final;
};


