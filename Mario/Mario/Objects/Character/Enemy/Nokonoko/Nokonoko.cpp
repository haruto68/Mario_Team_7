#include"Nokonoko.h"

Nokonoko::Nokonoko() :
	nokonoko_images(),
	nokonoko_shell_images(),
	shell_mode(false)
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
	nokonoko_images = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 4, 2, 2, 32, 32);
	nokonoko_shell_images = rm->GetImages("Resource/Images/Enemy/nokonoko_revival.png", 2, 2, 1, 32, 32);
	image = nokonoko_images[2];
	// ���C���[�ݒ�
	z_layer = 3;
	// �����ݒ�
	is_mobility = true;
}

Nokonoko::~Nokonoko()
{

}

void Nokonoko::Initialize()
{

}

void Nokonoko::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Nokonoko::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;


	DrawRotaGraphF((int)graph_location.x, (int)graph_location.y, SIZE, 0.0, image, TRUE);

	if (image == nokonoko_images[2])
	{
		DrawRotaGraphF((int)graph_location.x, (int)graph_location.y - D_MONO, SIZE, 0.0, nokonoko_images[0], TRUE);
	}
	else
	{
		DrawRotaGraphF((int)graph_location.x, (int)graph_location.y - D_MONO, SIZE, 0.0, nokonoko_images[1], TRUE);
	}
}

void Nokonoko::Finalize()
{

}

void Nokonoko::OnHitCollision(GameObject* hit_object)
{

}

void Nokonoko::Movement(float delta_seconds)
{
	float speed = 100.0f;

	location.x -= 1.0f * speed * delta_seconds;
}

void Nokonoko::Animation()
{
	anime_count++;
	if (anime_count > 120)
	{
		if (image == nokonoko_images[2])
		{
			image = nokonoko_images[3];
		}
		else
		{
			image = nokonoko_images[2];
		}
		anime_count = 0;
	}
}