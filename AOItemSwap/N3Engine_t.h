#pragma once

struct Identity_t
{
	int Type;
	int Instance;
};

class N3Dynel_t
{
public:
	char _0x0000[0x14];
	Identity_t Identity;
};

class N3EngineClientAnarchy_t
{
public:
	char _0x0000[0x84];
	N3Dynel_t* LocalPlayer;
};