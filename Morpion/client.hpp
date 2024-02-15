#pragma once
#include <array>

static enum LightState {
    NotRecv = 0,
    IsSend = 1,
    IsRecv = 2
};

static std::array<LightState, 3> states{
    LightState::NotRecv,
    LightState::IsSend,
    LightState::IsRecv
};

static LightState state = states[0];

static void toggle() {
    state = states[(state + 1) % states.size()];
}

static bool end = false;
static const char* importFromMorpion;
static int client();
static int sendData(const char data[4096]);
static char* recvData();