#include"Kuribo.h"

Kuribo::Kuribo() :
	kuribo_images()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(D_MONO, D_MONO);
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eGround);
	// �摜�ݒ�
	kuribo_images = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = kuribo_images[0];
	// ���C���[�ݒ�
	z_layer = 3;
	// �����ݒ�
	is_mobility = true;
}

Kuribo::~Kuribo()
{

}

void Kuribo::Initialize()
{
	
}

void Kuribo::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Kuribo::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;

	DrawRotaGraphF((int)graph_location.x, (int)graph_location.y, SIZE, 0.0, image, TRUE);
}

void Kuribo::Finalize()
{

}

void Kuribo::OnHitCollision(GameObject* hit_object)
{
	
}

void Kuribo::Movement(float delta_seconds)
{
	float speed = 100.0f;

	location.x -= 1.0f* speed * delta_seconds;
}

void Kuribo::Animation()
{
	anime_count++;
	if (anime_count > 360)
	{
		if (image == kuribo_images[0])
		{
			image = kuribo_images[1];
		}
		else
		{
			image = kuribo_images[0];
		}
		anime_count = 0;
	}
}