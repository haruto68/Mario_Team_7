#include"Ground.h"

Ground::Ground() :
	ground_state(eGroundState::FLOOR),
	floor_image(0),
	stairs_image(0),
	pipe_images(),
	pipe_num(0)
{

}

Ground::~Ground()
{

}

void Ground::Initialize()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(D_MONO, D_MONO);
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eItem);
	// �摜�ݒ�
	floor_image = rm->GetImages("Resource/Images/Block/floor.png")[0];
	stairs_image = rm->GetImages("Resource/Images/Block/kai_block.png")[0];
	pipe_images[0] = rm->GetImages("Resource/Images/dokan_left_up.png")[0];
	pipe_images[1] = rm->GetImages("Resource/Images/dokan_right_up.png")[0];
	pipe_images[2] = rm->GetImages("Resource/Images/dokan_left_down.png")[0];
	pipe_images[3] = rm->GetImages("Resource/Images/dokan_right_down.png")[0];
	// ���C���[�ݒ�
	z_layer = 1;
	// �����ݒ�
	is_mobility = false;
}

void Ground::Update(float delta_seconds)
{
	
}

void Ground::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	switch (ground_state)
	{
	case FLOOR:
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, floor_image, TRUE);
		break;
	case STAIRS:
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, stairs_image, TRUE);
		break;
	case PIPE:
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, pipe_images[pipe_num], TRUE);
		break;
	default:
		break;
	}
}

void Ground::Finalize()
{

}

void Ground::SetGroundState(eGroundState state)
{
	ground_state = state;
}

void Ground::SetPipeNum(int num)
{
	pipe_num = num;
}