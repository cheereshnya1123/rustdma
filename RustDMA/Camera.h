#pragma once
extern unsigned int screenWidth;
extern unsigned int halfScreenHeight;
extern unsigned int screenHeight;
extern unsigned int halfScreenWidth;
uint64_t cameraSetup(uint64_t gameAssemblyBase);
ViewMatrix GetViewMatrix(uint64_t camera);
Vector2 WorldToScreen(const Vector3& position, const ViewMatrix& viewMatrix);