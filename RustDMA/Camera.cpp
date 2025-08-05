#include "Pch.h"

uint64_t cameraSetup(uint64_t gameAssemblyBase) {
	uint64_t camera_manager = TargetProcess.Read<uint64_t>(gameAssemblyBase + cameraManagerOffset);
	if (!camera_manager)
	{
		return 0;
	}

	uint64_t camera_static = TargetProcess.Read<uint64_t>(camera_manager + cameraStaticOffset);
	if (!camera_static)
	{
		return 0;
	}

	uint64_t camera_object = TargetProcess.Read<uint64_t>(camera_static + cameraObjectOffset);
	if (!camera_object)
	{
		return 0;
	}

	uint64_t camera = TargetProcess.Read<uint64_t>(camera_object + cameraOffset);
	if (!camera)
	{
		return 0;
	}

	return camera;
}

Vector2 WorldToScreen(const Vector3& position, const ViewMatrix& viewMatrix) {
    float m00 = viewMatrix.matrix[0][0], m01 = viewMatrix.matrix[0][1], m02 = viewMatrix.matrix[0][2], m03 = viewMatrix.matrix[0][3];
    float m10 = viewMatrix.matrix[1][0], m11 = viewMatrix.matrix[1][1], m12 = viewMatrix.matrix[1][2], m13 = viewMatrix.matrix[1][3];
    float m20 = viewMatrix.matrix[2][0], m21 = viewMatrix.matrix[2][1], m22 = viewMatrix.matrix[2][2], m23 = viewMatrix.matrix[2][3];
    float m30 = viewMatrix.matrix[3][0], m31 = viewMatrix.matrix[3][1], m32 = viewMatrix.matrix[3][2], m33 = viewMatrix.matrix[3][3];

    float w = m03 * position.x + m13 * position.y + m23 * position.z + m33;

    if (w < 1.f)
        return Vector2(0, 0);
	float invW = 1.0f / w;

	float x = m00 * position.x + m10 * position.y + m20 * position.z + m30;
	float y = m01 * position.x + m11 * position.y + m21 * position.z + m31;

    float screenX = (halfScreenWidth) * (1.f + x * invW);
    float screenY = (halfScreenHeight) * (1.f - y * invW);

    return Vector2(screenX, screenY);
}
