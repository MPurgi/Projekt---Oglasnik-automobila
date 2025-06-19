#pragma once

typedef enum {
	NEPOZNATO_MOTOR = 0,
	BENZIN = 1,
	DIZEL,
	HIBRID,
	ELEKTRICNI
} EngineType;

typedef enum {
	NEPOZNATO_MJENJAC = 0,
	AUTOMATSKI = 1,
	RUCNI,
	POLUAUTOMATSKI
}GearboxType;