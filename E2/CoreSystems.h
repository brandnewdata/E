#pragma once
#include "Predefines.h"
#include "ETimer.h"
#include "EInputManager.h"
#include "EGameInstance.h"
#include "ETableManager.h"


#define ISKEYDOWN(key) GET_SINGLE(EInputManager)->IsKeyDown(key);
#define ISKEYPRESSED(key) GET_SINGLE(EInputManager)->IsKeyPressed(key);
#define ISKEYUP(key) GET_SINGLE(EInputManager)->IsKeyUp(key);