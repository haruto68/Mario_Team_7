#include"Collision.h"
#include <math.h>

Collision::Collision() :
	is_blocking(false),
	box_size(0.0f),
	pivot(0.0f),
	object_type(eObjectType::eNone),
	hit_object_type()
{

}

Collision::~Collision()
{
	hit_object_type.clear();
}

/// <summary>
/// �K�p�I�u�W�F�N�g���m�F���鏈��
/// </summary>
/// <param name="hit_object">����̃I�u�W�F�N�g�^�C�v</param>
/// <returns>�K�p����I�u�W�F�N�g�Ȃ�Atrue</returns>
bool Collision::IsCheckHitTarget(eObjectType hit_object) const
{
	for (eObjectType type : hit_object_type)
	{
		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}